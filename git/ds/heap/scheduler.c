#include <stdlib.h> /*malloc(), free()*/
#include <assert.h>
#include<time.h>
#include<stdio.h>

#include"scheduler.h"
#include"p_queue.h"
#include "schedtask.h"



struct scheduler
{
    pqueue_ty *task_q;
    int ranotstopped;
    int running;
};

static int Time_Sort(const void *data1, const void *data2);

static int TaskUIDComp(const void* task, const void* id);

static pqueue_ty *SchedToPQ(scheduler_ty *scheduler);

static void SchedulerExeTimeUpD(scheduler_ty *scheduler);

scheduler_ty *SchedulerCreate(void)
{
    scheduler_ty *new = NULL;

    new = (scheduler_ty*)malloc(sizeof(scheduler_ty));

    if ( new == NULL )
    {
        return NULL;
    }

    new->task_q = PQueueCreate(Time_Sort);

    if ( new->task_q == NULL)
    {
        free(new);
        return NULL;
    }

    new->ranotstopped = 0;
    new->running = 0;

    return new;
}

void SchedulerDestroy(scheduler_ty *scheduler)/*pqdestroy does not use task destroy. need to add (clear)*/
{
    assert(scheduler);

    SchedulerClear(scheduler);
    PQueueDestroy(scheduler->task_q);
    scheduler->task_q = NULL;

    free(scheduler);
}

uid_ty SchedulerAdd(scheduler_ty *scheduler, callback_ty callback, void *param, int interval)
{
    task_ty* new_t = NULL;
    
    /*asserts*/
    assert(scheduler && callback);
    
    /*generate and init new task node*/
    new_t = TaskCreate(callback, param, interval);
    
    if( new_t == NULL)
    {
        return bad_uid;
    }
    
    /*add new task node to task_q*/
    if (!PQueueEnqueue(SchedToPQ(scheduler), (void*)new_t))
    {
        /*return task uid*/
       return TaskGetUID(new_t);
    }
    
    TaskDestroy(new_t);
    return bad_uid;
}

int SchedulerRemove(scheduler_ty *scheduler, uid_ty task_id)
{
    task_ty *task = NULL;
    /*asserts*/
    assert(scheduler);/* && !UIDIsBadUid(task_id));*/
    
    /*find task with given task id*/
    /*remove found task from task_q*/
    task = PQueueErase(SchedToPQ(scheduler), TaskUIDComp, (void*)&task_id);

    if (task)/*return !*/
    {
        TaskDestroy(task);
        /*if not found return 1 if found and removed return 0*/
        return 0;
    }
    return 1;
}

int SchedulerRun(scheduler_ty *scheduler)
{
    task_ty* runner = NULL;
    int runstat = 0;
    time_t diff = (time_t)0, curr_time = (time_t)0;
    
    /*asserts*/
    assert(scheduler);
    
    if( scheduler->running )
    {
        return 1;
    }
    scheduler->running = 1;
    /*update all tasks time to be current plus interval*/
    SchedulerExeTimeUpD(scheduler);
    
    /*while task list is not empty and stopped flag not 1*/
    while(!SchedulerIsEmpty(scheduler) && !(scheduler->ranotstopped))
    {
        /*while current time is not next node exec time*/
        curr_time = time(0);
        if (curr_time == (time_t)-1)
        {
            SchedulerStop(scheduler);
            break;
        }
    
        runner = (task_ty*)PQueueDequeue(SchedToPQ(scheduler));
        diff = TaskGetExecTime(runner) - curr_time;
        sleep((unsigned int)diff);
        runstat = TaskRunAction(runner);
    
        /*re add task to q according to returned val from task*/
        if(runstat == 1)
        {
            curr_time = time(0);
            if (curr_time == (time_t)-1)
            {
                SchedulerStop(scheduler);
                break;
            }
            TaskSetExecTime(runner, curr_time);
            if(PQueueEnqueue(SchedToPQ(scheduler), (void*)runner))
            {
                SchedulerStop(scheduler);
                break;
            }
        }
        else if( runstat == -1)
        {
            TaskDestroy(runner);
            SchedulerStop(scheduler);
        }
        /*pop next task and run*/
        else if(runstat == 0)
        {
            TaskDestroy(runner);
        }

    }
        
    /*update stop flag on scheduler to 1*/
    scheduler->ranotstopped = -1; /*-1 means ran*/
    return (scheduler->ranotstopped);
}

void SchedulerStop(scheduler_ty *scheduler)
{
    /*asserts*/
    assert(scheduler);
    /*update stop flag on scheduler to 1*/
    scheduler->ranotstopped = 1;/*means stopped*/
}

size_t SchedulerSize(const scheduler_ty *scheduler)
{
    /*asserts*/
    assert(scheduler);

    return PQueueSize(SchedToPQ((scheduler_ty *)scheduler));
}

int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
    /*asserts*/
    assert(scheduler);

    return PQueueIsEmpty(SchedToPQ((scheduler_ty*)scheduler));
}

void SchedulerClear(scheduler_ty *scheduler)/*destroy all tasks*/
{
    task_ty *temp = NULL;  
    size_t len = 0;
    /*asserts*/
    assert(scheduler);

    len = PQueueSize(SchedToPQ(scheduler));
    for(; len > 0; --len)
    {
        temp = (task_ty*)PQueueDequeue(SchedToPQ(scheduler));
        TaskDestroy(temp);
    }
}

static pqueue_ty *SchedToPQ(scheduler_ty *scheduler)
{
    return (scheduler->task_q);
}



static void SchedulerExeTimeUpD(scheduler_ty *scheduler)
{
    time_t curr = time(0);
    task_ty *temp = NULL;  
    size_t len = PQueueSize(SchedToPQ(scheduler));
    
    if(curr != (time_t)-1)
    {
        for(; len > 0; --len)
        {
            temp = (task_ty*)PQueueDequeue(SchedToPQ(scheduler));
            TaskSetExecTime(temp, curr);
            if(PQueueEnqueue(SchedToPQ(scheduler), (void*)temp))
            {
                SchedulerStop(scheduler);
                break;
            }
        }
    }
    else
    {
        SchedulerStop(scheduler);  
    }
}

static int Time_Sort(const void *data1, const void *data2)
{
    time_t t1 = TaskGetExecTime((task_ty*)data1), t2 = TaskGetExecTime((task_ty*)data2);
    if (t1 < t2)
    {
        return 1;
    }
    else if (t1 > t2)
    {
        return -1;
    }
    else
    {
        return 0;
    }/*floating numbers no good*/
}

static int TaskUIDComp(const void* task, const void* id)
{
    return UIDIsEqual(TaskGetUID((task_ty*)task), *(uid_ty*)id);
}

