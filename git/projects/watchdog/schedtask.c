#include <assert.h> 	/* assert()				 */
#include <stdlib.h> 	/* malloc(), free()		 */
#include <time.h> 		/* time() 				 */

#include "schedtask.h"

#define NSEC_IN_SEC 1000000000L

struct task
{
	uid_ty uid;
	callback_ty callback;
	void *params;
	ts_ty interval;
	ts_ty exec_time;
};

task_ty *TaskCreate(callback_ty callback, void *params, ts_ty interval)
{
	task_ty *task = NULL;
	
	assert(callback);
	
	
	task = (task_ty *)malloc(sizeof(task_ty));
	
	if (!task)
	{
		return NULL;
	}
	
	task->uid = UIDGenerate();
	task->callback = callback;
	task->params = params;
	task->interval = interval;
	task->exec_time = interval;
	
	return task;
}

uid_ty TaskGetUID(const task_ty *task)
{
	return ((NULL == task) ? bad_uid : task->uid);
}

ts_ty TaskGetExecTime(const task_ty *task) 
{
	ts_ty current_time = {0};
	ts_ty result = {0};
	
	if (!task || clock_gettime(CLOCK_MONOTONIC, &current_time))
	{
		return current_time;
	}

	if ((task->exec_time.tv_nsec - current_time.tv_nsec) < 0) 
	{
		result.tv_sec = task->exec_time.tv_sec - current_time.tv_sec - 1;
		result.tv_nsec = task->exec_time.tv_nsec - current_time.tv_nsec + NSEC_IN_SEC;
	} 
	else 
	{
		result.tv_sec = task->exec_time.tv_sec - current_time.tv_sec;
		result.tv_nsec = task->exec_time.tv_nsec - current_time.tv_nsec;
	}

	return result;
}

int TaskUpdateTime(task_ty *task)
{
	ts_ty current_time = {0};

	if (!task || clock_gettime(CLOCK_MONOTONIC, &current_time))
	{
		return 1;
	}
	else
	{
		task->exec_time.tv_nsec = current_time.tv_nsec + task->interval.tv_nsec;
		task->exec_time.tv_sec = current_time.tv_sec + task->interval.tv_sec;
		
		if (task->exec_time.tv_nsec > NSEC_IN_SEC)
		{
			task->exec_time.tv_nsec -= NSEC_IN_SEC;
			++task->exec_time.tv_sec;
		}

		return 0;
	}
}


int TaskRunAction(task_ty *task)
{
	assert(task);
	
	return (task->callback(task->params));
}


void TaskDestroy(task_ty *task)
{
	assert(task);
	task->callback = NULL;
	task->params = NULL;
	
	free(task);
}

int TaskCompare(const task_ty *task1, const task_ty *task2)
{
	double diff = 0.0;	

	assert(task1);
	assert(task2);

	diff = task2->exec_time.tv_sec - task1->exec_time.tv_sec + 
			(double)(task2->exec_time.tv_nsec - task1->exec_time.tv_nsec) / NSEC_IN_SEC;
	
	return (diff < 0) ? -1 : (diff > 0) ? 1 : 0;
}

int TaskIsMatch(const task_ty *task, const uid_ty uid)
{
	assert(task);
	
	return UIDIsEqual(uid, task->uid);
}
