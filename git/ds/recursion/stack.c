#include <assert.h> 	/*assert*/
#include <stdlib.h> 	/*malloc*/
#include <stddef.h>	/*size_t*/
#include <string.h>	/*memcpy*/
#include "stack.h"

struct stack
{
	void *start; /* A start address */
	size_t size; /* The current stack size */
	size_t element_size; /* The element size in bytes */
	size_t capacity; /* The maximum number of elements */
};

stack_ty *StackCreate(size_t element_size, size_t capacity)
{
	stack_ty* new_stack = malloc(element_size * capacity + sizeof(stack_ty));
	
	new_stack->start = (void*)(new_stack + 1); 
	assert(new_stack->start);
	new_stack->size = 0;
	new_stack->element_size = element_size;
	new_stack->capacity = capacity;
	
	return new_stack;
}

void StackDestroy(stack_ty *stack)
{
	assert(stack->start);
	
	free((void*)stack);
	(stack->start) = NULL;
}

void StackPop(stack_ty *stack)
{
	assert(stack->start);
	
	if(stack->size>0)
	{
		stack->size -= 1;
	}
}

void StackPush(stack_ty *stack, const void *element)
{	
	assert(stack->start);

	if (stack->size<stack->capacity)
	{
		memcpy((char*)stack->start + (stack->size * stack->element_size), element, stack->element_size);
		stack->size += 1;
	}
}

void *StackPeek(const stack_ty *stack)
{
	assert(stack->start);
	
	if(stack->size>0)
	{
		return (void*)((char*)stack->start + ((stack->size - 1) * stack->element_size));
	}
	else
	{
		return NULL;
	}
}

size_t StackSize(const stack_ty *stack)
{
	assert(stack->start);
	
	return stack->size;
}

int StackIsEmpty(const stack_ty *stack)
{
	assert(stack->start);
	
	if (stack->size > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

size_t StackCapacity(const stack_ty *stack)
{
	assert(stack->start);
	
	return stack->capacity;
}
