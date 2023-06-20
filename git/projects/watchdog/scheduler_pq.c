/*******************************************************************************
*		                			SCHEDULER                                                  
*******************************************************************************/
/*******************************************************************************
* DESCRIPTION: 		A task scheduler. Supports scheduling callback functions to
* 					be performed after a given interval of time in seconds, and
* 					repeating them if needed.
* AUTHOR: Tom Lyden
* REVIEWER: Oriya Turgeman
* DATE: 26/04/2022
* VERSION: 0.1
*******************************************************************************/
#include <stdlib.h> 	/* malloc(), free()	 */
#include <assert.h> 	/* assert()			 */
#include <time.h> 		/* time()			 */
#include <unistd.h> 	/* sleep()			 */

#include "heap_pq.h"
#include "scheduler_pq.h"

enum status { ERROR = -1, SUCCESS = 0, FAILURE = 1, STOP = 0, REPEAT = 1, TRUE = 1, FALSE = 0 };

struct scheduler
{
	pqueue_ty *tasks;
	int should_stop;
};

static int SchedTaskCompare(const void *task1, const void *task2);
static int SchedTaskIsMatch(const void *task, const void *uid);
static int UpdateTaskTimes(scheduler_ty *scheduler);

scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *scheduler = NULL;
	
	/* allocate struct for scheduler */
	scheduler = (scheduler_ty *)malloc(sizeof(scheduler_ty));
	
	/* handle failure */
	if (!scheduler)
	{
		return NULL;
	}
	
	/* create priority queue */
	scheduler->tasks = PQueueCreate(SchedTaskCompare);
	
	/* handle failure */
	if (!scheduler->tasks)
	{
		free(scheduler);
		return NULL;
	}
	
	
	/* populate struct */
	scheduler->should_stop = FALSE;
	
	/* return struct */
	return scheduler;
}

void SchedulerDestroy(scheduler_ty *scheduler)
{
	assert(scheduler);
	
	SchedulerClear(scheduler);
	
	/* destroy priority queue */
	PQueueDestroy(scheduler->tasks); 
	scheduler->tasks = NULL;
	
	/* free struct memory */
	free(scheduler);
}

uid_ty SchedulerAdd(scheduler_ty *scheduler, callback_ty callback, void *param, ts_ty interval)
{
	task_ty *task = NULL;
	
	/* assert */
	assert(scheduler);
	assert(callback);
	
	/* create and populate task struct */
	task = TaskCreate(callback, param, interval);
	
	/* handle failure */
	if (!task)
	{
		return bad_uid;
	}

	if (TaskUpdateTime(task))
	{
		TaskDestroy(task);

		return bad_uid;
	}
	
	/* enqueue task in priority queue */
	if (PQueueEnqueue(scheduler->tasks, task))
	{
		/* handle failure */
		TaskDestroy(task);
		
		return bad_uid;
	}
	
	return TaskGetUID(task);
}

int SchedulerRemove(scheduler_ty *scheduler, uid_ty task_id)
{
	task_ty *task = NULL;
	
	/* assert */
	assert(scheduler);
	assert(!UIDIsBadUid(task_id));
	
	/* find task with given uid in queue */
	/* remove task from queue */
	task = PQueueErase(scheduler->tasks, SchedTaskIsMatch, &task_id);
	
	if (!task)
	{
		return FAILURE;
	}
	
	TaskDestroy(task);
	
	/* return value accordingly */
	return SUCCESS;
}

int SchedulerRun(scheduler_ty *scheduler)
{
	ts_ty time_to_exec;
	task_ty *task = NULL;
	int res = 0;
	int is_task_repeat = FALSE;
	
	/* assert */
	assert(scheduler);
	
	/* update execution times for tasks */
	if(UpdateTaskTimes(scheduler))
	{
		return ERROR; 
	}
	
	/* lower stop flag */
	scheduler->should_stop = FALSE;
	
	/* while stop flag is off */
	while(!scheduler->should_stop)
	{
		/* if queue is empty, set return to 0 and break */
		if (SchedulerIsEmpty(scheduler))
		{
			res = STOP;
			break;
		}
		
		/* look at top priority task in queue */
		task = PQueueDequeue(scheduler->tasks);
		time_to_exec = TaskGetExecTime(task);
		
		/* while it's not time to execute, sleep */
		while(nanosleep(&time_to_exec, &time_to_exec) && !scheduler->should_stop);
		
		/* perform callback */
		is_task_repeat = TaskRunAction(task);
		
		/* if callback returns 1, add it again, otherwise destroy it */
		if (REPEAT == is_task_repeat)
		{
			TaskUpdateTime(task);
			if (PQueueEnqueue(scheduler->tasks, task))
			{
				/* handle failure */
				res = ERROR;
				break;
			}
		}
		else
		{
			TaskDestroy(task);
			task = NULL;
			
			if (ERROR == is_task_repeat)
			{
				res = ERROR;
			}
		}
	}
	
	/* 
	* Return error if it occured, otherwise determine whether run was stopped
	* by SchedulerStop() or because it ran out of tasks.
	*/
	res = (ERROR == res) ? res : (res ^ scheduler->should_stop); 
	
	/* update flags and return value */
	scheduler->should_stop = FALSE; 
	
	return res; 
}

void SchedulerStop(scheduler_ty *scheduler)
{
	/* assert */
	assert(scheduler);
	
	/* set should stop flag to 1 */
	scheduler->should_stop = TRUE;
}

size_t SchedulerSize(const scheduler_ty *scheduler)
{
	/* assert */
	assert(scheduler);
	
	/* return priority queue size */
	return PQueueSize(scheduler->tasks);
}

int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	/* assert */
	assert(scheduler);
	
	/* return priority queue is_empty */
	return PQueueIsEmpty(scheduler->tasks);
}

void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *task = NULL;
	
	/* assert */
	assert(scheduler);
	
	/* pop every value in the queue and free it */
	while(!PQueueIsEmpty(scheduler->tasks))
	{
		task = PQueueDequeue(scheduler->tasks);
		TaskDestroy(task);
	}
}

static int SchedTaskCompare(const void *task1, const void *task2)
{
	assert(task1);
	assert(task2);
	
	return TaskCompare((task_ty *)task1, (task_ty *)task2);
}

static int SchedTaskIsMatch(const void *task, const void *uid)
{
	assert(task);
	assert(uid);
	
	return TaskIsMatch((task_ty *)task, *(uid_ty *)uid);
}

static int UpdateTaskTimes(scheduler_ty *scheduler)
{
	void *task = NULL;
	size_t i = 0;
	
	assert(scheduler);
	
	for (i = 0; i < SchedulerSize(scheduler); ++i)
	{
		task = PQueueDequeue(scheduler->tasks);
		TaskUpdateTime((task_ty *)task);
		if (PQueueEnqueue(scheduler->tasks, task))
		{
			return FAILURE;
		}
	}
	
	return SUCCESS;
}

#ifndef NDEBUG
int DebugUpdateTaskTimes(scheduler_ty *scheduler)
{
	assert(scheduler);
	
	return UpdateTaskTimes(scheduler);
}

ts_ty DequeueAndGetNextTimeToExecution(scheduler_ty *scheduler)
{
	task_ty *task = NULL;
	ts_ty time;
	
	assert(scheduler);
	
	task = PQueueDequeue(scheduler->tasks);
	time = TaskGetExecTime(task);
	
	TaskDestroy(task);
	
	return time;
}
#endif

