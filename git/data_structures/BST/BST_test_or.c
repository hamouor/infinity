#include<stdio.h>

#include"BST.h"

int comp(void* dat1, void* dat2)
{
    if(*(int*)dat1 > *(int*)dat2)
    {
        return 1;
    }
    else if(*(int*)dat1 < *(int*)dat2)
    {
        return -1;
    }
    return 0;
}

int main()
{
    bst_ty* new_bst = NULL;
    int arr[10] = {75, 65, 85, 55, 70, 80, 90, 45, 60, 67}, i = 0;
    bst_iter_ty iters[10];
    
    new_bst = BSTCreate(comp);

    if (!BSTIsEmpty(new_bst))
    {
        printf("isempty is fucking up\n");
    }
    
    for(;i < 10; ++i)
    {
        iters[i] = BSTInsert(new_bst, (void*)&arr[i]);
        if(BSTIterIsEqual(iters[i], BAD_ITER))
        {
            printf("insert is fucking up\n");
        }
    }

    if (BSTIsEmpty(new_bst))
    {
        printf("isempty is fucking up\n");
    }

    if(BSTSize(new_bst) != 10)
    {
        printf("size is fucking up\n");
    }

    if(!BSTIterIsEqual(BSTBegin(new_bst), iters[7]))
    {
        printf("begin is fucking up %d/n", *(int*)BSTGetData(BSTBegin(new_bst)));
    }
    if(!BSTIterIsEqual(BSTEnd(new_bst), iters[6]))
    {
        printf("end is fucking up %d/n", *(int*)BSTGetData(BSTEnd(new_bst)));
    }
    if(!BSTIterIsEqual(BSTPrev(iters[6]), iters[2]))
    {
        printf("prev is fucking up %d/n", *(int*)BSTGetData(BSTPrev(iters[6])));
    }
    if(!BSTIterIsEqual(BSTNext(iters[0]), iters[5]))
    {
        printf("next is fucking up %d/n", *(int*)BSTGetData(BSTNext(iters[0])));
    }


    BSTRemove(iters[0]);

    BSTRemove(iters[1]);

    BSTDestroy(new_bst);

    return 0;
}
