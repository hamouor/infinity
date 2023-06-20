#include <assert.h> /*assert*/
#include <stdlib.h>

#include "vector.h"
#include "heap.h"

#define MIN(x,y)    (((x)<(y))?(x):(y))

struct heap
{
    vector_ty *vec;
    compfunc_ty comp;
};


static void HeapifyUp(heap_ty *heap, size_t index);

static void HeapifyDown(heap_ty *heap, size_t index);


heap_ty *HeapCreate(compfunc_ty comp_func)
{
    heap_ty *new = NULL;

    assert(comp_func);

    new = (heap_ty*)malloc(sizeof(heap_ty));
    if(!new)
    {
        return NULL;
    }
    new->vec = VectorCreate(sizeof(void*), 10);
    if(!new->vec)
    {
        free(new);
        return NULL;
    }
    
    new->comp = comp_func;

    return new;
}

void HeapDestroy(heap_ty *heap)
{
    assert(heap);

    VectorDestroy(heap->vec);
    free(heap);
}

size_t HeapSize(const heap_ty *heap)
{
    assert(heap);

    return VectorSize(heap->vec);
}

int HeapIsEmpty(const heap_ty *heap)
{
    assert(heap);

    return !HeapSize(heap);
}

void *HeapPeek(const heap_ty *heap)
{
    void **fake = NULL;

    assert(heap);

    fake = VectorGetAccessToElement(heap->vec, 0);
    return(*fake);
}

int HeapPush(heap_ty *heap, void *data)
{
    int res = 0;

    assert(heap && data);

    res = VectorPushBack(heap->vec, &data);

    if(!res)
    {
        HeapifyUp(heap, HeapSize(heap) - 1);
    }

    return res;

}

void *HeapPop(heap_ty *heap)
{
    void **temp = NULL, *ret_val = NULL, **last = NULL;

    assert(heap);

    temp = VectorGetAccessToElement(heap->vec, 0);
    ret_val = *temp;
    last = VectorGetAccessToElement(heap->vec, HeapSize(heap) - 1);

    *temp = *last;

    VectorPopBack(heap->vec);

    HeapifyDown(heap, 0);

    return ret_val;
}

void *HeapRemove(heap_ty *heap, ismatch_ty ismatch, void *param)
{
    size_t i = 0;
    int j = -1;
    void **curr = NULL, **last = NULL, *ret_val = NULL;

    assert(heap && ismatch && param);

    for(; i < HeapSize(heap); ++i)
    {
        curr = VectorGetAccessToElement(heap->vec, i);
        if(ismatch(*curr, param))
        {
            j = i;
            break;
        }
    }

    if(j >= 0)
    {
        last = VectorGetAccessToElement(heap->vec, HeapSize(heap) - 1);
        ret_val = *curr;
        *curr = *last;
        
        VectorPopBack(heap->vec);
        HeapifyUp(heap,j);
        HeapifyDown(heap, j);

        return ret_val;
    }

    return NULL;

}

static void HeapifyDown(heap_ty *heap, size_t index)
{
    size_t size = 0, downl = 0, downr = 0;
    void **down_l = NULL, **down_r = NULL, **curr = NULL, *temp = NULL;
    int comp_res = 0;

    assert(heap);

    size = HeapSize(heap);

    downl = 2 * index + 1;
    downr = 2 * index + 2;

    while(downr <= size)
    {
        downr = MIN(downr, size - 1);
        curr = VectorGetAccessToElement(heap->vec, index);
        down_l = VectorGetAccessToElement(heap->vec, downl);
        down_r = VectorGetAccessToElement(heap->vec, downr);
        comp_res = heap->comp(*down_l, *down_r);
        if (comp_res >= 0 && heap->comp(*curr, *down_l) < 0)
        {
            temp = *curr;
            *curr = *down_l;
            *down_l = temp;
            index = downl;
        }
        else if (comp_res < 0 && heap->comp(*curr, *down_r) < 0)
        {
            temp = *curr;
            *curr = *down_r;
            *down_r = temp;
            index = downr;
        }
        else
        {
            break;
        }
        downl = 2 * index + 1;
        downr = 2 * index + 2;
    } 

}


static void HeapifyUp(heap_ty *heap, size_t index)
{
    size_t up = 0;
    void **upv = NULL, **curr = NULL, *temp = NULL;
    int comp_res = 0;

    assert(heap);

    if(index == 0)
    {
        return;
    }
    up = (index - 1) / 2;

    while(up < index)
    {
        curr = VectorGetAccessToElement(heap->vec, index);
        upv = VectorGetAccessToElement(heap->vec, up);
        comp_res = heap->comp(*curr, *upv);
        if (comp_res > 0)
        {
            temp = *curr;
            *curr = *upv;
            *upv = temp;
            index = up;
        }
        else
        {
            break;
        }
        up = (index - 1) / 2;
    } 
}




