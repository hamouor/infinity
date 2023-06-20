#include <stdio.h>
#include "p_queue.h"

int compare(const void *data1, const void *data2); 

int match(const void *data1, const void *data2);

int main()
{
    pqueue_ty* new = NULL;
    int arr[] = {8, 6, 1, 3, 10, 6};
    int a = 3;
    void* param = NULL;

    param = (void*)&a;
    new = PQueueCreate(compare);

    PQueueEnqueue(new, (void*)&arr[0]);
    PQueueEnqueue(new, (void*)&arr[1]);
    PQueueEnqueue(new, (void*)&arr[2]);
    PQueueEnqueue(new, (void*)&arr[3]);

    printf("should be 8:%d\n", *(int*)PQueueDequeue(new));
    printf("should be 6:%d\n", *(int*)PQueuePeek(new));
    printf("should be 6:%d\n", *(int*)PQueueDequeue(new));
    printf("not empty ISEMPTY sais:%d\n", PQueueIsEmpty(new));
    printf("should be 2:%ld\n",PQueueSize(new));
    PQueueClear(new);
    printf("is empty ISEMPTY sais:%d\n", PQueueIsEmpty(new));

    PQueueEnqueue(new, (void*)&arr[0]);
    PQueueEnqueue(new, (void*)&arr[1]);
    PQueueEnqueue(new, (void*)&arr[2]);
    PQueueEnqueue(new, (void*)&arr[3]);

    printf("should be 3:%d\n", *(int*)PQueueErase(new, match, param));  




    PQueueDestroy(new);

    return 0;
}

int compare(const void *data1, const void *data2)
{
    if (*(int*)data1 > *(int*)data2)
    {
        return 1;
    }
    else if (*(int*)data1 < *(int*)data2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int match(const void *data1, const void *data2)
{
    return (*(int*)data1 % *(int*)data2 == 0);
}