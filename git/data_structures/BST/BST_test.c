#include <stdio.h>
#include <limits.h>
#include <time.h>

#include "BST.h"

#define UNUSED(x) (void)(x)

enum bool { FALSE, TRUE };

typedef enum status { ERROR, SUCCESS, FAILURE } status_ty;

typedef status_ty (*test_func)(void);

status_ty TestBSTCreate(void);
status_ty TestBSTDestroy(void);
status_ty TestBSTIsEmpty(void);
status_ty TestBSTSize(void);
status_ty TestBSTInsert(void);
status_ty TestBSTRemove(void);
status_ty TestBSTGetData(void);
status_ty TestBSTBegin(void);
status_ty TestBSTEnd(void);
status_ty TestBSTPrev(void);
status_ty TestBSTNext(void);
status_ty TestBSTIterIsEqual(void);
status_ty TestBSTFind(void);
status_ty TestBSTForEach(void);

int IntCmp(void *int1, void *int2);
int MultiplyByNum(void *data, void *multiplier);
int GetMin(int *array, int size);
int GetMax(int *array, int size);
void MultiplyArray(int *array, int size, int multiplier);

int main(void)
{
	test_func tests[] = {
		TestBSTCreate,
		TestBSTDestroy,
		TestBSTIsEmpty,
		TestBSTSize,
		TestBSTInsert,
		TestBSTRemove,
		TestBSTGetData,
		TestBSTBegin,
		TestBSTEnd,
		TestBSTPrev,
		TestBSTNext,
		TestBSTIterIsEqual,
		TestBSTFind,
		TestBSTForEach
	};
	
	char *test_names[] = {
		"TestBSTCreate",
		"TestBSTDestroy",
		"TestBSTIsEmpty",
		"TestBSTSize",
		"TestBSTInsert",
		"TestBSTRemove",
		"TestBSTGetData",
		"TestBSTBegin",
		"TestBSTEnd",
		"TestBSTPrev",
		"TestBSTNext",
		"TestBSTIterIsEqual",
		"TestBSTFind",
		"TestBSTForEach"
	};
	
	int num_tests = sizeof(tests) / sizeof(tests[0]);
	int i = 0;
	status_ty test_result = SUCCESS;
	status_ty unit_result = ERROR;
	
	for (i = 0; i < num_tests; ++i)
	{
		unit_result = tests[i]();
		switch (unit_result)
		{
			case ERROR:
				printf("ERROR in running test %d: %s().\n", i + 1, test_names[i]);
				test_result = ERROR;
				break;
			case SUCCESS:
				break;
			case FAILURE:
				printf("%s() failed! See details above!.\n", test_names[i]);
				test_result = FAILURE;
				break;
			default:
				break;
		}
	}
	
	switch (test_result)
	{
		case ERROR:
			printf("Error in running some tests! See details above!\n");
			test_result = ERROR;
			break;
		case SUCCESS:
			printf("All tests successful!\n");
			break;
		case FAILURE:
			printf("Some tests failed! See details above!.\n");
			test_result = FAILURE;
			break;
		default:
			break;
	}
	
	return 0;
}

status_ty TestBSTCreate(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	
	result = SUCCESS;
	
	/* check for non-null return */
	bst = BSTCreate(IntCmp);
	
	if (!bst)
	{
		result = FAILURE;
		printf("Creation returned NULL.\n");
	}
	
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTDestroy(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int size = sizeof(nums) / sizeof(nums[0]);
	int i = 0;
	
	result = SUCCESS;
	
	bst = BSTCreate(IntCmp);
	
	/* put some values in */
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	/* use valgrind lol */
	
	return result;
}

status_ty TestBSTIsEmpty(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int size = sizeof(nums) / sizeof(nums[0]);
	int i = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* make sure returns true */
	if (!BSTIsEmpty(bst))
	{
		result = FAILURE;
		printf("Fresh BST registered as non-empty.\n");
	}
	
	/* put some values in */
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
	}
	
	/* make sure returns false */
	if (BSTIsEmpty(bst))
	{
		result = FAILURE;
		printf("Non-empty BST registered as empty.\n");
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTSize(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* make sure returns 0 */
	if (BSTSize(bst))
	{
		result = FAILURE;
		printf("Fresh BST yielded non-zero size.\n");
	}
	
	/* put some values in and make sure size keeps up*/
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
		if (BSTSize(bst) != i + 1)
		{
			result = FAILURE;
			printf("Size doesn't reflect amount of items inserted.\n");
		}
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTInsert(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int sorted_nums[] = { -20, -15, -10, -5, 0, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
	}
	
	/* starting from begin, do next until end and make sure all values are there in order */
	iter = BSTBegin(bst);
	
	for (i = 0; i < size; ++i)
	{
		data = *(int *)BSTGetData(iter);
		if (data != sorted_nums[i])
		{
			result = FAILURE;
			printf("Insert is not in order. Expected %d but yielded %d\n", sorted_nums[i], data);
		}
		
		iter = BSTNext(iter);
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTRemove(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int sorted_nums[] = { -20, -10, -5, 0, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
	}
	
	/* remove some value */
	
	/* starting from begin, do next until end and make sure all values are there in order */
	iter = BSTBegin(bst);
	iter = BSTNext(iter);
	
	BSTRemove(iter);
	iter = BSTBegin(bst);
	
	/* starting from begin, do next until end and make sure all values are there in order */
	for (i = 0; i < size - 1; ++i)
	{
		data = *(int *)BSTGetData(iter);
		if (data != sorted_nums[i])
		{
			result = FAILURE;
			printf("Remove is not in order. Expected %d but yielded %d\n", sorted_nums[i], data);
		}
		
		iter = BSTNext(iter);
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTGetData(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int num = -666;
	bst_iter_ty iter;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a value */
	iter = BSTInsert(bst, (void *)&num);
	data = *(int *)BSTGetData(iter);
	/* make sure value equals inserted value */
	if (data != num)
	{
		result = FAILURE;
		printf("GetData yielded a bad result. Expected %d but got %d.\n", num, data);
	}
	BSTDestroy(bst);
	return result;
}

status_ty TestBSTBegin(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	int min = 0;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
	}
	
	/* make sure returns smallest value */
	
	iter = BSTBegin(bst);
	min = GetMin(nums, size);
	data = *(int *)BSTGetData(iter);
	
	/* make sure value equals inserted value */
	if (data != min)
	{
		result = FAILURE;
		printf("Begin yielded a bad result. Expected %d but got %d.\n", min, data);
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTEnd(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	int max = 0;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		BSTInsert(bst, (void *)(nums + i));
	}
	
	/* make sure returns largest value */
	
	iter = BSTEnd(bst);
	max = GetMax(nums, size);
	data = *(int *)BSTGetData(iter);
	
	/* make sure value equals inserted value */
	if (data != max)
	{
		result = FAILURE;
		printf("End yielded a bad result. Expected %d but got %d.\n", max, data);
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTPrev(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int sorted_nums[] = { -20, -15, -10, -5, 0, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		iter = BSTInsert(bst, (void *)(nums + i));
	}
	
	/* starting with end, do prev */
	
	iter = BSTPrev(iter);
	data = *(int *)BSTGetData(iter);
	
	/* make sure it is the previous value */
	if (data != sorted_nums[size - 2])
	{
		result = FAILURE;
		printf("Prev yielded a bad result. Expected %d but got %d.\n", sorted_nums[size - 2], data);
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTNext(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int sorted_nums[] = { -20, -15, -10, -5, 0, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		iter = BSTInsert(bst, (void *)(nums + i));
	}
	
	/* starting with root, do next */
	
	iter = BSTBegin(bst);
	iter = BSTNext(iter);
	data = *(int *)BSTGetData(iter);
	
	/* make sure it is the next value */
	if (data != sorted_nums[1])
	{
		result = FAILURE;
		printf("Next yielded a bad result. Expected %d but got %d.\n", sorted_nums[1], data);
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTIterIsEqual(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty iter;
	bst_iter_ty runner;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		/* get iter of end */
		iter = BSTInsert(bst, (void *)(nums + i));
	}
	
	/* starting with begin, do next until end */
	runner = BSTBegin(bst);
	
	for (i = 0; i < size - 1; ++i)
	{
		runner = BSTNext(runner);
		/* make sure only root yields true */
		if (i == size - 2)
		{
			if (!BSTIterIsEqual(runner, iter))
			{
				result = FAILURE;
				printf("Equal iterators registered as different.\n");				
			}
		}
		else
		{
			if (BSTIterIsEqual(runner, iter))
			{
				result = FAILURE;
				printf("Different iterators registered as equals.\n");				
			}
		}
	}
	
	/* destroy */
	BSTDestroy(bst);
	
	return result;

	
	return result;
}

status_ty TestBSTFind(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int sorted_nums[] = { -20, -15, -10, -5, 0, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty expected_iter;
	bst_iter_ty iter;
	size_t index_of_found = 3;
	int to_find = sorted_nums[index_of_found];
	int not_to_find = -813756;
	int data = 0;
	
	result = SUCCESS;
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		/* get iter of end */
		BSTInsert(bst, (void *)(nums + i));
	}
	
	expected_iter = BSTBegin(bst);
	
	for (i = 0; i < index_of_found; ++i)
	{
		expected_iter = BSTNext(expected_iter);
	}
	
	/* search for an existing value */
	iter = BSTFind(bst, (void *)&to_find);
	data = *(int *)BSTGetData(iter);
	
	/* make sure it's the right iter */
	if (!BSTIterIsEqual(iter, expected_iter))
	{
		result = FAILURE;
		printf("Find returned the wrong iterator.\n");	
	}

	/* make sure it's the right data */
	if (data != to_find)
	{
		result = FAILURE;
		printf("Found data but value is wrong?!.\n");	
	}
	
	/* search for a non-existing value */
	iter = BSTFind(bst, (void *)&not_to_find);
	
	/* make sure it doesn't find anything */
	if (!BSTIterIsEqual(iter, BAD_ITER))
	{
		result = FAILURE;
		printf("Found data even though it wasn't there.\n");
	}
	
	BSTDestroy(bst);
	
	return result;
}

status_ty TestBSTForEach(void)
{
	status_ty result = ERROR;
	
	bst_ty *bst = NULL;
	int nums[] = { 0, -20, -10, -15, -5, 5, 10, 15, 20 };
	int sorted_nums[] = { -20, -15, -10, -5, 0, 5, 10, 15, 20 };
	size_t size = sizeof(nums) / sizeof(nums[0]);
	size_t i = 0;
	bst_iter_ty start;
	bst_iter_ty end;
	int multiplier = 10;
	
	int data = 0;
	
	result = SUCCESS;
	
	MultiplyArray(sorted_nums, size, multiplier);
	
	/* create bst */
	bst = BSTCreate(IntCmp);
	
	/* insert a few values */
	for (i = 0; i < size; ++i)
	{
		/* get iter of end */
		BSTInsert(bst, (void *)(nums + i));
	}
	
	start = BSTBegin(bst);
	end = BSTEnd(bst);
	
	/* multiply each by something using foreach */
	BSTForEach(start, end, MultiplyByNum, (void *)&multiplier);
	
	i = 0;
	/* starting with begin, do next until end and make sure all values have been updated */
	while (!BSTIterIsEqual(start, end))
	{
		data = *(int *)BSTGetData(start);
		
		if (sorted_nums[i] != data)
		{
			result = FAILURE;
			printf("Foreach didn't work on index %ld.\n", i);
		}
		
		++i;
		start = BSTNext(start);
	}
	
	BSTDestroy(bst);
	
	return result;
}

int IntCmp(void *int1, void *int2)
{
	return (*(int *)int1 - *(int *)int2);
}

int MultiplyByNum(void *data, void *multiplier)
{
	int *data_ = (int *)data;
	*data_ *= *(int *)multiplier;
	
	return 0;
}

int GetMin(int *array, int size)
{
	int result = INT_MAX;
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (array[i] < result)
		{
			result = array[i];
		}
	}
	
	return result;
}

int GetMax(int *array, int size)
{
	int result = INT_MIN;
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (array[i] > result)
		{
			result = array[i];
		}
	}
	
	return result;
}

void MultiplyArray(int *array, int size, int multiplier)
{
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{
		*(array + i) *= multiplier;
	}
}
