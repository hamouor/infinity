/*----------------------------------------------------------------------------*
*                               Circular Buffer                               *
*-----------------------------------------------------------------------------*
* DESCRIPTION: A circular buffer data structure which supports writing and 
*              reading bytes in FIFO order.
* AUTHOR: Yair Lapid
* REVIEWER: Yossi Benayoun
* DATE: 18/04/2022
* VERSION: 0.3
*----------------------------------------------------------------------------*/
#ifndef __CBUFFER_H__
#define __CBUFFER_H__

#include <sys/types.h> /* size_t, ssize_t */


typedef struct cbuffer cbuffer_ty;


/*******************************************************************************
* Function: Allocates memory for a new 'cbuffer'. 
* Arguments: The maximum amount of bytes the buffer will be able to contain.
* Return value: A pointer to the new buffer or NULL on failure
* Notes: An allocated buffer should be destroyed as it goes out of use.
* Complexity: O(1).
*******************************************************************************/
cbuffer_ty *CBufCreate(size_t capacity);


/*******************************************************************************
* Function: Frees the memory allocated to 'cbuffer'.
* Arguments: A pointer to the buffer.
* Return value: None
* Notes: undefined behaviour -  if cbuffer is NULL 
* Complexity: O(1).
*******************************************************************************/
void CBufDestroy(cbuffer_ty *cbuffer);


/*******************************************************************************
* Function: Returns the number of free bytes currently available on 'cbuffer'.
* Arguments: A pointer to the buffer.
* Return value: The amount of free bytes in size_t.
* Notes: Undefined behavior - if buffer pointer points to NULL.
* Complexity: O(1).
*******************************************************************************/
size_t CBufFreeSpace(const cbuffer_ty *cbuffer);


/*******************************************************************************
* Function: Returns the amount of bytes currently occupied in 'cbuffer'.
* Arguments: A pointer to buffer.
* Return value: The amount of bytes in buffer in size_t.
* Notes: Undefined behavior - if buffer pointer points to NULL.
* Complexity: O(1).
*******************************************************************************/
size_t CBufSize(const cbuffer_ty *cbuffer);


/*******************************************************************************
* Function: Attempts to read 'count' bytes from 'cbuffer' to 'output_buf'.
* Arguments: A pointer to cbuffer, data address to copy into and an amount of
* bytes.
* Return value: Amount of bytes read successfuly or -1 if cbuffer is empty.
* Notes: Undefined behavior - if buffer points to NULL. Note, If count is bigger
* than the occupied bytes in 'cbuffer' it will copy only part of it.
* Complexity: O(n).
*******************************************************************************/
ssize_t CBufRead(cbuffer_ty *cbuffer, void *output_buf, size_t count);


/*******************************************************************************
* Function: Attempts to write 'count' bytes from 'input_buf' into 'cbuffer'.
* Arguments: A pointer to cbuffer, data address to copy from and an amount of
* bytes.
* Return value: Amount of bytes written successfuly or -1 if cbuffer is full.
* Notes: Undefined behavior - if 'cbuffer' points to NULL or if 'input_buf' does
* not have enough space to store the requested bytes. Note, If count is bigger
* than the free bytes in 'cbuffer' it will copy only part of it.
* Complexity: O(n).
*******************************************************************************/
ssize_t CBufWrite(cbuffer_ty *cbuffer, const void *input_buf, size_t count);


/*******************************************************************************
* Function: Checks if a 'cbuffer' is empty.
* Arguments: A pointer to cbuffer.
* Return value: 1 if empty, 0 if not.
* Notes: Undefined behavior - if buffer pointer points to NULL.
* Complexity: O(1).
*******************************************************************************/
int CBufIsEmpty(const cbuffer_ty *cbuffer);




#endif /* __CBUFFER_H__ */



