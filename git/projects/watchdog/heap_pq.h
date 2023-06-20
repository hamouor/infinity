/*******************************************************************************
*		                 PRIORITY QUEUE                                                  
*******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A priority queue data structure, which supports inserting elements
*              according to priority function, removing element from the front
*              of the queue, count elements, find nodes (according to match 
*              function), and peek to the top element in the list.
* AUTHOR: HDR24
* REVIEWER:
* DATE: 25/04/2022
* VERSION: 0.4
* Time of last Change: 15:39
*******************************************************************************/

#ifndef __P_QUEUE__
#define __P_QUEUE__

#include <stddef.h>	/* size_t */

typedef struct pqueue pqueue_ty;

/* Priority comparison function return value:
* 1 if data1 has higher priority than data2
* -1 if data1 has lower priority than data2
* 0 if data1 and data2 have equal priority */
typedef int(*PQDataCompare_ty)(const void *data1, const void *data2);

/* Data value match return value:
* 1 if data fits some criterion, 0 otherwise */ 
typedef int(*PQIsMatch_ty)(const void *data, const void *param);

/*******************************************************************************
* Function:			Creates a priority queue.
* Arguments:		Priority sorting function prior_func.
* Return value:		A pointer to the created priority queue, NULL if creation 
* 					not successful.
* Notes:			A created priority queue MUST be destroyed using 
* 					PQueueDestroy()!
* Complexity:		O(1)
*******************************************************************************/
pqueue_ty *PQueueCreate(PQDataCompare_ty prior_func);

/*******************************************************************************
* Function:			Destroys a priority queue.
* Arguments:		A pointer to an existing priority queue.
* Return value:		None.
* Notes:			Undefined behaviour if given NULL pointer.
* Complexity:		O(n)
*******************************************************************************/
void PQueueDestroy(pqueue_ty *pqueue);

/*******************************************************************************
* Function:			Enqueues a given data into a priority queue.
* Arguments:		Pointer to desired priority queue, pointer to data.
* Return value:		0 on success, 1 on failure.
* Notes:			Undefined behaviour if pointer to queue is NULL.
* Complexity:		O(n)
*******************************************************************************/
int PQueueEnqueue(pqueue_ty *pqueue, void *data);

/*******************************************************************************
* Function:			Dequeues the top priority item from a priority queue.
* Arguments:		Pointer to priority queue.
* Return value:		Pointer to dequeued data.
* Notes:			Undefined behaviour if pointer to queue is NULL or queue is 
* 					empty.
* Complexity:		O(1)
*******************************************************************************/
void *PQueueDequeue(pqueue_ty *pqueue);

/*******************************************************************************
* Function:			Allows to peek at the data with the top priority in the 
* 					priority queue without dequeueing it.
* Arguments:		Pointer to priority queue.
* Return value:		Pointer to top priority data in the queue.
* Notes:			Undefined behaviour if pointer to queue is NULL or queue is 
* 					empty.
* Complexity:		O(1)
*******************************************************************************/
void *PQueuePeek(const pqueue_ty *pqueue);

/*******************************************************************************
* Function:			Checks whether the priority queue is empty or not.
* Arguments:		Pointer to priority queue.
* Return value:		1 if queue is empty, 0 otherwise.
* Notes:			Undefined behaviour if pointer to queue is NULL.
* Complexity:		O(1)
*******************************************************************************/
int PQueueIsEmpty(const pqueue_ty *pqueue);

/*******************************************************************************
* Function:			Counts the number of items in the priority queue.
* Arguments:		Pointer to priority queue.
* Return value:		A non-negative integer.
* Notes:			Undefined behaviour if pointer to queue is NULL.
* Complexity:		O(n)
*******************************************************************************/
size_t PQueueSize(const pqueue_ty *pqueue);

/*******************************************************************************
* Function:			Removes all items from priority queue.
* Arguments:		Pointer to priority queue.
* Return value:		None.
* Notes:			Undefined behaviour if pointer to queue is NULL.
* Complexity:		O(n)
*******************************************************************************/
void PQueueClear(pqueue_ty *pqueue);

/*******************************************************************************
* Function:			Finds data in queue according to given is_match function and
* 					a parameter and removes it from the queue.
* Arguments:		Pointer to priority queue, pointer to function of type 
* 					is_match, pointer to some parameter to be sent to function.
* Return value:		Pointer to data that was erased or NULL if nothing was found.
* Notes:			Undefined behaviour if pointer to queue or is_match function
* 					is NULL.
* Complexity:		O(n)
*******************************************************************************/
void *PQueueErase(pqueue_ty *pqueue, PQIsMatch_ty is_match, void *param);

#endif /* __P_QUEUE_H__ */
