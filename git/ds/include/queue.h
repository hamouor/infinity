#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t       */
/*----------------------------------------------------------------------------*
*			                QUEUE                                  *
*-----------------------------------------------------------------------------*
* DESCRIPTION: A Queue, which supports enqueueing elements and dequeueing 
*              elements in FIFO order, peeking at the element at the front of
*              the queue and appending two queues together.
* AUTHOR: HRD24
* REVIEWER: 
* DATE: 14/04/2022
* VERSION: 0.2
*----------------------------------------------------------------------------*/

typedef struct queue queue_ty;



/******************************************************************************
* Function: Allocates memory for a new queue. 
* Arguments: None.
* Return value: pointer to the new queue.
* Notes: A created queue MUST be destroyed after use.
*        Returns NULL if queue creation failed.
* Complexity: O(1)
******************************************************************************/
queue_ty *QueueCreate(void);


/*******************************************************************************
* Function: Frees the memory allocated for the queue.
* Arguments: A pointer to the queue.
* Return value: None
* Complexity: O(n)
*******************************************************************************/
void QueueDestroy(queue_ty *queue);


/*******************************************************************************
* Function: Adds elmement to the end of the queue.
* Arguments: A pointer to a queue, a pointer to element.
* Return value: 1 if enqueue succeeded, 0 if failed.
* Notes: Undefined behavior - if queue pointer points to NULL.
* Complexity: O(1)
*******************************************************************************/
int QueueEnqueue(queue_ty *queue, const void *element);


/*******************************************************************************
* Function: Removes the elmement at the front of the queue .
* Arguments: A Pointer To Queue.
* Return value: None
* Notes: Undefined behavior - if queue is empty, if queue pointer points to NULL.
* Complexity: O(1)
*******************************************************************************/
void QueueDequeue(queue_ty *queue);


/*******************************************************************************
* Function: Returns a pointer to the element at the front of the queue.
* Arguments: A pointer to queue.
* Return value: void pointer to the element at the front.
* Notes: Undefined behavior - if queue is empty, if queue pointer points to NULL.
* Complexity: O(1)
*******************************************************************************/
void *QueuePeek(const queue_ty *queue);


/*******************************************************************************
* Function: Counts how many element the queue contains.
* Arguments: A pointer to queue.
* Return value: Number of elements in queue.
* Notes: Undefined behavior - if queue pointer points to NULL.
* Complexity: O(n)
*******************************************************************************/
size_t QueueSize(const queue_ty *queue);


/*******************************************************************************
* Function: Checks if queue is empty.
* Arguments: A pointer to queue.
* Return value: 1 if empty 0 if not.
* Notes: Undefined behavior - if queue pointer points to NULL.
* Complexity: O(1)
*******************************************************************************/
int QueueIsEmpty(const queue_ty *queue);


/*******************************************************************************
* Function: Appends queue2 to the end of queue1, empties queue2.
* Arguments: A pointer to queue1, a pointer to queue2.
* Return value: A pointer to the beginning of queue1.
* Notes: Empties queue2 but queue2 still needs to be destroyed.
* Notes: Undefined behavior - if queue pointers point to NULL.
* Complexity: O(1)
*******************************************************************************/
queue_ty *QueueAppend(queue_ty *queue1, queue_ty *queue2);


#endif /* __QUEUE_H__ */



