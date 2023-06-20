#include<stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*compar)(void*, void*);

void MergeR(int *out, int *arr1, int n1, int *arr2, int n2);
int MergeSort(int *arr, size_t n);
void MergeSortR(int* arr, int *sorted, size_t size);
int Partition(void* base, size_t nmemb, size_t size, compar func);
void Qsort(void* base, size_t nmemb, size_t size, compar func);
void swap(void* a, void* b, size_t size);
int func(void* a, void* b);

int BinarySearch(int* arr, size_t n, int k)
{
    int i = 0, j = n - 1, mid = n / 2;

    while (i <= j)
    {
        if(arr[i + mid] == k)
        {
            return i + mid;
        }
        
        if(arr[i + mid] < k)
        {
            i += mid + 1;
        }
        
        else
        {
            j = i + mid - 1;
        }
       
        mid = (j - i) / 2;
    }

    return -1;
    
}

int BinarySearchR(int* arr, int l, int r, int k)
{
    int res = 0, mid  = 0;

    if(r - l >= 0)
    {   
        mid = l + (r - l) / 2;
        res = arr[mid];

        if(res == k)
        {
            return mid;
        }

        if(res > k)
        {
            return BinarySearchR(arr, l, mid - 1, k);
        }

        return BinarySearchR(arr, mid + 1, r , k);
    }
    return -1;
}

int MergeSort(int *arr, size_t n)
{
    int *sorted = NULL;

    sorted = (int*)malloc(sizeof(int) * n);
    if(!sorted)
    {
        return 1;
    }

    MergeSortR(arr, sorted, n);

    free(sorted);

    return 0;
}

void MergeSortR(int* arr, int *sorted, size_t size)
{
    int n1 = size / 2, temp = 0;
    int n2 = size - n1;
    
    if (size == 1)
    {
        sorted[0] = arr[0];
        return;
    }
    
    if(size == 2)
    {
        if(arr[1] < arr[0])
        {
            temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
            return;
        }
    }

    MergeSortR(arr, sorted, n1);
    MergeSortR(arr + n1, sorted + n1, n2);
    MergeR(sorted, arr, n1, arr + n1, n2);
}

void MergeR(int *sorted, int *arr1, int n1, int *arr2, int n2)
{
    int i = 0, j = 0;

    while(i < n1 && j < n2)
    {
        if (arr1[i] < arr2[j])
        {
            sorted[i + j] = arr1[i];
            ++i;
        }
        else
        {
            sorted[i + j] = arr2[j];
            ++j;
        }
    }
    
    while(i < n1)
    {
        sorted[i + j] = arr1[i];
        ++i;
    }
    
    while(j < n2)
    {
        sorted[i + j] = arr2[j];
        ++j;
    }

    for(i = 0; i < n1 + n2; ++i)
    {
        arr1[i] = sorted[i];
    }
}

void Qsort(void* base, size_t nmemb, size_t size, compar func)
{
    size_t pi = 0;

    if(nmemb > 1)
    {
        pi = Partition(base, nmemb, size, func);
        if (pi > 0)
        {
            Qsort(base, pi , size, func);
        }
        if(pi < nmemb)
        {
            Qsort((void*)((char*)base + (pi + 1) * size), nmemb - pi - 1, size, func);
        }    
    }  
}

int Partition(void* base, size_t nmemb, size_t size, compar func)
{
    void* pivot = NULL;
    int i = 0, k = 1;
    if(nmemb < 2)
    {
        return 0;
    }
    pivot = (void*)((char*)base + (nmemb - 1) * size);
    while(i < nmemb - k)
    {
        if(func((void*)((char*)base + i * size), pivot) < 0)
        {
            ++i;
        }
        else
        {
            swap((void*)((char*)base + i * size), (void*)((char*)pivot - k * size), size);
            ++k;
        }
    }
    swap((void*)((char*)pivot - (k - 1) * size), pivot, size);
    return nmemb - k;
}

int func(void* a, void* b)
{
    return (*(int*)a - *(int*)b);
}

void swap(void* a, void* b, size_t size)
{
    char temp;
    size_t i = 0;

    for(;i < size; ++i)
    {
        temp = *((char*)a + i);
        *((char*)a + i) = *((char*)b + i);
        *((char*)b + i) = temp;
    }
}