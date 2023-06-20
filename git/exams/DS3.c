#include<stdlib.h>

/**Q1**/
typedef struct my_arr
{
    int* vals;
    size_t size;
    char* upd;
    int default;
    char up;
}arry;

void Setval(int idx, int val, arry *arr)
{
    *(arr->vals + idx) = val;
    *(arr->upd + idx) = arr->up;
}

int Getval(int idx, arry *arr)
{
    if(arr->up == *(arr->upd + idx))
    {
        return *(arr->vals + idx);
    }
    else
    {
        return arr->default;
    }
}

void Setall(int val, arry *arr)
{
    arr->default = val;
    ++arr->up;
}

/**Q2**/

void SOT(int * arr, size_t size, int sum)
{
    size_t* bita = NULL;
    size_t* curr = NULL;
    int i = 0, remainder = 0;

    bita  = calloc(INT_MAX * 2 / sizeof(size_t) / 8);

    for(i = 0; i < size; ++i)
    {
        curr = *(arr + i) / 8;
        *(bita + curr) |= (1 << (*(arr + i) % 8));
    }
    
    for(i = 0; i < size; ++i)
    {
        if(*(arr + i) > sum)
        {
            remainder = sum - *(arr + i);
            curr = remainder / 8;
            if(1 & (*(bita + curr) >> remainder % 8))
            {
                printf("found\n");
                free(bita);
                return;
            }
        }
    }
    free(bita);
    printf("not found\n");
}

/**Q3**/

int UT(char* arr, size_t size, char find)
{
    int ret_val = 0, i = 0;

    for(i = 0; i < size; ++i)
    {
        ret_val += (find == *(arr + i));
    }

    return !!ret_val;
}

/**Q4**/

void Rot(char *arr, size_t size, size_t N)
{
    char* aux = NULL;
    int i = 0;

    aux = malloc(size);

    for(i = 0; i < size; ++i)
    {
        *(aux + ((i + N) % size)) = *(arr + i);
    }

    for(i = 0; i < size; ++i)
    {
        *(arr + i) = *(aux + i);
    }

    free(aux);
}

/**Q5**/

#define MIN(x, y) (x < y)? x:y
#define MAX(x, y) (x > y)? x:y

int Islands(int** arr, size_t dim1, size_t dim2)
{
    int counter = 2;
    int  i = 0, j = 0;

    for(i = 0; i < dim1; ++i)
    {
        for(j = 0; j < dim2; ++j)
        {
            if(arr[i][j] == 1)
            {
                color(arr, dim1, dim2, i ,j, counter);
                ++counter;
            }
        }
    }
    return counter - 1;
}

void color(int ** arr, size_t dim1, size_t dim2, int i, int j, col)
{
    if(arr[i][j] == 1)
    {
        arr[i][j] = col;
        color(arr, dim1, dim2, MIN(i + 1, dim1), j, col);
        color(arr, dim1, dim2, i, MIN(j + 1, dim2), col);
        color(arr, dim1, dim2, MAX(i - 1, 0), j, col);
        color(arr, dim1, dim2, i, MAX(j - 1, 0), col);
    }
    else
    {
        return;
    }
}

/**Q8**/

int Multi(int a, int b)
{
    if(a == 1)
    {
        return b;
    }
    else
    {
        return b + Multi(a - 1, b);
    }
}

int Add(int a)
{
    if(!(a & 1))
    {
        return a | 1;
    }
    else
    {
        return add(a>>1)<<1;
    }
}

/**Q9**/

#include "slist.h"
#include "slist.c"

slist_ty * pivot(slist_ty* list, int pivot)
{
    slist_node_ty* curr = NULL;
    slist_ty* aux = NULL;

    aux = SlistCreate();

    curr = list->head;
    while(curr)
    {
        if(curr->val < pivot)
        {
            SlistInsertBefore(SlistBegin(aux), curr->data)
        }
    }
}

/**13**/

