#include<stdio.h>

#include"scheduler.h"

int task1(void* arg);
int task2(void* arg);

int main()
{
    int repeats = 3;
    scheduler_ty* testsched = NULL;
    uid_ty testuid = bad_uid;

    printf("should be 1 %d\n", UIDIsBadUid(testuid));

    testsched = SchedulerCreate();
    printf("sched is empty IsEmpty returns:%d\n", SchedulerIsEmpty(testsched));
    testuid = SchedulerAdd(testsched, task1, (void*)&repeats, 3);
    printf("should be 0 %d\n", UIDIsBadUid(testuid));

    testuid = SchedulerAdd(testsched, task2, (void*)&repeats, 10);
    SchedulerRemove(testsched,testuid);
    printf("should be 0 %d\n", UIDIsBadUid(testuid));
    printf("sched isnt empty IsEmpty returns:%d\n", SchedulerIsEmpty(testsched));
    printf("sched size of 1 Size returns:%ld\n", SchedulerSize(testsched));
    SchedulerRun(testsched);
    SchedulerDestroy(testsched);
    printf("ani gam PO\n");
    return 0;
}

int task1(void* arg)
{
    printf("ani PO %d\n", *(int*)arg);
    --(*(int*)arg);
    return !!(*(int*)arg);
}

int task2(void* arg)
{
    printf("im gonna stop this scheduler");
    return -1;
}
