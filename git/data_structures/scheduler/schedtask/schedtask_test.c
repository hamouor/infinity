#include <stdio.h>	/* printf			*/
#include <string.h>	/* strcat, strlen	*/
#include <stdlib.h>	/* malloc, free		*/
#include <time.h>
#include "schedtask.h"
#include "uid.h"

#define UNUSED(x) (void)(x)
/*
#define BAD_TIME (time_t) -1 

#define ERROR -999
#define BAD 1

#define REPEAT 1
#define NO_REPEAT 0

#define MATCH 1
#define NOT_MATCH 0
*/
#define STR_MAX 150

typedef struct 
{
	int x;
	int y;
	int z;
	int i;

}int_param_ty;

typedef struct 
{
	char *str1;
	int length1;
	char *str2;
	char *str3;
	char *str4;

}str_param_ty;

enum bool2 {repeat = 1, no_repeat = 0}; 
enum bool1 {match = 1, not_match = 0}; 
enum numbers {error = -999, baduid = 1, bad_time = (time_t)-1};

/* test function */
void TestSchedTask(void);
static void TestTaskGetUID(task_ty *task);
static void TestTaskGetExecTime(task_ty *task, time_t expc_time);
static void TestTaskSetExecTime(task_ty *task, int expc_interval);
static void TestTaskRunAction(task_ty *task, int expc_ret);
static void TestTaskIsMatch(const void *task, const void *uid, int expc_match);

/* tasks function */
int MultiplyFunc(void *param);
int PrintHelloFunc(void *param);
int StrCatFunc(void *param);

int main(void)
{
	TestSchedTask();

	return 0;
}


void TestSchedTask(void)
{

	task_ty *multiply_task1;
	task_ty *multiply_task2;
	task_ty *print_task1;
	task_ty *strcat_task1;
	
	int_param_ty int_param1 = {2, 3, 4, 0};
	int_param_ty int_param2 = {5, 5, 6, 0};
	int_param_ty int_param3 = {3, 0, 0, 0};
	str_param_ty str_param1 = {NULL, STR_MAX, "VENI ", "VIDI ", "VICI "}; 
	
	uid_ty multiply_task1_uid;
	uid_ty multiply_task2_uid;
	
	int interval_arr[] = {10, 5, 1, 20, 30};

	time_t curr_time = 0;
	
	int i = 0; 
	

	/*----- CREATE TASK 1: MULTIPLY TASK -------------------------------------*/
	
	multiply_task1 = TaskCreate(MultiplyFunc, &int_param1, interval_arr[0]);
	
	TestTaskGetUID(multiply_task1);
	
	TestTaskGetExecTime(multiply_task1, 0);
	
	TestTaskSetExecTime(multiply_task1, interval_arr[0]);
	
	for(i = 0; int_param1.z > i; ++i)
	{
		TestTaskRunAction(multiply_task1, repeat);
	}
	
	TestTaskRunAction(multiply_task1, no_repeat);
	
	curr_time = TaskGetExecTime(multiply_task1);
	
	TestTaskGetExecTime(multiply_task1, curr_time);
	
	
	
	/*----- CREATE TASK 2: MULTIPLY TASK -------------------------------------*/
	
	multiply_task2 = TaskCreate(MultiplyFunc, &int_param2, interval_arr[1]);
	
	TestTaskGetUID(multiply_task2);
	
	TestTaskGetExecTime(multiply_task2, 0);
	
	TestTaskSetExecTime(multiply_task2, interval_arr[1]);
	
	for(i = 0; int_param2.z > i; ++i)
	{
		TestTaskRunAction(multiply_task2, repeat);
	}
	
	TestTaskRunAction(multiply_task2, no_repeat);
	
	multiply_task1_uid = TaskGetUID(multiply_task1);
	multiply_task2_uid = TaskGetUID(multiply_task2);
	
	TestTaskIsMatch(multiply_task1, &multiply_task1_uid, match);
	TestTaskIsMatch(multiply_task2, &multiply_task2_uid, match);
	TestTaskIsMatch(multiply_task1, &multiply_task2_uid, not_match);
	TestTaskIsMatch(multiply_task2, &multiply_task1_uid, not_match);

	
	/*----- CREATE TASK 3: PRINT TASK ----------------------------------------*/
	
	print_task1 = TaskCreate(PrintHelloFunc, &int_param3, interval_arr[2]);
	
	for(i = 0; int_param3.x > i; ++i)
	{
		TestTaskRunAction(print_task1, repeat);
	}
	
	TestTaskRunAction(print_task1, no_repeat);
	

	/*----- CREATE TASK 4: STRCAT TASK ---------------------------------------*/
	
	strcat_task1 = TaskCreate(StrCatFunc, &str_param1, interval_arr[3]);
	
	TestTaskRunAction(strcat_task1, no_repeat);
	
	
	/*---- DESTROY ALL TASKS -------------------------------------------------*/
	
	TaskDestroy(multiply_task1);
	TaskDestroy(multiply_task2);
	TaskDestroy(print_task1);
	TaskDestroy(strcat_task1);
}


static void TestTaskGetUID(task_ty *task)
{
	uid_ty task_uid;
	
	task_uid = TaskGetUID(task);
	
	if(baduid == UIDIsBadUid(task_uid))
	{
		printf("is_bad is BAD =(\n");
	}
}


static void TestTaskGetExecTime(task_ty *task, time_t expc_time)
{
	time_t exec_time = 0;
	
	exec_time = TaskGetExecTime(task);

	if(expc_time != exec_time)
	{
		printf("problem with TaskGetExecTime =(.. exec_time is %ld, and expc_time is %ld\n", exec_time, expc_time);
	}	
}


static void TestTaskSetExecTime(task_ty *task, int expc_interval)
{
	time_t expc_time = 0; 
	time_t curr_time = 0;
	
	curr_time = time(&curr_time);
	if(bad_time == curr_time)
	{
		printf("problem with time function, time == BAD_TIME\n");
	}

	TaskSetExecTime(task, curr_time);
	
	expc_time = curr_time + expc_interval;
	TestTaskGetExecTime(task, expc_time);
}


static void TestTaskRunAction(task_ty *task, int expc_ret)
{
	int ret_run = error;
	
	ret_run = TaskRunAction(task);
	
	if(expc_ret != ret_run)
	{
		printf("problem with TaskRunAction, should return %d (1 is REPEAT, 0 NO_REPEAT)\n", expc_ret);
		printf("And TaskRunAction return %d\n", ret_run);
	}
}


static void TestTaskIsMatch(const void *task, const void *uid, int expc_match)
{
	int ret_match = error;
	
	ret_match = TaskIsMatch((task_ty*)task, (uid_ty*)uid);
	
	if(expc_match != ret_match)
	{
		printf("problem with TaskIsMatch, expc_match is %d and ret_match is %d\n", expc_match, ret_match);
	}
}


/* Task func of type callback_ty. Returns 1 if task should repeat, 0 otherwise */
int MultiplyFunc(void *param)
{
	int_param_ty *parameters = (int_param_ty *)param;
	
	while(parameters->z > parameters->i)
	{
		printf("x is now %d\n", parameters->x);
		parameters->x *= parameters->y;
		++parameters->i;
		
		return repeat;
	} 
	
	return no_repeat;
}


int PrintHelloFunc(void *param)
{
	int_param_ty *parameters = (int_param_ty *)param;
	
	while(parameters->x > parameters->i)
	{
		printf("\n	# # ### #   #    ##   \n");
		printf("	### ##  #   #   #  #  \n");
		printf("	# # ### ### ###  ##  # # #\n");
		printf("\n");
		
		++parameters->i;
		return repeat;
	} 
	
	return no_repeat;
}


int StrCatFunc(void *param)
{
	str_param_ty *parameters = (str_param_ty *)param;
	/*char *str1_ptr = parameters->str1;*/
	parameters->str1 = (char *)malloc(sizeof(char) * parameters->length1);
	if(NULL == parameters->str1)
	{
		return no_repeat;
	}
	
	*parameters->str1 = '\0';
	parameters->str1 = strcat(parameters->str1, parameters->str2);
	parameters->str1 = strcat(parameters->str1, parameters->str3);
	parameters->str1 = strcat(parameters->str1, parameters->str4);
	
	printf("\n%s\n\n", parameters->str1);
	
	free(parameters->str1);
	parameters->str1 = NULL;
	
	return no_repeat;
}






