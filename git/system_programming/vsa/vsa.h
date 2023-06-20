/*******************************************************************************
*			VSA (VARIABLE-SIZE ALLOCATOR)                                                    
*******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A variable-size allocator, which supports initialization,
			   allocation and deallocation (free), and VSALargestAvailable
			   (which a user can use in order to know what is the largest chunk
			   available in the pool).
* AUTHOR: HRD24
* REVIEWER: 
* DATE: 08/05/2022
* VERSION: 0.1

*******************************************************************************/
#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_ty;


/*******************************************************************************
* Function: Create a VSA to manage the memory given by the void *mem, 
  and divide the memory_size given to chunks of chunk_size.
  
* Arguments: mem - void ptr to the memory allocated by the user,
  	     memory_size - the allocated space size pointed to by mem.
  	     
* Return value: A pointer to the VSA

* Notes: Undefined behavior - if pointer is NULL or size is 0, or size
		 is not enough for at least 1 chunk.
 		 This function assumes that mem is aligned to word size.
 		 
* Complexity: O(1)
*******************************************************************************/
vsa_ty *VSAInit(void *mem, size_t memory_size);


/*******************************************************************************
* Function: Allocate (OCCUPY) a chunk of memory of chunk_size.

* Arguments: vsa  A pointer to VSA, 

             chunk_size (the number of bytes to allocate).

* Return value: A pointer to the allocated  chunk of memory;
* 				NULL when allocation fails.

* Notes: Undefined behavior - if vsa ptr is NULL 

* Complexity: O(n) - number of free chunks 
*******************************************************************************/
void *VSAAlloc(vsa_ty *vsa, size_t chunk_size);


/*******************************************************************************
* Function: Free the memory allocated to a chunk of memory before
* 			so that this memory could be re-use.
* Arguments: a pointer to the chunk to free.
* Notes: Undefined behavior - If the chunk isn't a previously allocated chunk.
* Complexity: O(1)
*******************************************************************************/
void VSAFree(void *chunk);


/*******************************************************************************
* Function: Returns the largest size of chunk available to be allocated.
* Arguments: A pointer to the vsa
* Notes: Undefined behavior if vsa is NULL.
* Complexity: O(n)
*******************************************************************************/
size_t VSALargestAvailable(vsa_ty *vsa);


#endif /* __VSA_H__ */