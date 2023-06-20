#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "heap.h"
#include "vector.h"

#define INITIAL_SIZE 4

#define L_CHILD(n) (2 * n + 1)
#define R_CHILD(n) (2 * n + 2)
#define PARENT(n) ((n - 1)/ 2)

#define GET_ELEMENT *(void **)VectorGetAccessToElement

struct heap
{
    compfunc_ty compare;
    vector_ty *elements;
};

static void HeapifyUp(heap_ty *heap, size_t index); 
static void HeapifyDown(heap_ty *heap, size_t index);
static int CompareTwoIndices(heap_ty *heap, size_t index1, size_t index2);
static void SwapTwoIndices(heap_ty *heap, size_t index1, size_t index2);

heap_ty *HeapCreate(compfunc_ty CompFunc)
{
    heap_ty *heap = NULL;

    assert(CompFunc);

    heap = (heap_ty *)malloc(sizeof(heap_ty));

    if (!heap)
    {
        return NULL;
    }

    heap->elements = VectorCreate(sizeof(void *), INITIAL_SIZE);

    if (!heap->elements)
    {
        free(heap);
        return NULL;
    }

    heap->compare = CompFunc;

    return heap;
}

void HeapDestroy(heap_ty *heap)
{
    assert(heap);

    VectorDestroy(heap->elements);

    heap->compare = NULL;
    heap->elements = NULL;

    free(heap);
}


size_t HeapSize(const heap_ty *heap)
{
    assert(heap);

    return VectorSize(heap->elements);
}


int HeapIsEmpty(const heap_ty *heap)
{
    assert(heap);

    return !HeapSize(heap);
}


void *HeapPeek(const heap_ty *heap)
{
    assert(heap);
    
    return GET_ELEMENT(heap->elements, 0);
}


int HeapPush(heap_ty *heap, void *data)
{
    int push_res = -1;
    
    assert(heap);

    push_res = VectorPushBack(heap->elements, &data);

    /* heapify up if successful */
    if (!push_res)
    {
        HeapifyUp(heap, VectorSize(heap->elements) - 1);
    }

    return push_res;
}


void *HeapPop(heap_ty *heap)
{
    void *data = NULL;

    assert(heap);

    if (HeapIsEmpty(heap))
    {
        return NULL;
    }

    /* save data from first element */
    data = GET_ELEMENT(heap->elements, 0);
    
    /* swap with end */
    SwapTwoIndices(heap, 0, VectorSize(heap->elements) - 1);

    /* pop back from vector */
    VectorPopBack(heap->elements);
    
    /* heapify down from the new root */
    HeapifyDown(heap, 0);

    return data;
}


void *HeapRemove(heap_ty *heap, ismatch_ty ismatch, void *param)
{
    size_t i = 0;
    size_t size = 0;
    void *data = NULL;

    assert(heap);
    assert(ismatch);

    size = HeapSize(heap);

    /* sequentially find fitting data */
    for (i = 0; i < size; ++i)
    {
        data = GET_ELEMENT(heap->elements, i);

        if (ismatch(data, param))
        {
            /* once found, swap with last element and pop back */
            SwapTwoIndices(heap, i, size - 1);

            VectorPopBack(heap->elements);

            /* if there is a child and compare function returns positive, heapify down */
            if ((L_CHILD(i) <= size - 1 && CompareTwoIndices(heap, L_CHILD(i), i) > 0) || 
                (R_CHILD(i) <= size - 1 && CompareTwoIndices(heap, R_CHILD(i), i) > 0))
            {
                HeapifyDown(heap, i);
            }
            else /* otherwise heapify up */
            {
                HeapifyUp(heap, i);
            }

            return data;
        }
    }

    /* if nothing found, return NULL */
    return NULL;
}

static void HeapifyUp(heap_ty *heap, size_t index)
{
    assert(heap);

    /* if called with root or compare function yields positive with parent, return */
    if (!index || 0 < CompareTwoIndices(heap, PARENT(index), index))
    {
        return;
    }
    
    /* if data in parent is smaller, swap */
    SwapTwoIndices(heap, PARENT(index), index);

    /* call again with parent index */
    HeapifyUp(heap, PARENT(index));
}

static void HeapifyDown(heap_ty *heap, size_t index)
{
    size_t l_child = 0;
    size_t r_child = 0;
    size_t target = 0;

    assert(heap);

    /* get children indices */
    l_child = L_CHILD(index);
    r_child = R_CHILD(index);

    /* if left child is beyond size, return */
    if (l_child >= VectorSize(heap->elements))
    {
        return;
    }

    /* if right child is beyond size, target is left child */
    /* else target is the bigger of the two */
    target = r_child >= VectorSize(heap->elements) ? l_child : 
            ((CompareTwoIndices(heap, l_child, r_child)) > 0 ? l_child : r_child);

    /* if data is smaller than target */ 
    if (CompareTwoIndices(heap, target, index) > 0)
    {
        /* swap it with target */
        SwapTwoIndices(heap, index, target);

        /* call recursively with target index */
        HeapifyDown(heap, target);
    }
}

static int CompareTwoIndices(heap_ty *heap, size_t index1, size_t index2)
{
    void *item1 = NULL;
    void *item2 = NULL;

    assert(heap);

    item1 = GET_ELEMENT(heap->elements, index1);
    item2 = GET_ELEMENT(heap->elements, index2);

    return (heap->compare(item1, item2));
}

static void SwapTwoIndices(heap_ty *heap, size_t index1, size_t index2)
{
    void *item1 = NULL;
    void *item2 = NULL;
    
    assert(heap);

    item1 = GET_ELEMENT(heap->elements, index1);
    item2 = GET_ELEMENT(heap->elements, index2);

    VectorSetElement(heap->elements, index2, &item1);
    VectorSetElement(heap->elements, index1, &item2);
}