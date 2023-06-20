#ifndef __SCHEDTASK_H__
#define __SCHEDTASK_H__

#include "uid.h"

typedef struct task task_ty;
typedef struct timespec ts_ty;

/* Returns 1 if task should repeat, 0 otherwise, -1 if failed */
typedef int (*callback_ty)(void *);

/* Returns NULL if unsuccessful, undefined behaviour if interval is negative */
task_ty *TaskCreate(callback_ty callback, void *params, ts_ty interval);

/* Returns bad UID if task pointer is NULL */
uid_ty TaskGetUID(const task_ty *task);

/* Returns negative if task pointer is NULL */
ts_ty TaskGetExecTime(const task_ty *task);

/* If pointer is NULL, undefined behaviour */
/* Returns 0 for success, failure otherwise */
int TaskUpdateTime(task_ty *task);

/* If pointer is NULL, undefined behaviour */
/* Returns 1 if task should repeat, 0 otherwise */
int TaskRunAction(task_ty *task);

/* If pointer is NULL, undefined behaviour */
void TaskDestroy(task_ty *task);

/* compares exec time-> returns positive if task1 is earlier than task2, 0 if the same, negative if task1 is later than task2 */
int TaskCompare(const task_ty *task1, const task_ty *task2);

/* 1 if task UID is same as given UID, 0 otherwise */ 
int TaskIsMatch(const task_ty *task, const uid_ty uid);

#endif /* __SCHEDTASK_H__ */
