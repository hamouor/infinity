#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc(), free() */

#include "heap_pq.h"
#include "heap.h"

static const heap_ty *PQ2Heap(const pqueue_ty *pqueue);
static const pqueue_ty *Heap2PQ(const heap_ty *heap);

pqueue_ty *PQueueCreate(PQDataCompare_ty prior_func)
{
	pqueue_ty *queue = NULL;
	
	assert(prior_func);
	
	queue = (pqueue_ty *)Heap2PQ(HeapCreate(prior_func));
	
	return queue;
}

void PQueueDestroy(pqueue_ty *pqueue)
{
	assert(pqueue);
	
	HeapDestroy((heap_ty *)PQ2Heap(pqueue));
}

int PQueueEnqueue(pqueue_ty *pqueue, void *data)
{
	assert(pqueue);
	
	return (HeapPush((heap_ty *)PQ2Heap(pqueue), data));
}

void *PQueueDequeue(pqueue_ty *pqueue)
{
	assert(pqueue);
	assert(!PQueueIsEmpty(pqueue));
	
	return (HeapPop((heap_ty *)PQ2Heap(pqueue)));
}

void *PQueuePeek(const pqueue_ty *pqueue)
{
	assert(pqueue);
	assert(!PQueueIsEmpty(pqueue));
	
	return HeapPeek(PQ2Heap(pqueue));
}

int PQueueIsEmpty(const pqueue_ty *pqueue)
{
	assert(pqueue);
	
	return (HeapIsEmpty(PQ2Heap(pqueue)));
}

size_t PQueueSize(const pqueue_ty *pqueue)
{
	assert(pqueue);
	
	return (HeapSize(PQ2Heap(pqueue)));
}

void PQueueClear(pqueue_ty *pqueue)
{
	assert(pqueue);
	
	while(!PQueueIsEmpty(pqueue))
	{
		PQueueDequeue(pqueue);
	}
}

void *PQueueErase(pqueue_ty *pqueue, PQIsMatch_ty is_match, void *param)
{
	assert(pqueue);
	assert(is_match);
	
	return (HeapRemove((heap_ty *)PQ2Heap(pqueue), is_match, param));
}

static const heap_ty *PQ2Heap(const pqueue_ty *pqueue)
{
	assert(pqueue);
	
	return (heap_ty *)pqueue;
}


static const pqueue_ty *Heap2PQ(const heap_ty *heap)
{
	assert(heap);
	
	return (pqueue_ty *)heap;
}
