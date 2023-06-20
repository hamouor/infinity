#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "scheduler.h"
#include "schedtask.h"

#define FALSE 0
#define TRUE 1
#define bad_time (time_t)-1

#define UNUSED(x) (void)(x)

typedef enum status { ERROR, SUCCESS, FAILURE } status_ty;

typedef status_ty (*test_func)(void);

struct time
{
	time_t run;
	int interval;
};

status_ty TestTaskGetUID(void);
status_ty TestTaskGetExecTime(void);
status_ty TestTaskUpdateTime(void);
status_ty TestTaskRunAction(void);
status_ty TestTaskCompare(void);
status_ty TestTaskIsMatch(void);
status_ty TestSchedulerCreate(void);
status_ty TestSchedulerAdd(void);
status_ty TestSchedulerRemove(void);
status_ty TestSchedulerRun(void);
status_ty TestSchedulerStop(void);
status_ty TestSchedulerSize(void);
status_ty TestSchedulerIsEmpty(void);
status_ty TestSchedulerClear(void);
status_ty TestDebugUpdateTaskTimes(void);

static int CallbackTest(void *param);
static int CallbackTimeTest(void *time);
static int CallbackRepeatTest(void *num);
static int CallbackStopTest(void *param);

int main(void)
{
	test_func tests[] = {
		TestTaskGetUID,
		TestTaskGetExecTime,
		TestTaskUpdateTime,
		TestTaskRunAction,
		TestTaskCompare,
		TestTaskIsMatch,
		TestSchedulerCreate,
		TestSchedulerAdd,
		TestSchedulerRemove,
		TestSchedulerRun,
		TestSchedulerStop,
		TestSchedulerSize,
		TestSchedulerIsEmpty,
		TestSchedulerClear,
		TestDebugUpdateTaskTimes
	};
	
	char *test_names[] = {
		"TestTaskGetUID",
		"TestTaskGetExecTime",
		"TestTaskUpdateTime",
		"TestTaskRunAction",
		"TestTaskCompare",
		"TestTaskIsMatch",
		"TestSchedulerCreate",
		"TestSchedulerAdd",
		"TestSchedulerRemove",
		"TestSchedulerRun",
		"TestSchedulerStop",
		"TestSchedulerSize",
		"TestSchedulerIsEmpty",
		"TestSchedulerClear",
		"TestDebugUpdateTaskTimes"
	};
	
	int num_tests = sizeof(tests) / sizeof(tests[0]);
	int i = 0;
	status_ty test_result = SUCCESS;
	status_ty unit_result = ERROR;
	
	for (i = 0; i < num_tests; ++i)
	{
		unit_result = tests[i]();
		switch (unit_result)
		{
			case ERROR:
				printf("ERROR in running test %d: %s().\n", i + 1, test_names[i]);
				test_result = ERROR;
				break;
			case SUCCESS:
				break;
			case FAILURE:
				printf("%s() failed! See details above!.\n", test_names[i]);
				test_result = FAILURE;
				break;
			default:
				break;
		}
	}
	
	switch (test_result)
	{
		case ERROR:
			printf("Error in running some tests! See details above!\n");
			test_result = ERROR;
			break;
		case SUCCESS:
			printf("All tests successful!\n");
			break;
		case FAILURE:
			printf("Some tests failed! See details above!.\n");
			test_result = FAILURE;
			break;
		default:
			break;
	}
	
	return 0;
}

status_ty TestTaskGetUID(void)
{
	status_ty status = ERROR;
	task_ty *task = NULL;
	int param = 10;
	int interval = 5;
	
	status = SUCCESS;
	
	task = TaskCreate(CallbackTest, &param, interval);
	
	if (!task)
	{
		status = FAILURE;
		printf("Couldn't create task.\n");
		return status;
	}
	
	if (UIDIsBadUid(TaskGetUID(task)))
	{
		status = FAILURE;
		printf("Task has bad UID.\n");
	}
	
	TaskDestroy(task);
	
	return status;
}

status_ty TestTaskGetExecTime(void)
{
	status_ty status = ERROR;
	task_ty *task = NULL;
	int param = 10;
	int interval = 5;
	
	status = SUCCESS;
	
	task = TaskCreate(CallbackTest, &param, interval);
	
	if (bad_time != TaskGetExecTime(task))
	{
		status = FAILURE;
		printf("Execution time doesn't match initial interval.\n");
	}
	
	TaskDestroy(task);
	
	return status;
}

status_ty TestTaskUpdateTime(void)
{
	status_ty status = ERROR;
	task_ty *task = NULL;
	int param = 10;
	int interval = 5;
	
	status = SUCCESS;
	
	task = TaskCreate(CallbackTest, &param, interval);
	
	TaskUpdateTime(task);
	
	if (interval + time(0) != TaskGetExecTime(task))
	{
		status = FAILURE;
		printf("Set execution time doesn't match expected time.\n");
	}
	
	TaskDestroy(task);
	
	return status;
}

status_ty TestTaskRunAction(void)
{
	status_ty status = ERROR;
	task_ty *task = NULL;
	int param = 10;
	int interval = 5;
	
	status = SUCCESS;
	
	task = TaskCreate(CallbackTest, &param, interval);
	
	if (1 != TaskRunAction(task))
	{
		status = FAILURE;
		printf("Task was supposed to repeat but won't, or failed completely.\n");
	}
	
	param = -10;
	
	if (0 != TaskRunAction(task))
	{
		status = FAILURE;
		printf("Task was not supposed to repeat but will, or failed completely.\n");
	}
	
	param = 0;
	
	if (-1 != TaskRunAction(task))
	{
		status = FAILURE;
		printf("Task was supposed to fail, but didn't?!?!.\n");
	}
	
	TaskDestroy(task);
	
	return status;
}

status_ty TestTaskCompare(void)
{
	status_ty status = ERROR;
	task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	int param = 10;
	int interval1 = 5;
	int interval2 = 7;
	
	status = SUCCESS;
	
	task1 = TaskCreate(CallbackTest, &param, interval1);
	task2 = TaskCreate(CallbackTest, &param, interval2);
	
	if (0 > TaskCompare(task1, task2))
	{
		status = FAILURE;
		printf("1Tasks are not sorted correctly.\n");
	}
	
	if (0 < TaskCompare(task2, task1))
	{
		status = FAILURE;
		printf("2Tasks are not sorted correctly.\n");
	}
	
	if (0 != TaskCompare(task1, task1))
	{
		status = FAILURE;
		printf("3Tasks are not sorted correctly.\n");
	}
	
	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return status;
}

status_ty TestTaskIsMatch(void)
{
	status_ty status = ERROR;
	task_ty *task1 = NULL;
	task_ty *task2 = NULL;
	int param = 10;
	int interval = 5;
	uid_ty uid1;
	uid_ty uid2;
	
	status = SUCCESS;
	
	task1 = TaskCreate(CallbackTest, &param, interval);
	task2 = TaskCreate(CallbackTest, &param, interval);
	
	uid1 = TaskGetUID(task1);
	uid2 = TaskGetUID(task2);
	
	if (!TaskIsMatch(task1, &uid1))
	{
		status = FAILURE;
		printf("Matching UID and task were not matched.\n");
	}
	
	if (TaskIsMatch(task1, &uid2))
	{
		status = FAILURE;
		printf("Non-matching UID and task were matched.\n");
	}
	
	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return status;
}

status_ty TestSchedulerCreate(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();
	
	if (!scheduler)
	{
		status = FAILURE;
		printf("Failed to create scheduler.\n");
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestSchedulerAdd(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	int interval = 5;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	if (UIDIsBadUid(SchedulerAdd(scheduler, CallbackTest, &param, interval)))
	{
		status = FAILURE;
		printf("Failed to add task to scheduler.\n");
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestSchedulerRemove(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	int interval = 5;
	uid_ty uid;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	
	if (SchedulerRemove(scheduler, uid))
	{
		status = FAILURE;
		printf("Failed to remove task from scheduler.\n");
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestSchedulerRun(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 3;
	int interval = 1;
	uid_ty uid;
	struct time test_time;
	int sched_result = 0;
	
	status = SUCCESS;
	return status;
	
	scheduler = SchedulerCreate();

	uid = SchedulerAdd(scheduler, CallbackTimeTest, &test_time, interval);
	
	test_time.run = time(0);
	test_time.interval = interval;
	
	sched_result = SchedulerRun(scheduler);
	if(1 == sched_result)
	{
		status = FAILURE;
		printf("Scheduler was stopped by Stop() even though it wasn't supposed to.\n");
	}
	else if(-1 == sched_result)
	{
		status = FAILURE;
		printf("Error in running scheduler.\n");
	}
	
	SchedulerDestroy(scheduler);
	
	scheduler = SchedulerCreate();

	uid = SchedulerAdd(scheduler, CallbackRepeatTest, &param, interval);
	sched_result = SchedulerRun(scheduler);
	
	if (0 != param)
	{
		status = FAILURE;
		printf("Repeating function didn't work.\n");
	}
	
	SchedulerDestroy(scheduler);
	
}

status_ty TestSchedulerStop(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int interval = 5;
	int uns_intervals[] = { 5, 1, 4, 2 };
	uid_ty uid;
	int num_tasks = 4;
	int i = 0;
	int sched_result = 0;
	int param = -5;
	time_t start_time;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	uid = SchedulerAdd(scheduler, CallbackStopTest, scheduler, interval);
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, uns_intervals[i]);
	}
	
	start_time = time(0);
	sched_result = SchedulerRun(scheduler);
	
	if(time(0) - start_time != interval)
	{
		status = FAILURE;
		printf("Scheduler was not stopped at the right time.\nExpected to stop after %d but stopped after %ld\n", interval, time(0) - start_time);
	}
	
	if(0 == sched_result)
	{
		status = FAILURE;
		printf("Scheduler was stopped because it was empty even though it was supposed to be stopped by Stop().\n");
	}
	else if(-1 == sched_result)
	{
		status = FAILURE;
		printf("Error in running scheduler.\n");
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestSchedulerSize(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	int interval = 5;
	uid_ty uid;
	int num_tasks = 10;
	int i = 0;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	if (0 != SchedulerSize(scheduler))
	{
		status = FAILURE;
		printf("Size of empty scheduler is not zero.\n");
	}
	
	uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);

	if (1 != SchedulerSize(scheduler))
	{
		status = FAILURE;
		printf("Size of scheduler with one task is not 1.\n");
	}
	
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	}

	if (num_tasks + 1 != SchedulerSize(scheduler))
	{
		status = FAILURE;
		printf("Size of scheduler after putting in %d tasks doesn't match.\n", num_tasks + 1);
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestSchedulerIsEmpty(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	int interval = 5;
	uid_ty uid;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	if (!SchedulerIsEmpty(scheduler))
	{
		status = FAILURE;
		printf("Empty scheduler registered as nonempty.\n");
	}
	
	uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);

	if (SchedulerIsEmpty(scheduler))
	{
		status = FAILURE;
		printf("Nonempty scheduler registered as empty.\n");
	}
	
	SchedulerDestroy(scheduler);

	return status;
}

status_ty TestSchedulerClear(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	int interval = 5;
	uid_ty uid;
	int num_tasks = 10;
	int i = 0;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();
	
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	}

	if (SchedulerIsEmpty(scheduler))
	{
		status = FAILURE;
		printf("Couldn't add tasks for scheduler to clear.\n");
	}
	
	SchedulerClear(scheduler);

	if (!SchedulerIsEmpty(scheduler))
	{
		status = FAILURE;
		printf("Scheduler is not empty after clearing.\n");
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestDebugUpdateTaskTimes(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	int intervals[] = { 1, 2, 3, 4 };
	int uns_intervals[] = { 3, 1, 4, 2 };
	uid_ty uid;
	int num_tasks = 4;
	int i = 0;
	time_t add_time = bad_time;
	int exec_time = 0;
	time_t new_time = bad_time;
	time_t wait_time = 2;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();
	
	add_time = time(0);
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, uns_intervals[i]);
	}
	
	while(time(0) > add_time + wait_time);
	
	new_time = time(0);

	SchedulerDestroy(scheduler);
	
	return status;
}

static int CallbackTimeTest(void *param)
{
	struct time time_ = *(struct time *)param;
	
	return (time_.run + time_.interval != time(0)) ? -1 : 0;
}

static int CallbackRepeatTest(void *num)
{
	--(*(int *)num);
	
	return *(int *)num > 0;
}

static int CallbackStopTest(void *param)
{
	SchedulerStop((scheduler_ty *)param);
	
	return 0;
}

static int CallbackTest(void *param)
{
	if (*(int *)param > 0)
	{
		return 1;
	}
	else if (*(int *)param < 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
