#ifndef __Heap_H__
#define __Heap_H__

/******************************************************************************/
/*  		                        Heap	            		              */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  A heap is a data structure based.
* AUTHOR: Liverpool
* REVIEWER: Real Madrid
* DATE: 08/06/2022
* VERSION: 0.11
*******************************************************************************/

#include <stddef.h> /* size_t */


typedef struct heap heap_ty;

/* returns nonzero if data1 and data2 are equal, 0 otherwise */
typedef int(*ismatch_ty)(const void *data1, const void *data2);

/*returns < 0 if data1 < data2, 0 if data1 = data2, and > 0 if data1 > data2*/
typedef int(*compfunc_ty)(const void* data1, const void* data2); 


/*******************************************************************************
* Function:     Creates a new heap.                                      TODO- initial capacity?
* Arguments:    A compare function to sort the heap.
* Return value: A pointer to the new heap; NULL on failure.
* Notes:		Complexity - O(1).
*******************************************************************************/
heap_ty *HeapCreate(compfunc_ty CompFunc);

/*******************************************************************************
* Function:     Destroy an existing heap.
* Arguments:    A pointer to the existing heap.
* Return value: None.
* Notes:        Complexity - O(1).
*******************************************************************************/
void HeapDestroy(heap_ty *heap);

/*******************************************************************************
* Function:     Determines the size of the heap.
* Arguments:    A pointer to existing heap.
* Return value: The number of the elements in the heap.
* Notes: 		Complexity - O(1).
*******************************************************************************/
size_t HeapSize(const heap_ty *heap);

/*******************************************************************************
* Function:     Determines if the heap is empty.
* Arguments:    A pointer to existing heap.
* Return value: 1 if the heap is empty; zero if not. 
* Notes: 		Complexity - O(1).
*******************************************************************************/
int HeapIsEmpty(const heap_ty *heap);

/*******************************************************************************
* Function: Returns a copy of the top element (largest) without removing it.
* Arguments: Pointer to the heap.
* Return value: The top element from the heap.
* Notes: Undefined behavior if heap is empty.
*******************************************************************************/
void *HeapPeek(const heap_ty *heap);

/*******************************************************************************
* Function:     Inserts a new element into the heap.
* Arguments:    heap - A pointer to the heap.
				data - A void pointer to the data to add.
* Return value: 0 on success, 1 on failure.
* Notes:        Complexity - O(log n).
*******************************************************************************/
int HeapPush(heap_ty *heap, void *data);

/*******************************************************************************
* Function:     Pops the top element from heap.
* Arguments:    An heap and the data to remove.
* Return value: The data of the removed element.  
* Notes:        Complexity - O(log n). NULL if heap is empty
*******************************************************************************/
void *HeapPop(heap_ty *heap);

/*******************************************************************************
* Function:     Removes an existing element from the heap.
* Arguments:    A heap, is_match function pointer and the data to remove.
* Return value: The data of the removed element; NULL on failure (element wasn't found) 
* Notes:        Complexity - O(n).
*******************************************************************************/
void *HeapRemove(heap_ty *heap, ismatch_ty ismatch, void *param);







#endif      /* __Heap_H__ */





