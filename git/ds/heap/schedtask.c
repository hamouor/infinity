#include <assert.h>
#include <stdlib.h> /*malloc(), free()*/
#include<time.h>    /*time()*/

#include"schedtask.h"

struct task 
{
    uid_ty          id;
    callback_ty     action;
    void           *ac_param;
    int             interval;           /* represented in seconds */
    time_t          exe_time;
};

task_ty *TaskCreate(callback_ty callback, void *param, int interval)
{
    task_ty* new_t = NULL;
    /* assert */
    assert(callback);

    /* allocate memory */
    new_t = (task_ty*)malloc(sizeof(task_ty));
    /* handle failed alloc */
    if (new_t == NULL)
    {
        return NULL;
    }
    /* generate new uid */ 
    new_t->id = UIDGenerate();
    if(UIDIsBadUid(new_t->id))
    {
        free(new_t);
        return NULL;
    }
    /* init task members */
    new_t->action = callback;
    new_t->ac_param = param;
    new_t->interval = interval;
    new_t->exe_time = (time_t)0;
    /* return new task */
    return new_t;
}
void TaskDestroy(task_ty *task_ty)
{
    /* assert */
    assert(task_ty);
    /* free task & compare to NULL */
    free(task_ty);
}

void TaskSetExecTime(task_ty *task, time_t time) /*think weather bad time merits a check or assert*/
{
    /* assert */
    assert(task && time != (time_t)-1);
    /* return updated task */
    task->exe_time = time + (time_t)task->interval;
}

uid_ty TaskGetUID(task_ty *task)
{
    assert(task);

    return task->id;
}

time_t TaskGetExecTime(task_ty *task)
{
    assert(task);

    return task->exe_time;
}

int TaskRunAction(task_ty *task)
{
    assert(task);

    return (task->action)(task->ac_param);
}

int TaskIsMatch(task_ty *task1, uid_ty *id)
{
    return UIDIsEqual( TaskGetUID(task1), *id );
}