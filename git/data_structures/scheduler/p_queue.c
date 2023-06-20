#include <assert.h>
#include <stdlib.h>     /*malloc()  free()*/

#include "p_queue.h"
#include "sorted_list.h"


struct p_queue
{
    sortlist_ty *list;
};

static sortlist_ty *qtos(pqueue_ty *p_queue)
{
    return p_queue->list;
}

static pqueue_ty *stoq(sortlist_ty *sorted_list)
{
    pqueue_ty *queue = NULL;

    queue->list = sorted_list;

    return queue;
}

pqueue_ty *PQueueCreate(DataCompare_ty prior_func)
{
    pqueue_ty *new = (pqueue_ty *)malloc(sizeof(pqueue_ty));
    
    if (!new)
    {
        return NULL;
    }

    new->list = SortListCreate(prior_func);

    if (!new->list)
    {
        free(new);
        return NULL;
    }

    return new;
}

void PQueueDestroy(pqueue_ty *pqueue)
{
    assert(pqueue);

    SortListDestroy(qtos(pqueue));
    pqueue->list = NULL;
    free(pqueue);
}

int PQueueEnqueue(pqueue_ty *pqueue, void *data)
{
    return (SortListIterIsEqual(SortListEnd(qtos(pqueue)), SortListInsert(qtos(pqueue), data)));
}

void *PQueueDequeue(pqueue_ty *pqueue)
{
    return SortListPopBack(qtos(pqueue));
}

void *PQueuePeek(const pqueue_ty *pqueue)
{
    return SortListGetData(SortListPrev(SortListEnd(qtos((pqueue_ty *)pqueue))));
}

int PQueueIsEmpty(const pqueue_ty *pqueue)
{
    return SortListIsEmpty(qtos((pqueue_ty *)pqueue));
}

size_t PQueueSize(const pqueue_ty *pqueue)
{
    return SortListSize(qtos((pqueue_ty *)pqueue));
}

void PQueueClear(pqueue_ty *pqueue)
{
    while(!SortListIterIsEqual( SortListEnd(qtos(pqueue)), SortListBegin(qtos(pqueue))))
    {
        SortListRemove(SortListBegin(qtos(pqueue)));
    }
}

void *PQueueErase(pqueue_ty *pqueue, PQIsMatch_ty is_match, void *param)
{
    void* ret = NULL;
    sortlist_iter_ty iter = SortListFindIf(SortListBegin(qtos(pqueue)), SortListEnd(qtos(pqueue)),(Sort_IsMatch_ty) is_match, param);
    if (SortListIterIsEqual(iter,SortListEnd(qtos(pqueue))))
    {
        return NULL;
    }
    ret = SortListGetData(iter);
    SortListRemove(iter);
    
    return ret;
}
