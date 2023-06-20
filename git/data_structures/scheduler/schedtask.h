#include "uid.h"

/* Returns 1 if task should repeat, 0 otherwise */
typedef int (*callback_ty)(void *);

typedef struct task task_ty;


/* Returns NULL if unsuccessful, undefined behaviour if interval is negative */
/*******************************************************************************
* Function:		Create a new task for scheduler 
* Arguments:	A pointer to the callback (actual task created by the user) to
	be performed. Parameters for the callback. The time in seconds after which 
	the task should be executed.
* Return value:	A Pointer to the new task handler, if creation failed 
	returns NULL.
*******************************************************************************/
task_ty *TaskCreate(callback_ty callback, void *params, int interval);


/* If pointer is NULL, undefined behaviour */
/*******************************************************************************
* Function:		Destroy A created task -free memory
* Arguments:	Pointer to the task.
* Return value:	None. ?? uid? to keep trak on destroyed task uid? 
* Notes:		Undefined behavior- if task is NULL.
*******************************************************************************/
void TaskDestroy(task_ty *task);


/* Returns bad UID if task pointer is NULL */
/*******************************************************************************
* Function:		get the task uid
* Arguments:	Pointer to task.
* Return value:	uid.
* Notes:		Undefined behavior- if task is NULL.
*******************************************************************************/
uid_ty TaskGetUID(task_ty *task);


/* Returns bad time if task pointer is NULL */
/*******************************************************************************
* Function:		get ExecTime value
* Arguments:	Pointer to task.
* Return value:	time_t time value
* Notes:		Undefined behavior- if task is NULL.
*******************************************************************************/
time_t TaskGetExecTime(task_ty *task);


/* If pointer is NULL, undefined behaviour */
/*******************************************************************************
* Function:		setExecTime
* Arguments:	Pointer to task.
* Return value:	return 0 for success and 1 for failure
* Notes:		Undefined behavior- if task is NULL. Undefined behavior- if time
	is bad time
*******************************************************************************/
void TaskSetExecTime(task_ty *task, time_t time);


/* If pointer is NULL, undefined behaviour */
/* Returns 1 if task should repeat, 0 otherwise */
int TaskRunAction(task_ty *task);


int IsMatchTasks(task_ty *task1, task_ty *task2);
