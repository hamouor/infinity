#include"heap.h"
#include <stdio.h>

int comp(const void* data1, const void* data2);

int ismatch(const void *data1, const void *data2);


int main()
{
    heap_ty *test = NULL;
    int arr[] = {15, 20, 3, 9, 51, 200, 0, 201}, i = 0;
    size_t size = sizeof(arr) / sizeof(int);

    test = HeapCreate(comp);

    for(; i < size; ++i)
    {
        HeapPush(test, (void*)&(arr[i]));
    }

    if(HeapSize(test) != size)
    {
        printf("size is fucking up. should be:%ld, but is: %ld", size, HeapSize(test));
    }
    
    if(*(int*)HeapPeek(test) != arr[7])
    {
        printf("peek or insert is fucking up. should be:%d, but is: %d", arr[7], *(int*)HeapPeek(test));
    }
    /*for(i = 0; i < size; ++i)
    {
        printf("%d\n", *(int*)HeapPop(test));
    }
    for(; i < size; ++i)
    {
        HeapPush(test, (void*)&(arr[i]));
    }*/
    HeapRemove(test, ismatch, (void*)&arr[2]);
    for(i = 0; i < size-1; ++i)
    {
        printf("%d\n", *(int*)HeapPop(test));
    }
    HeapDestroy(test);

    return 0;
}

int comp(const void* data1, const void* data2)
{
    int a = 0, b = 0;

    a = *(int*)data1;
    b = *(int*)data2;

    return a - b;
} 

int ismatch(const void *data1, const void *data2)
{
    int a = 0, b = 0;

    a = *(int*)data1;
    b = *(int*)data2;

    return a == b;
}