#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>	/*size_t*/
/******************************************************************************/
/*									Stack									  */ 
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A Stack data type, which supports a user-defined element size, 
* pushing elements and popping elements in LIFO order and peeking at the top
* element.
* AUTHOR: HRD24
* REVIEWER:
* DATE: 05/04/2022
* VERSION: 0.1
*******************************************************************************/

typedef struct stack stack_ty;

/* TODO: Move this to the implementation file. */


/* Create */
/*******************************************************************************
* Function: Allocates memory for a stack type of some size and a user-defined 
* element size in bytes.
* Arguments: Element size and capacity.
* Return value: The stack struct.
* Notes: The number of elements that the stack can store is either constant or
* dependent on the element size (constant memory size). 
* ***A created stack MUST be destroyed after use!***
*******************************************************************************/
stack_ty *StackCreate(size_t element_size, size_t capacity);

/* Destroy */
/*******************************************************************************
* Function: Frees the memory allocated to a stack.
* Arguments: Stack.
* Return value:
* Notes: 
*******************************************************************************/
void StackDestroy(stack_ty *stack);

/* Pop */
/*******************************************************************************
* Function: Removes the top element from the stack.
* Arguments: Stack.
* Return value:
* Notes:
*******************************************************************************/
void StackPop(stack_ty *stack);

/* Push */
/*******************************************************************************
* Function: Puts an element at the top of the stack.
* Arguments: Stack, element to be pushed.
* Return value:
* Notes: If the stack is full, the element is not pushed.
*******************************************************************************/
void StackPush(stack_ty *stack, const void *element);

/* Peek */
/*******************************************************************************
* Function: Returns a copy of the top element in the stack, without removing it.
* Arguments: Stack.
* Return value: The top element from the stack.
* Notes:
*******************************************************************************/
void *StackPeek(const stack_ty *stack);

/* Size */
/*******************************************************************************
* Function: Returns the current number of elements in the stack.
* Arguments: Stack.
* Return value: An unsigned integer describing the amount of elements currently
* in the stack.
* Notes:
*******************************************************************************/
size_t StackSize(const stack_ty *stack);

/* Is Empty */
/*******************************************************************************
* Function: Checks if the stack is empty and returns a boolean value of 'true'
* if that's the case. Returns 'false' if the stack has at least 1 element in it. 
* Arguments: Stack.
* Return value: An integer that can be either 0 or non-zero.
* Notes:
*******************************************************************************/
int StackIsEmpty(const stack_ty *stack);

/* Capacity */
/*******************************************************************************
* Function: Returns the possible amount of elements in the stack.
* Arguments: Stack.
* Return value: An unsigned integer describing the amount of elements the stack
* can contain.
* Notes:
*******************************************************************************/
size_t StackCapacity(const stack_ty *stack);


#endif /* __STACK_H__ */
