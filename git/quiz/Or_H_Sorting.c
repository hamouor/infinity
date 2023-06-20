#include <stddef.h>     /* size_t */
#include <assert.h>     /* assert */

void BubbleSort(int* arr, size_t N)
{
    int swaps = 1, i = 0;

    assert(arr);

    while(swaps)
    {
        swaps = 0;
        for(i = 0; i < N - 1; ++i)
        {
            if(*(arr + i) > *(arr + i + 1))
            {
                swaps = 1;
                Swap(arr, i, i+1);
            }
        }
    }
}

void SelectionSort(int* arr, size_t N)
{
    int* curr = NULL, *local_min = NULL, temp = 0;


    assert(arr);
    
    curr = arr;

    while(curr != arr + N - 1)
    {
        for(i = 0; i < N - (curr - arr); ++i)
        {
            if (*(curr + i) < *curr)
            {
                local_min = (curr + i);
            }
            temp = *local_min;
            *local_min = *curr;
            *curr = temp;
        }
    }

}

void InsertionSort(int* arr, size_t N)
{
    int i = 0, key = 0, j = 0;

    assert(arr);

    for (i = 1; i < N; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}