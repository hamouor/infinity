#ifndef __SHARED_SCHED_H__
#define __SHARED_SCHED_H__

/******************************************************************************/
/*			Shared Scheduler Watchdog           		     */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION: Shared scheduler api for the parent thread and the child process.
* AUTHOR:
* REVIEWER:
* DATE:
* VERSION:
*******************************************************************************/

/* SIGUSR1 signals: "im alive" to the other process */
/* SIGUSR2 signals: "stop" to the other process */


/*******************************************************************************
* Function: create scheduler for the calling process with 2 added tasks:
            - "message" task.
            - "check message" task.
            then run the scheduler untill stop signal arrives.
* Arguments:
* Return value: 0 on Succsess, 1 on failure
* Notes: returns 1 if failed to create scheduler or the tasks.
*******************************************************************************/
int SSRun(void);

#endif /* __SHARED_SCHED_H__ */