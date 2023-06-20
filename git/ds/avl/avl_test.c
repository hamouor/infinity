#include"avl.h"

#include <stdio.h>

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
    avl_ty* avl = NULL;
    int arr[10] = {75, 65, 85, 55, 70, 80, 90, 45, 60, 67}, i = 0;
    int arr2[10] = {1,2,3,4,5,6,7,8,9,10};
    
    
    avl = AVLCreate(comp);
    
    for(i = 0; i < 10; ++i)
    {
        AVLInsert(avl, (void*)&arr2[i]);
    }
    PrintTree(avl);

    printf("height %d\nsize:%ld\n", AVLHeight(avl), AVLSize(avl));
    
    AVLRemove(avl, (void*)&arr2[0]);
    AVLRemove(avl, (void*)&arr2[1]);
    AVLRemove(avl, (void*)&arr2[2]);
    AVLRemove(avl, (void*)&arr2[3]);
    /*AVLRemove(avl, (void*)&arr2[7]);*/


    PrintTree(avl);

    printf("height %d\nsize:%ld\n", AVLHeight(avl), AVLSize(avl));
    AVLDestroy(avl);
    
    return 0;
}



