/*#include<stdio.h>

#include"sortlist.h"

void printlist(sortlist_ty *list);
int DatC(const void* d1, const void* d2);
int main()
{
    sortlist_ty *test = NULL, *test2 = NULL;
    int arr1[] ={-1, -6, 0, 100, 3}, arr2[] = {-20, -6, 15, 9, 1}, i = 0;
    test = SortListCreate(DatC);
    test2 = SortListCreate(DatC);
    for (; i < 5; ++i)
    {
        SortListInsert(test, (void*)&(arr1[i]));
        SortListInsert(test2, (void*)&(arr2[i]));
    }
    printlist(test);
    printlist(test2);
    
    test = SortListMerge (test, test2);

    printlist(test);
    printlist(test2);

    SortListDestroy(test);
    SortListDestroy(test2);
    return 0;
}

int DatC(const void* d1, const void* d2)
{
    if (*(int*)d1 < *(int*)d2)
    {
        return 1;
    }
    if(*(int*)d2 < *(int*)d1)
    {
        return -1;
    }
    return 0;
}

void printlist(sortlist_ty *list)
{
    sortlist_iter_ty run = SortListBegin(list);
    printf("list:");
    while(!SortListIterIsEqual(run, SortListEnd(list)))
    {
        printf("%d\n", *(int*)SortListGetData(run));
        run = SortListNext(run);
    }
}*/
#include <stdio.h>
#include <limits.h>

#include "sorted_list.h"

#define ERROR -1
#define SUCCESS 0
#define FAILURE 1

#define FALSE 0
#define TRUE 1

#define LESSTHAN -1
#define EQUALS 0
#define MORETHAN 1

#define UNUSED(x) (void)(x)

typedef int (*test_func)(void);

int TestBegin(void);
int TestEnd(void);
int TestNext(void);
int TestPrev(void);
int TestGetData(void);
int TestIterIsEqual(void);
int TestSize(void);
int TestIsEmpty(void);
int TestInsert(void);
int TestRemove(void);
int TestPopBack(void);
int TestPopFront(void);
int TestForEach(void);
int TestFind(void);
int TestFindIf(void);
int TestMerge(void);

static int IntCompare(const void *int1, const void *int2);
static int IntListComparison(sortlist_ty *list, int *arr, int size);
static int IntCompareToIterData(sortlist_iter_ty iter, int data);
static int IntMatch(void *data1, void *data2);
static void IntListPrinter(sortlist_ty *list);
static void IntArrayPrinter(int *array, int size);
static int MinIntInArray(int *arr, int size);
static int MaxIntInArray(int *arr, int size);
static int Multiply(void *num, void *multiplier);
static int IsPositive(void *num, void *unused);
static int IsMoreThanAMillion(void *num, void *unused);

int main(void)
{
	test_func tests[] = {
		TestBegin,
		TestEnd,
		TestNext,
		TestPrev,
		TestGetData,
		TestIterIsEqual,
		TestSize,
		TestIsEmpty,
		TestInsert,
		TestRemove,
		TestPopBack,
		TestPopFront,
		TestForEach,
		TestFind,
		TestFindIf,
		TestMerge
	};
	
	char *test_names[] = {
		"TestBegin",
		"TestEnd",
		"TestNext",
		"TestPrev",
		"TestGetData",
		"TestIterIsEqual",
		"TestSize",
		"TestIsEmpty",
		"TestInsert",
		"TestRemove",
		"TestPopBack",
		"TestPopFront",
		"TestForEach",
		"TestFind",
		"TestFindIf",
		"TestMerge"
	};
	
	int num_tests = sizeof(tests) / sizeof(tests[0]);
	int i = 0;
	int test_result = 0;
	
	for (i = 0; i < num_tests; ++i)
	{
		test_result = tests[i]();
		switch (test_result)
		{
			case ERROR:
				printf("Error in running test %d: %s().\n", i + 1, test_names[i]);
				break;
			case SUCCESS:
				printf("%s() works according to specification.\n", test_names[i]);
				break;
			case FAILURE:
				printf("%s() failed! See details above!.\n", test_names[i]);
				break;
			default:
				break;
		}
	}
	
	return 0;
}

int TestBegin(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	sortlist_iter_ty result_iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListBegin(list);
	
	if (FALSE == IntCompareToIterData(result_iter, MinIntInArray(values, size)))
	{
		printf("Begin() didn't return the list head OR items are not sorted correctly.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestEnd(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	sortlist_iter_ty result_iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListPrev(SortListEnd(list));
	
	if (FALSE == IntCompareToIterData(result_iter, MaxIntInArray(values, size)))
	{
		printf("Begin() didn't return the list end OR items are not sorted correctly.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestNext(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	sortlist_iter_ty result_iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListBegin(list);
	
	for (i = 0; i < size; ++i)
	{
		if (FALSE == IntCompareToIterData(result_iter, sorted_values[i]))
		{
			printf("Next() didn't retrieve the correct next iterator.\n");
			test_status = FAILURE;
	
			SortListDestroy(list);
			return test_status;
		}
		
		result_iter = SortListNext(result_iter);
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestPrev(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	sortlist_iter_ty result_iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListPrev(SortListEnd(list));
	
	for (i = 0; i < size; ++i)
	{
		if (FALSE == IntCompareToIterData(result_iter, sorted_values[size - i - 1]))
		{
			printf("Prev() didn't retrieve the correct previous iterator.\n");
			test_status = FAILURE;
	
			SortListDestroy(list);
			return test_status;
		}
		
		result_iter = SortListPrev(result_iter);
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestGetData(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int value = -666;
	sortlist_iter_ty result_iter;
	
	SortListInsert(list, &value);
	
	result_iter = SortListBegin(list);
	
	if (FALSE == IntCompareToIterData(result_iter, value))
	{
		printf("GetData() didn't retrieve the correct data.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestIterIsEqual(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	sortlist_iter_ty idle_iter;
	sortlist_iter_ty running_iter;
	int idle_index = 3;
	
	/* push a few items */
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	/* make two iters, set one in the beginning and one in the middle */
	idle_iter = running_iter = SortListBegin(list);
	
	for (i = 0; i <= idle_index; ++i)
	{
		idle_iter = SortListNext(idle_iter);
	}
	
	/* advance the first and make sure function returns 1 only at the right spot */
	for (i = 0; i < size; ++i)
	{
		running_iter = SortListNext(running_iter);
		if (idle_index == i)
		{
			if (FALSE == SortListIterIsEqual(running_iter, idle_iter))
			{
				printf("Iters are registered not equal where they're expected to be equal.\n");
				test_status = FAILURE;
			}
		}
		else
		{
			if (TRUE == SortListIterIsEqual(running_iter, idle_iter))
			{
				printf("Iters are registered equal where they're expected to be not equal.\n");
				test_status = FAILURE;
			}
		}
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestSize(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	int result = -1;
	
	/* make sure function returns 0 */
	result = SortListSize(list);
	if (0 != result)
	{
		printf("Empty list size registered as non-zero.\n");
		test_status = FAILURE;
	}
	
	/* push a few items */
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result = SortListSize(list);
	/* make sure function returns number of pushed items */
	if (size != result)
	{
		printf("Nonempty list size was counted wrong. Expected size was %d, but function returned %d.\n", size, result);
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestIsEmpty(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	int result = -1;
	
	result = SortListIsEmpty(list);
	if (TRUE != SortListIsEmpty(list))
	{
		printf("Empty list registered as non-empty.\n");
		test_status = FAILURE;
	}
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	if (FALSE != SortListIsEmpty(list))
	{
		printf("Non-empty list registered as empty.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestInsert(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -666, -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int insert1 = -666;
	int insert2 = 0;
	int i = 0;
	sortlist_iter_ty result_iter;
	sortlist_iter_ty end_iter;
	sortlist_iter_ty iter;
	int flag = 0;
	
	iter = SortListInsert(list, &insert1);
	
	result_iter = SortListBegin(list);
	
	if (FALSE == IntCompareToIterData(result_iter, insert1))
	{
		printf("Insert into empty list didn't insert the right value, or at all.\n");
		test_status = FAILURE;

		SortListDestroy(list);
		return test_status;
	}
	
	if (FALSE == SortListIterIsEqual(result_iter, iter))
	{
		printf("Insert() didn't return the iterator with the new data.\n");
		test_status = FAILURE;
	}
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListBegin(list);
	
	for (i = 0; i < size + 1; ++i)
	{
		if (FALSE == IntCompareToIterData(result_iter, sorted_values[i]))
		{
			printf("Inserted values weren't sorted correctly.\n");
			test_status = FAILURE;
	
			SortListDestroy(list);
			return test_status;
		}
		
		result_iter = SortListNext(result_iter);
	}
	
	SortListInsert(list, &insert2);
	
	result_iter = SortListBegin(list);
	end_iter = SortListEnd(list);
	
	while(FALSE == SortListIterIsEqual(result_iter, end_iter))
	{
		if (*(int *)SortListGetData(result_iter) == insert2)
		{
			flag = 1;
			
			if (MORETHAN == IntCompare(SortListGetData(SortListPrev(result_iter)), SortListGetData(result_iter)))
			{
				printf("Inserted value after value that's larger.\n");
				test_status = FAILURE;
			}
			
			if (LESSTHAN == IntCompare(SortListGetData(SortListNext(result_iter)), SortListGetData(result_iter)))
			{
				printf("Inserted value before value that's smaller.\n");
				test_status = FAILURE;
			}
			
			if (FAILURE == test_status)
			{
				printf("Inserted %d after %d and before %d.\n", 
				*(int *)SortListGetData(result_iter), 
				*(int *)SortListGetData(SortListPrev(result_iter)), 
				*(int *)SortListGetData(SortListNext(result_iter)));
	
				SortListDestroy(list);
				return test_status;
			}
		}
		
		result_iter = SortListNext(result_iter);
	}
	
	if (0 == flag)
	{
		printf("Couldn't find inserted value in list after insertion.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestRemove(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -4, -2, -1, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	int remove_index = 3;
	sortlist_iter_ty result_iter;
	sortlist_iter_ty iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	iter = SortListBegin(list);
	
	result_iter = SortListRemove(iter);
	
	iter = SortListBegin(list);
	
	if (FALSE == SortListIterIsEqual(result_iter, iter))
	{
		printf("Remove() doesn't return correct iterator OR messes up the dummy head when removing first value.\n");
		test_status = FAILURE;
	}
	
	if (size - 1 != SortListSize(list))
	{
		printf("List has unexpected size after remove.\n");
		test_status = FAILURE;
	}
	
	for (i = 0; i < remove_index; ++i)
	{
		result_iter = SortListNext(result_iter);
	}
	
	SortListRemove(result_iter);
	
	iter = SortListBegin(list);
	
	for (i = 0; i < size - 2; ++i)
	{
		if (FALSE == IntCompareToIterData(iter, sorted_values[i]))
		{
			printf("Remove() got rid of the wrong piece of data.\n");
			test_status = FAILURE;
		}
		
		iter = SortListNext(iter);
	}
	
	iter = SortListPrev(SortListEnd(list));
	
	result_iter = SortListRemove(iter);
	
	iter = SortListEnd(list);
	
	if (FALSE == SortListIterIsEqual(result_iter, iter))
	{
		printf("Remove() doesn't return correct iterator OR messes up the dummy tail when removing last value.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestPopBack(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	void *data = NULL;
	sortlist_iter_ty iter;
	
	/* push a few items */
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	/* pop an item and make sure the new previous of list end matches penultimate pushed item */
	data = SortListPopBack(list);
	iter = SortListPrev(SortListEnd(list));
	
	if (FALSE == IntCompareToIterData(iter, sorted_values[size - 2]))
	{
		printf("After one PopBack(), the end value doesn't match the item that was pushed before last.\n");
		test_status = FAILURE;
	}
	
	/* also check that the data matches the last pushed item */
	if (*(int *)data != sorted_values[size - 1])
	{
		printf("After one PopBack(), the popped value doesn't match the item that was pushed last.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestPopFront(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	void *data = NULL;
	sortlist_iter_ty iter;
	
	/* push a few items */
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	/* pop an item and make sure the new list begin matches second pushed item */ 
	data = SortListPopFront(list);
	iter = SortListBegin(list);
	
	if (FALSE == IntCompareToIterData(iter, sorted_values[1]))
	{
		printf("After one PopFront(), the head value doesn't match the item that was pushed second.\n");
		test_status = FAILURE;
	}
	
	/* also check that the data matches the first pushed item */
	if (*(int *)data != sorted_values[0])
	{
		printf("After one PopFront(), the popped value doesn't match the item that was pushed first.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestForEach(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int mul_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	int result = -1;
	int multiplier = 10;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	for (i = 0; i < size; ++i)
	{
		mul_values[i] = sorted_values[i] * multiplier;
	}
	
	/* make a multiply() function and run it on the first list */
	result = SortListForEach(SortListBegin(list), SortListEnd(list), Multiply, &multiplier);
	if (SUCCESS != result)
	{
		printf("ForEach() user function failure.\n");
		test_status = FAILURE;
	}
	
	if (FAILURE == IntListComparison(list, mul_values, size))
	{
		printf("ForEach() wasn't performed correctly.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestFind(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	int to_find = 4;
	int not_to_find = 0;
	sortlist_iter_ty iter;
	sortlist_iter_ty result_iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListFind(list, SortListBegin(list), SortListEnd(list), sorted_values + to_find);
	
	/* check if it's the right iterator when it's found */
	iter = SortListBegin(list);
	
	for(i = 0; i < to_find; ++i)
	{
		iter = SortListNext(iter);
	}
	
	if (FALSE == SortListIterIsEqual(iter, result_iter))
	{
		printf("Find() returned the wrong iterator.\n");
		test_status = FAILURE;
	}
	
	if (FALSE == IntCompareToIterData(result_iter, sorted_values[to_find]))
	{
		printf("Found something other than the requested value in the list.\n");
		test_status = FAILURE;
	}
	
	result_iter = SortListFind(list, SortListBegin(list), SortListEnd(list), &not_to_find);
	
	/* check if it's the right iterator when it's found */
	iter = SortListEnd(list);
	
	if (FALSE == SortListIterIsEqual(iter, result_iter))
	{
		printf("Find() found something matching the condition when there was no such thing.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestFindIf(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list = SortListCreate(IntCompare);
	int values[] = { -1, 2, 4, 5, -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size = sizeof(values) / sizeof(values[0]);
	int i = 0;
	int to_find = 4;
	sortlist_iter_ty iter;
	sortlist_iter_ty result_iter;
	
	for (i = 0; i < size; ++i)
	{
		SortListInsert(list, values + i);
	}
	
	result_iter = SortListFindIf(SortListBegin(list), SortListEnd(list), IsPositive, NULL);
	
	/* check if it's the right iterator when it's found */
	iter = SortListBegin(list);
	
	for(i = 0; i < to_find; ++i)
	{
		iter = SortListNext(iter);
	}
	
	if (FALSE == SortListIterIsEqual(iter, result_iter))
	{
		printf("FindIf() returned the wrong iterator.\n");
		test_status = FAILURE;
	}
	
	if (FALSE == IntCompareToIterData(result_iter, sorted_values[to_find]))
	{
		printf("FindIf() found something other than the requested value in the list.\n");
		test_status = FAILURE;
	}
	
	result_iter = SortListFindIf(SortListBegin(list), SortListEnd(list), IsMoreThanAMillion, NULL);
	
	/* check if it's the right iterator when it's found */
	iter = SortListEnd(list);
	
	if (FALSE == SortListIterIsEqual(iter, result_iter))
	{
		printf("FindIf() found something matching the condition when there was no such thing.\n");
		test_status = FAILURE;
	}
	
	SortListDestroy(list);
	
	return test_status;
}

int TestMerge(void)
{
	int test_status = SUCCESS;
	sortlist_ty *list1 = SortListCreate(IntCompare);
	sortlist_ty *list2 = SortListCreate(IntCompare);
	sortlist_ty *result_list = NULL;
	int values1[] = { -1, 2, 4, 5 };
	int values2[] = { -2, -6, -4, 100 };
	int sorted_values[] = { -6, -4, -2, -1, 2, 4, 5, 100 };
	int size1 = sizeof(values1) / sizeof(values1[0]);
	int size2 = sizeof(values2) / sizeof(values2[0]);
	int sorted_size = sizeof(sorted_values) / sizeof(sorted_values[0]);
	int i = 0;
	
	for (i = 0; i < size1; ++i)
	{
		SortListInsert(list1, values1 + i);
	}
	
	for (i = 0; i < size2; ++i)
	{
		SortListInsert(list2, values2 + i);
	}
	
	result_list = SortListMerge(list1, list2);
	
	if (TRUE != SortListIsEmpty(list2))
	{
		printf("Source list is not empty after merge.\n");
		test_status = FAILURE;
	}
	
	if (FAILURE == IntListComparison(result_list, sorted_values, sorted_size))
	{
		printf("Merge was performed incorrectly.\n");
		printf("Expected:\n");
		IntArrayPrinter(sorted_values, sorted_size);
		printf("Result:\n");
		IntListPrinter(result_list);
		test_status = FAILURE;
	}

	return test_status;
}

static int IntCompareToIterData(sortlist_iter_ty iter, int data)
{
	int value = 0;
	
	value = *(int *)SortListGetData(iter);
	if (value == data)
	{
		return TRUE;
	}
	else
	{
		printf("Value comparison mismatch!\nValue in iter was %d.\nGiven data was %d.\n", value, data);
		return FALSE;
	}
}

static int IntCompare(const void *int1, const void *int2)
{
	int val1 = *(int *)int1;
	int val2 = *(int *)int2;
	return ((val1 > val2) ? 1 : ((val1 < val2) ? -1 : 0));
}

static int MinIntInArray(int *arr, int size)
{
	int result = INT_MAX;
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (*(arr + i) < result)
		{
			result = *(arr + i);
		}
	}
	
	return result;
}

static int MaxIntInArray(int *arr, int size)
{
	int result = INT_MIN;
	int i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (*(arr + i) > result)
		{
			result = *(arr + i);
		}
	}
	
	return result;
}

static int Multiply(void *num, void *multiplier)
{
	int *num_int = (int *)num;
	*num_int *= *(int *)multiplier;
	
	return SUCCESS;
}

static int IntListComparison(sortlist_ty *list, int *arr, int size)
{
	sortlist_iter_ty iter = SortListBegin(list);
	sortlist_iter_ty end = SortListEnd(list);
	int i = 0;
	
	for (i = 0; i < size; ++i, iter = SortListNext(iter))
	{
		if (TRUE == SortListIterIsEqual(iter, end))
		{
			printf("List ended before int array. List length was %d while array had size %d.\n", i + 1, size);
			IntListPrinter(list);
			IntArrayPrinter(arr, size);
			return FAILURE;
		}
		
		if (FALSE == IntCompareToIterData(iter, *(arr + i)))
		{
			printf("List comparison mismatch! At index %d, List contained %d and array contained %d!\n", i, *(int *)SortListGetData(iter), *(arr + i));
			return FAILURE;
		}
	}
	
	if (FALSE == SortListIterIsEqual(iter, end))
	{
		printf("Int array ended before list. List length was %d while array had size %d.\n", i + 1, size);
		IntListPrinter(list);
		IntArrayPrinter(arr, size);
		return FAILURE;
	}
	
	return SUCCESS;
}

static void IntListPrinter(sortlist_ty *list)
{
	sortlist_iter_ty iter = SortListBegin(list);
	printf("List:\n");
	while(FALSE == SortListIterIsEqual(iter, SortListEnd(list)))
	{
		printf("%d, ", *(int *)SortListGetData(iter));
		iter = SortListNext(iter);
		if (FALSE == SortListIterIsEqual(iter, SortListEnd(list)))
		{
			printf(", ");
		}
	}
	printf("\n");
}

static void IntArrayPrinter(int *array, int size)
{
	int i = 0;
	printf("Array:\n");
	for (i = 0; i < size; ++i)
	{
		printf("%d", *(array + i));
		if (i < size - 1)
		{
			printf(", ");
		}
	}
	printf("\n");
}

static int IsPositive(void *num, void *unused)
{
	UNUSED(unused);
	
	return *(int *)num > 0;
}

/* lol */
static int IsMoreThanAMillion(void *num, void *unused)
{
	UNUSED(unused);
	
	return *(int *)num > 1000000;
}
