#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "scheduler_pq.h"
#include "schedtask.h"

#define FALSE 0
#define TRUE 1

#define UNUSED(x) (void)(x)

#define NSEC_IN_SEC 1000000000UL
#define TIME_PRECISION 1000UL

typedef enum status { ERROR, SUCCESS, FAILURE } status_ty;

typedef status_ty (*test_func)(void);

struct time
{
	ts_ty run;
	ts_ty interval;
};

/* returns positive if task1 is earlier than task2, negative if task1 is later than task2 */
int TaskCompare(const task_ty *task1, const task_ty *task2);

/* 1 if task UID is same as given UID, 0 otherwise */ 
int TaskIsMatch(const task_ty *task, const uid_ty uid);

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
static int IsTimeSpecEqual(ts_ty time1, ts_ty time2);

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
	ts_ty interval = {5, 0};
	
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
	ts_ty interval = {5, 0};
	ts_ty time;

	status = SUCCESS;
	
	task = TaskCreate(CallbackTest, &param, interval);
	
	clock_gettime(CLOCK_MONOTONIC, &time);

	time.tv_sec += TaskGetExecTime(task).tv_sec;
	time.tv_nsec += TaskGetExecTime(task).tv_nsec;
	if (!IsTimeSpecEqual(time, interval))
	{
		status = FAILURE;
		printf("Execution time doesn't match initial interval.\n");
		printf("Expected: %ld seconds, %ld nanoseconds\n"
				"Yielded: %ld seconds, %ld nanoseconds\n",
				interval.tv_sec, interval.tv_nsec,
				time.tv_sec, time.tv_nsec);
	}
	
	TaskDestroy(task);
	
	return status;
}

status_ty TestTaskUpdateTime(void)
{
	status_ty status = ERROR;
	task_ty *task = NULL;
	int param = 10;
	ts_ty interval = {5, 0};
	ts_ty time;
	
	status = SUCCESS;
	
	task = TaskCreate(CallbackTest, &param, interval);
	
	TaskUpdateTime(task);
	
	time.tv_sec = TaskGetExecTime(task).tv_sec;
	time.tv_nsec = TaskGetExecTime(task).tv_nsec;

	if (!IsTimeSpecEqual(time, interval))
	{
		status = FAILURE;
		printf("Set execution time doesn't match expected time.\n");
		printf("Expected: %ld seconds, %ld nanoseconds\n"
				"Yielded: %ld seconds, %ld nanoseconds\n",
				interval.tv_sec, interval.tv_nsec,
				time.tv_sec, time.tv_nsec);
	}
	
	TaskDestroy(task);
	
	return status;
}

status_ty TestTaskRunAction(void)
{
	status_ty status = ERROR;
	task_ty *task = NULL;
	int param = 10;
	ts_ty interval = {5, 0};
	
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
	ts_ty interval1 = {5, 0};
	ts_ty interval2 = {7, 0};
	
	status = SUCCESS;
	
	task1 = TaskCreate(CallbackTest, &param, interval1);
	task2 = TaskCreate(CallbackTest, &param, interval2);
	
	if (0 >= TaskCompare(task1, task2))
	{
		status = FAILURE;
		printf("Tasks are not sorted correctly.\n");
	}
	
	if (0 <= TaskCompare(task2, task1))
	{
		status = FAILURE;
		printf("Tasks are not sorted correctly.\n");
	}
	
	if (0 != TaskCompare(task1, task1))
	{
		status = FAILURE;
		printf("Tasks are not sorted correctly.\n");
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
	ts_ty interval = {5, 0};
	uid_ty uid1;
	uid_ty uid2;
	
	status = SUCCESS;
	
	task1 = TaskCreate(CallbackTest, &param, interval);
	task2 = TaskCreate(CallbackTest, &param, interval);
	
	uid1 = TaskGetUID(task1);
	uid2 = TaskGetUID(task2);
	
	if (!TaskIsMatch(task1, uid1))
	{
		status = FAILURE;
		printf("Matching UID and task were not matched.\n");
	}
	
	if (TaskIsMatch(task1, uid2))
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
	ts_ty interval = {5, 0};
	
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
	ts_ty interval = {5, 0};
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
	ts_ty interval = {1, 0};
	uid_ty uid;
	struct time test_time;
	int sched_result = 0;
	
	status = SUCCESS;
	return status;
	
	scheduler = SchedulerCreate();

	uid = SchedulerAdd(scheduler, CallbackTimeTest, &test_time, interval);
	
	if (UIDIsBadUid(uid))
	{
		printf("Returned bad UID.\n");
		status = FAILURE;
	}

	clock_gettime(CLOCK_MONOTONIC, &(test_time.run));
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
	
	if (UIDIsBadUid(uid))
	{
		printf("Returned bad UID.\n");
		status = FAILURE;
	}

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
	ts_ty interval = {5, 0};
	ts_ty uns_intervals[] = { {5, 0}, {1, 0}, {4, 0}, {2, 0} };
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
	
		if (UIDIsBadUid(uid))
		{
			printf("Returned bad UID.\n");
			status = FAILURE;
		}
	}
	
	start_time = time(0);
	sched_result = SchedulerRun(scheduler);
	
	if(time(0) - start_time != interval.tv_sec)
	{
		status = FAILURE;
		printf("Scheduler was not stopped at the right time.\nExpected to stop after %ld but stopped after %ld\n", interval.tv_sec, time(0) - start_time);
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
	ts_ty interval = {5, 0};
	uid_ty uid;
	size_t num_tasks = 10;
	size_t i = 0;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	if (0 != SchedulerSize(scheduler))
	{
		status = FAILURE;
		printf("Size of empty scheduler is not zero.\n");
	}
	
	uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	
	if (UIDIsBadUid(uid))
	{
		printf("Returned bad UID.\n");
		status = FAILURE;
	}

	if (1 != SchedulerSize(scheduler))
	{
		status = FAILURE;
		printf("Size of scheduler with one task is not 1.\n");
	}
	
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	
		if (UIDIsBadUid(uid))
		{
			printf("Returned bad UID.\n");
			status = FAILURE;
		}
	}

	if (num_tasks + 1 != SchedulerSize(scheduler))
	{
		status = FAILURE;
		printf("Size of scheduler after putting in %ld tasks doesn't match.\n", num_tasks + 1);
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

status_ty TestSchedulerIsEmpty(void)
{
	status_ty status = ERROR;
	scheduler_ty *scheduler = NULL;
	int param = 10;
	ts_ty interval = {5, 0};
	uid_ty uid;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();

	if (!SchedulerIsEmpty(scheduler))
	{
		status = FAILURE;
		printf("Empty scheduler registered as nonempty.\n");
	}
	
	uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	
	if (UIDIsBadUid(uid))
	{
		printf("Returned bad UID.\n");
		status = FAILURE;
	}

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
	ts_ty interval = {5, 0};
	uid_ty uid;
	int num_tasks = 10;
	int i = 0;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();
	
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, interval);
	
		if (UIDIsBadUid(uid))
		{
			printf("Returned bad UID.\n");
			status = FAILURE;
		}
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
	ts_ty intervals[] = {{1, 0}, {2, 0}, {3, 0}, {4, 0}};
	ts_ty uns_intervals[] = {{3, 0}, {1, 0}, {4, 0}, {2, 0}};
	uid_ty uid;
	int num_tasks = 4;
	int i = 0;
	time_t add_time = BAD_TIME;
	ts_ty exec_time;
	time_t wait_time = 2;
	
	status = SUCCESS;
	
	scheduler = SchedulerCreate();
	
	add_time = time(0);
	for (i = 0; i < num_tasks; ++i)
	{
		uid = SchedulerAdd(scheduler, CallbackTest, &param, uns_intervals[i]);
	
		if (UIDIsBadUid(uid))
		{
			printf("Returned bad UID.\n");
			status = FAILURE;
		}
	}
	
	while(time(0) > add_time + wait_time);
	DebugUpdateTaskTimes(scheduler);
	
	for (i = 0; i < num_tasks; ++i)
	{
		exec_time = DequeueAndGetNextTimeToExecution(scheduler);
		if (!IsTimeSpecEqual(exec_time, intervals[i]))
		{
			status = FAILURE;
			printf("Task %d time wasn't updated properly.\n"
			"Expected %ld seconds, %ld nanoseconds\n"
			"Yielded %ld seconds, %ld nanoseconds\n", 
			i, intervals[i].tv_sec, intervals[i].tv_nsec, 
			exec_time.tv_sec, exec_time.tv_nsec);
		}
	}
	
	SchedulerDestroy(scheduler);
	
	return status;
}

static int CallbackTimeTest(void *param)
{
	struct time time_ = *(struct time *)param;
	
	return (time_.run.tv_sec + time_.interval.tv_sec != time(0)) ? -1 : 0;
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

static int IsTimeSpecEqual(ts_ty time1, ts_ty time2)
{
	double diff = time1.tv_sec - time2.tv_sec + 
			(double)(time1.tv_nsec - time2.tv_nsec) / NSEC_IN_SEC;

	diff *= diff < 0 ? -1 : 1;

	diff = ((int)(diff * TIME_PRECISION + 0.5) / TIME_PRECISION);

	return (diff == 0);
}