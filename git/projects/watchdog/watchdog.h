#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

/******************************************************************************/
/*			Watch Dog           				                              */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION: create and control a "watchdog" which monitors the functunality
		of the caller process. If the caller process stops working the watchdog
        restart it.
        This API uses SIGUSR1 and SIGUSR2.
        
* AUTHOR:	fun c
* REVIEWER:	wade willson
* DATE:
* VERSION:
*******************************************************************************/

/*******************************************************************************
* Function: Create a watchdog handler and enable it
* Arguments: char *argv[] recieved from the main function
* Return value: 0 on Success, 1 on Failure
*******************************************************************************/
int WatchdogEnable(char *argv[]);

/*******************************************************************************
* Function: Stops the watchdog timer.
* Return value: 0 on SUCCESS, 1 on FAILURE
*******************************************************************************/
int WatchdogDisable(void);

#endif /* __WATCHDOG_H__ */
