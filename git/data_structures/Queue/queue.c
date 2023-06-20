#include <assert.h> 		/* assert */
#include <stdlib.h> 		/*malloc*/

#include"slist.h"
#include"queue.h"

struct queue
{
	slist_ty *list;
};


queue_ty *QueueCreate(void)
{
	queue_ty *new = (queue_ty*)malloc(sizeof(queue_ty));
	
	new -> list = SlistCreate();
	
	return new;
}

void QueueDestroy(queue_ty *queue)
{
	assert(queue);
	
	SlistDestroy(queue -> list);
	free(queue);
}

int QueueEnqueue(queue_ty *queue, const void *element)
{
	assert(queue);
	
	/* if NULL returns 0, otherwise returns 1 */
	return !!SlistInsertBefore(SlistEnd(queue -> list), (void*)element);
}

void QueueDequeue(queue_ty *queue)
{
	assert(queue);

	SlistRemove(SlistBegin(queue -> list));
}

void *QueuePeek(const queue_ty *queue)
{
	assert(queue);
	
	return SlistGetData(SlistBegin(queue -> list));
}

size_t QueueSize(const queue_ty *queue)
{
	assert(queue);
	
	return SlistCount(queue -> list);
}

int QueueIsEmpty(const queue_ty *queue)
{
	assert(queue);
	
	/* if true returns 1, false 0 */
	return (0 != QueueSize(queue));
}

queue_ty *QueueAppend(queue_ty *queue1, queue_ty *queue2)
{
	assert(queue1);
	assert(queue2);

	queue1 -> list = SlistAppend(queue1 -> list, queue2 -> list);
	
	return queue1;
}


