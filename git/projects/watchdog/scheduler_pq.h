/*******************************************************************************
*		                			SCHEDULER                                                  
*******************************************************************************/
/*******************************************************************************
* DESCRIPTION: 		A task scheduler. Supports scheduling callback functions to
* 					be performed after a given interval of time in seconds, and
* 					repeating them if needed.
* AUTHOR: HRD24
* REVIEWER:
* DATE: 26/04/2022
* VERSION: 0.1
* Time of last Change: 15:22
*******************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */
#include "uid.h"
#include "schedtask.h"

typedef struct scheduler scheduler_ty;

/* Returns 1 if task should repeat, 0 otherwise */
typedef int (*sched_callback_ty)(void *);

/*******************************************************************************
* Return value:		NULL if creation not successful.
* Notes:			A created scheduler MUST be destroyed using 
* 					SchedulerDestroy(), otherwise there will be a memory leak!
* Complexity:		O(1)
*******************************************************************************/
scheduler_ty *SchedulerCreate(void);

/*******************************************************************************
* Notes:			Undefined behaviour if pointer to scheduler is NULL.
* Complexity:		O(n)
*******************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler);

/*******************************************************************************
* Function:			Adds a task to the scheduler with a time interval for 
* 					performing the task.
* Arguments:		- A pointer to a scheduler
* 					- A pointer to the callback to be performed. 
* 					- Parameters for the callback
* 					- The time in seconds after which the task should be 
* 					executed.
* Return value:		A UID describing the added task, bad UID if failed.
* Notes:			Undefined behaviour if pointer to scheduler is NULL, pointer
* 					to callback is NULL, or interval is negative.
* Complexity:		O(number of tasks already in scheduler)
*******************************************************************************/
uid_ty SchedulerAdd(scheduler_ty *scheduler, sched_callback_ty callback, void *param, ts_ty interval);

/*******************************************************************************
* Arguments:		A pointer to a scheduler, the UID of the task to be removed.
* Return value:		0 if removed successfully, 1 if task not found.
* Notes:			Undefined behaviour if pointer to scheduler is NULL or UID 
* 					is bad.
* Complexity:		O(n)
*******************************************************************************/
int SchedulerRemove(scheduler_ty *scheduler, uid_ty task_id);

/*******************************************************************************
* Function:			Starts the scheduler and runs the tasks it was given.
* Return value:		0 if ran out of tasks, 1 if stopped, -1 if a function failed
* 					or there was an error getting current time.
* Notes:			Undefined behaviour if pointer to scheduler is NULL.
* 					This function will block any other input until the scheduler
* 					is stopped using SchedulerStop() or it ran out of scheduled
* 					tasks!
* 					Running a previously stopped or a currently running 
* 					scheduler is undefined.
* Complexity:		O(n)
*******************************************************************************/
int SchedulerRun(scheduler_ty *scheduler);

/*******************************************************************************
* Function:			Stops the scheduler from executing any further tasks.
* Notes:			Undefined behaviour if pointer to scheduler is NULL or 
* 					scheduler is not running.
* Complexity:		O(1)
*******************************************************************************/
void SchedulerStop(scheduler_ty *scheduler);

/*******************************************************************************
* Notes:			Undefined behaviour if pointer to scheduler is NULL.
* Complexity:		O(n)
*******************************************************************************/
size_t SchedulerSize(const scheduler_ty *scheduler);

/*******************************************************************************
* Return value:		1 if empty, 0 otherwise.
* Notes:			Undefined behaviour if pointer to scheduler is NULL.
* Complexity:		O(1)
*******************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler);

/*******************************************************************************
* Notes:			Undefined behaviour if pointer to scheduler is NULL.
* Complexity:		O(n)
*******************************************************************************/
void SchedulerClear(scheduler_ty *scheduler);

#ifndef NDEBUG
int DebugUpdateTaskTimes(scheduler_ty *scheduler);
ts_ty DequeueAndGetNextTimeToExecution(scheduler_ty *scheduler);
#endif

#endif /* __SCHEDULER_H__ */
