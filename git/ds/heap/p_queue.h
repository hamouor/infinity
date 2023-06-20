#ifndef __P_QUEUE__
#define __P_QUEUE__

#include <stddef.h>	/* size_t */

typedef struct p_queue pqueue_ty;

/* Priority comparison function return value:
* 1 if data1 has higher priority than data2
* -1 if data1 has lower priority than data2
* 0 if data1 and data2 have equal priority */
typedef int(*PQDataCompare_ty)(const void *data1, const void *data2);

/* Data value match return value:
* 1 if data fits some criterion, 0 otherwise */ 
typedef int(*PQIsMatch_ty)(const void *data, const void *param);
/*******************************************************************************
* Function:         Create a new priority queue.
* Arguments:        a priority function.
* Return value:     A pointer to the new priority queue handler or 
*                   NULL on failure
* Notes: 	        A created queue MUST be destroyed!
* Complexity:       O(1).
*******************************************************************************/
pqueue_ty *PQueueCreate(PQDataCompare_ty prior_func);

/*******************************************************************************
* Function:         destroys priority queue.
* Arguments:        a pointer to priority queue.
* Return value:     
* Notes: 	 
* Complexity:       O(n).
*******************************************************************************/

void PQueueDestroy(pqueue_ty *pqueue);

/*******************************************************************************
* Function:         insert new data to the queue
* Arguments:        a pointer to p_queue and pointer to data to insert
* Return value:     0 if successfull 1 if not
* Notes: 	        
* Complexity:       O(n).
*******************************************************************************/

int PQueueEnqueue(pqueue_ty *pqueue, void *data);

/*******************************************************************************
* Function:         remove the least prioritized element of the q and retun its value
* Arguments:        a pointer to p_queue
* Return value:     data of the removed member
* Notes: 	        
* Complexity:       O(1).
*******************************************************************************/

void *PQueueDequeue(pqueue_ty *pqueue);

/*******************************************************************************
* Function:         get the value of the least prioritized element of the q
* Arguments:        a pointer to p_queue
* Return value:     data of the member
* Notes: 	        
* Complexity:       O(1).
*******************************************************************************/

void *PQueuePeek(const pqueue_ty *pqueue);

/*******************************************************************************
* Function:         checks if q is empty
* Arguments:        a pointer to p_queue
* Return value:     1 if q is empty 0 otherwise
* Notes: 	        
* Complexity:       O(1).
*******************************************************************************/

int PQueueIsEmpty(const pqueue_ty *pqueue);

/*******************************************************************************
* Function:         returns the number of elements in q
* Arguments:        a pointer to p_queue
* Return value:     number of elements
* Notes: 	        
* Complexity:       O(n).
*******************************************************************************/

size_t PQueueSize(const pqueue_ty *pqueue);

/*******************************************************************************
* Function:         emptys out the q
* Arguments:        a pointer to p_queue
* Return value:     a pointer to p_queue now empty
* Notes: 	        
* Complexity:       O(n).
*******************************************************************************/

void PQueueClear(pqueue_ty *pqueue);

/*******************************************************************************
* Function:         erases an element in q according to ismatch function and the parameter
* Arguments:        a pointer to p_queue, match checking function, parameter.
* Return value:     a pointer to the data of the erased member. NULL if no match is found
* Notes: 	        
* Complexity:       O(n).
*******************************************************************************/

void *PQueueErase(pqueue_ty *pqueue, PQIsMatch_ty is_match, void *param);


#endif /* __P_QUEUE_H__ */