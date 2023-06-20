#include <stdio.h>      /* printf */

#include "BST.h"

#define ARR_SIZE       14

/* compared two ints returns:
 (-) if data1<data2 | (+) data1>data2 | 0 if equal */
int intsCmp(void *data1, void *data2);
/* doubles int with parameter */
int ForEachFunc(void *data, void *parameter);
void PrintTree(bst_ty *bst);

int main()
{
    bst_ty *new_bst = NULL;
    bst_iter_ty iter, iter1 = BAD_ITER, iter2 = BAD_ITER;
    bst_iter_ty iter_arr[ARR_SIZE] = {NULL};
    int arr[ARR_SIZE] = {-2, -23, 5, -7, 10, 11, 25, 0, 8, 6, -4, -24, 9, 20};
    int sorted_arr[ARR_SIZE] = {-24, -23, -7, -4, -2, 0, 5, 6, 8, 9, 10, 11, 20, 25};
    int arr_for_each[ARR_SIZE] = {-48, -46, -14, -8, -4, 0, 10, 12, 16, 18, 20, 22, 40, 50};
    int arr_from_bst[ARR_SIZE] = {0};
	int i = 0, failed = 0, parameter = 2;



    /* start new bst */
    new_bst = BSTCreate(intsCmp);
    /* check params */
    if (!BSTIsEmpty(new_bst))
    {
        printf("bst isnt empty after creation, madafaka\n");
    }
    if (0 != BSTSize(new_bst))
    {
        printf("bst size (%lu) is bullshit after creation, madafaka\n", BSTSize(new_bst));
    }    

    /* fill up and check param as you go */
    for (i = 0; ARR_SIZE > i; ++i)
    {
        iter = BSTInsert(new_bst, (void *)&arr[i]);
        iter_arr[i] = iter;
        if (BSTIterIsEqual(BAD_ITER, iter))
        {
            printf("insertion of %d failed, check ya shit\n", arr[i]);
        }
        if (BSTIsEmpty(new_bst))
        {
            printf("bst is empty after insertion num %d, what the hell??\n", i);
        }
        if (i + 1 != (int)BSTSize(new_bst))
        {
            printf("bst size (%lu) is bullshit after insertion num %d, fix it ASAP\n", BSTSize(new_bst), (i + 1));
        }
    }

    /* pass through values and validate insertions */
    iter = BSTBegin(new_bst);
    for (i = 0; ARR_SIZE > i; ++i)
    {
        arr_from_bst[i] = *(int *)BSTGetData(iter);

        if (sorted_arr[i] != *(int *)BSTGetData(iter))
        {
            failed = 1;
        }
        iter = BSTNext(iter);
    }

    if (failed)
    {
        printf("validation after insertion failed:\n bst step next result: ");
        
        for (i = 0; ARR_SIZE > i; ++i)
        {
            printf("%d\n", arr_from_bst[i]);
        }
    }

    /* remove and check */
    i = sorted_arr[5]; /* 0 */
    iter = BSTFind(new_bst, (void *)&i);
    if (i != *(int *)BSTGetData(iter))
    {
        printf("find (%d) didnt return the right iter (instead of %d)\n ", *(int *)BSTGetData(iter), i);
    }
    if (i != *(int *)BSTRemove(iter))
    {
        printf("remove didnt return the right value\n ");
    }    
    if ((ARR_SIZE - 1) != (int)BSTSize(new_bst))
    {
        printf("bst size (%lu) is bullshit after removing 0 mannnnnnnnn\n", BSTSize(new_bst));
    }

    i = sorted_arr[1]; /* -23 */
    iter = BSTFind(new_bst, (void *)&i);
    if (i != *(int *)BSTGetData(iter))
    {
        printf("find (%d) didnt return the right iter (instead of %d)\n ", *(int *)BSTGetData(iter), i);
    }
    if (i != *(int *)BSTRemove(iter))
    {
        printf("remove didnt return the right value\n ");
    }    
    if ((ARR_SIZE - 2) != (int)BSTSize(new_bst))
    {
        printf("bst size (%lu) is bullshit after removing 0 mannnnnnnnn\n", BSTSize(new_bst));
    }   

    i = sorted_arr[10]; /* 10 */
    iter = BSTFind(new_bst, (void *)&i);
    if (i != *(int *)BSTGetData(iter))
    {
        printf("find (%d) didnt return the right iter (instead of %d)\n ", *(int *)BSTGetData(iter), i);
    }
    if (i != *(int *)BSTRemove(iter))
    {
        printf("remove didnt return the right value\n ");
    }    
    fflush(stdout);
    if ((ARR_SIZE - 3) != (int)BSTSize(new_bst))
    {
        printf("bst size (%lu) is bullshit after removing 0 mannnnnnnnn\n", BSTSize(new_bst));
    }   

    /* destroy bst */
    BSTDestroy(new_bst);

	new_bst = BSTCreate(intsCmp);
    for (i = 0; ARR_SIZE > i; ++i)
    {
        iter = BSTInsert(new_bst, (void *)&arr[i]);
        iter_arr[i] = iter;
	}

	i = BSTForEach(BSTBegin(new_bst), BSTEnd(new_bst), ForEachFunc, (void *)&parameter);
	failed = 0;
	iter = BSTBegin(new_bst);
	for (i = 0; ARR_SIZE > i; ++i)
    {
		if (arr_for_each[i] != *(int *)BSTGetData(iter))
		{
			failed = 1;
		}
		iter = BSTNext(iter);
	}	
	if (failed)
	{
		PrintTree(new_bst);
	}
	

    return 0;
}

int intsCmp(void *data1, void *data2)
{
    return *(int *)data1 - *(int *)data2;
}

int ForEachFunc(void *data, void *parameter)
{
	*(int *)data *= *(int *)parameter;
	return 0;
}

void PrintTree(bst_ty *bst)
{
    bst_iter_ty iter = BSTBegin(bst);

    printf("\n");
    while (BSTIterIsEqual(BAD_ITER, iter))
    {
        printf("%d\t", *(int *)BSTGetData(iter));
        iter = BSTNext(iter);
    }
    printf("\n");
    fflush(stdout);
}