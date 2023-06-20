#include"heap.h"
#include"p_queue.h"

#include <stdlib.h>

struct p_queue
{
    heap_ty *heap;
};

pqueue_ty *PQueueCreate(PQDataCompare_ty prior_func)
{
    pqueue_ty *new = NULL;

    new = (pqueue_ty*)malloc(sizeof(pqueue_ty));

    new->heap = HeapCreate(prior_func);

    return new;
}

void PQueueDestroy(pqueue_ty *pqueue)
{
    HeapDestroy(pqueue->heap);
    free(pqueue);
}

int PQueueEnqueue(pqueue_ty *pqueue, void *data)
{
    return HeapPush(pqueue->heap, data);
}

void *PQueueDequeue(pqueue_ty *pqueue)
{
    return HeapPop(pqueue->heap);
}

void *PQueuePeek(const pqueue_ty *pqueue)
{
    return HeapPeek(pqueue->heap);
}

int PQueueIsEmpty(const pqueue_ty *pqueue)
{
    return HeapIsEmpty(pqueue->heap);
}

size_t PQueueSize(const pqueue_ty *pqueue)
{
    return HeapSize(pqueue->heap);
}

void PQueueClear(pqueue_ty *pqueue)
{
    while(!HeapIsEmpty(pqueue->heap))
    {
        HeapPop(pqueue->heap);
    }
}

void *PQueueErase(pqueue_ty *pqueue, PQIsMatch_ty is_match, void *param)
{
    return HeapRemove(pqueue->heap, is_match, param);
}