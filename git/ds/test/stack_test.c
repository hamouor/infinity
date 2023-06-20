#include "stack.h"
#include <stddef.h>	/*size_t*/
#include <stdio.h>	/*printf*/
int main()
{
	void* test_stack = NULL, *test2 = NULL;
	int* test_ptr = NULL, *ptr2 = NULL;
	int test_element = 18, elem2 = 14;
	
	
	test_stack = StackCreate(8,8);
	
	test2 = StackCreate(4,4);
	
	StackPush(test_stack, &test_element);
	
	StackPush(test2, &elem2);
	
	StackPush(test2, &elem2);
	
	printf("size when 1: %ld\n", StackSize(test_stack));

	printf("size when 1: %ld\n", StackSize(test2));
	
	printf("is empty when NOT empty: %d\n", StackIsEmpty(test_stack));

	printf("is empty when NOT empty: %d\n", StackIsEmpty(test2));
			
	test_ptr = (int*)StackPeek(test_stack);
	
	ptr2 = (int*)StackPeek(test2);
	
	printf("value inserted should be %d: %d\n",test_element, *test_ptr);
	
	printf("value inserted should be %d: %d\n",elem2, *ptr2);
	
	StackPop(test_stack);

	StackPop(test2);
	
	printf("size when 0: %ld\n", StackSize(test_stack));

	printf("size when 1: %ld\n", StackSize(test2));
	
	printf("is empty when empty: %d\n", StackIsEmpty(test_stack));
	
	printf("capacity: %ld\n", StackCapacity(test_stack));
	
	StackDestroy(test_stack);
	
	StackDestroy(test2);
	
	return 0;
}
