#include"queue.h"

#include<stdio.h>

int main()
{
	queue_ty* q1 = NULL, *q2 = NULL;
	int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6;
	q1 = QueueCreate();
	q2 = QueueCreate();
	printf("is empty returns %d\n",QueueIsEmpty(q2));
	QueueEnqueue(q1, (void*)&x1);
	QueueEnqueue(q1, (void*)&x2);
	QueueEnqueue(q1, (void*)&x3);
	QueueEnqueue(q1, (void*)&x4);
	QueueEnqueue(q2, (void*)&x5);
	QueueEnqueue(q2, (void*)&x6);
	printf("(size)should be 2 and it is: %lu\n", QueueSize(q2));
	printf("(create,enqueueing)should be %d and it is: %d\n", x1, *(int*)QueuePeek(q1));
	printf("(multipule create,enqueueing)should be %d and it is: %d\n", x5, *(int*)QueuePeek(q2));
	QueueDequeue(q2);
	printf("(peek, dequeue)should be %d and it is: %d\n", x6, *(int*)QueuePeek(q2));
	printf("(size)should be 4 and it is: %lu\n", QueueSize(q1));
	printf("isnt empty returns %d\n",QueueIsEmpty(q2));
	q1 = QueueAppend(q1,q2);
	printf("(size)should be 5 and it is: %lu\n", QueueSize(q1));
	printf("is empty returns %d\n",QueueIsEmpty(q2));
	QueueEnqueue(q2, (void*)&x5);
	QueueEnqueue(q2, (void*)&x6);
	printf("(size)should be 2 and it is: %lu\n", QueueSize(q2));
	printf("isnt empty returns %d\n",QueueIsEmpty(q2));
	QueueDestroy(q1);
	QueueDestroy(q2);
	return 1;
}
