/*******************************************************************************
*						FSA (FIXED-SIZE ALLOCATOR)                                                    
*******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A fixed-size allocator, which supports initialization, allocation
*			   and deallocation (free), count the number of free blocks in the
*			   pool, and SuggestSize (which a user can use before init, in order
*			   to know how many memory to allocate).
* AUTHOR: HRD24
* REVIEWER: 
* DATE: 02/05/2022
* VERSION: 0.1

*******************************************************************************/
#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_ty;

/*******************************************************************************
* Function:         Suggests a minimun size of bytes to allocate.
* Arguments:		number of blocks and number of bytes in each block.
* Return value:     suggested size in bytes
* Complexity:       O(1)
*******************************************************************************/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);


/*******************************************************************************
* Function:         Create a FSA to manage the memory given by the void *mem, 
                    and divide the memory_size given to chunks of block_size.
* Arguments:        void ptr to the memory allocated by the user,
                    memory_size (the allocated space size pointed to by mem),
					block_size (a fixed-size determined by the user).
* Return value:     A pointer to the FSA
* Notes:			Undefined behavior - if pointer is NULL or size is 0, or size
                    is not enough for at least 1 block.
                    This function assumes that mem is aligned to word size.
* Complexity:       O(n)
*******************************************************************************/
fsa_ty *FSAInit(void *mem, size_t memory_size, size_t block_size);


/*******************************************************************************
* Function:         Allocate (OCCUPY) a block of memory of block_size.
* Arguments:        A pointer to FSA
* Return value:     A pointer to the allocated  block of memory.
*                   NULL when memory is full (no free blocks).
* Notes:			Undefined behavior - if fsa ptr is NULL 
* Complexity:       O(1)
*******************************************************************************/
void *FSAAlloc(fsa_ty *fsa);


/*******************************************************************************
* Function:         Free the memory allocated to a block of memory before
*					so that this memory could be re-use.
* Arguments:        A pointer to the memory to free, a pointer to the block.
* Notes:			Undefined behavior - if fsa pointer is NULL or 
*					If the block isn't a previously allocated block from the
					given FSA.
* Complexity:       O(1)
*******************************************************************************/
void FSAFree(fsa_ty *fsa, void *block);


/*******************************************************************************
* Function:         Count the number of free blocks in the pool.
* Arguments:        A pointer to the memory pool.
* Return value:     number of free blocks in size_t.
* Notes:			Undefined behavior - if fsa pointer is NULL.
* Complexity:       O(n)
*******************************************************************************/
size_t FSACountFree(const fsa_ty *fsa);


#endif /* __FSA_H__ */