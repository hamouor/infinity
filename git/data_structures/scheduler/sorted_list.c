#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */

#include "sorted_list.h"

#ifndef NDEBUG
#define ASSERT_ITER(iter) (DlistAssertIter(IterToDlistIter(iter)))
#else
#define ASSERT_ITER(iter) NULL
#endif

#define NULL_ITER { NULL }

#define FALSE 0

struct sortlist
{
    dlist_ty        *list;
    DataCompare_ty  cmp_func;
};

typedef struct func_and_value
{
	void *value;
	DataCompare_ty func;
} fv_ty;

static sortlist_iter_ty DlistIterToIter(dlist_iter_ty dlist_iter);
static dlist_iter_ty IterToDlistIter(sortlist_iter_ty iter);
static sortlist_iter_ty FindFirstNotSmallerThan(sortlist_ty *list, sortlist_iter_ty from, sortlist_iter_ty to, void *data);
static int CompFuncNotSmallerThan(void *data, void *fv);

sortlist_ty *SortListCreate(DataCompare_ty data_comp)
{
	sortlist_ty *list = NULL;
	
	assert(data_comp);
	
	list = (sortlist_ty *)malloc(sizeof(sortlist_ty));
	
	if (NULL == list)
	{
		return NULL;
	}
	
	list->list = DlistCreate();
	
	if (NULL == list->list)
	{
		free(list);
		list = NULL;
		return NULL;
	}
	
	list->cmp_func = data_comp;
	
	return list;
}

void SortListDestroy(sortlist_ty* list)
{
	assert(list);
	
	DlistDestroy(list->list);
	list->list = NULL;
	list->cmp_func = NULL;
	
	free(list);
	list = NULL;
}

sortlist_iter_ty SortListBegin(const sortlist_ty *list)
{
	sortlist_iter_ty result = NULL_ITER;
	
	assert(list);
	
	result = DlistIterToIter(DlistBegin(list->list));
	
	return result;
}

sortlist_iter_ty SortListEnd(const sortlist_ty *list)
{
	sortlist_iter_ty result = NULL_ITER;
	
	assert(list);
	
	result = DlistIterToIter(DlistEnd(list->list));
	
	return result;
}

sortlist_iter_ty SortListNext(sortlist_iter_ty iter)
{
	sortlist_iter_ty result = NULL_ITER;

	ASSERT_ITER(iter);
		
	result = DlistIterToIter(DlistNext(IterToDlistIter(iter)));
	
	return result;
}

sortlist_iter_ty SortListPrev(sortlist_iter_ty iter)
{
	sortlist_iter_ty result = NULL_ITER;

	ASSERT_ITER(iter);
	
	result = DlistIterToIter(DlistPrev(IterToDlistIter(iter)));
	
	return result;
}

void *SortListGetData(sortlist_iter_ty iter)
{
	ASSERT_ITER(iter);

	return DlistGetData(IterToDlistIter(iter));
}

int SortListIterIsEqual(sortlist_iter_ty iter1, sortlist_iter_ty iter2)
{
	ASSERT_ITER(iter1);
	ASSERT_ITER(iter2);

	return DlistIterIsEqual(IterToDlistIter(iter1), IterToDlistIter(iter2));
}

size_t SortListSize(const sortlist_ty *list)
{
	assert(list);
	
	return DlistCount(list->list);
}

int SortListIsEmpty(const sortlist_ty *list)
{
	assert(list);
	
	return DlistIsEmpty(list->list);
}

sortlist_iter_ty SortListInsert(sortlist_ty *list, void *data)
{
	sortlist_iter_ty insert_pos = NULL_ITER;
	
	assert(list);
	
	insert_pos = FindFirstNotSmallerThan(list, SortListBegin(list), SortListEnd(list), data);
	
	return DlistIterToIter(DlistInsertBefore(IterToDlistIter(insert_pos), data));
}

sortlist_iter_ty SortListRemove(sortlist_iter_ty iter)
{
	dlist_iter_ty result;

	ASSERT_ITER(iter);
	
	result = DlistRemove(IterToDlistIter(iter));
	
	return DlistIterToIter(result);
}

void *SortListPopBack(sortlist_ty *list)
{
	assert(list);
	
	return DlistPopBack(list->list);
}

void *SortListPopFront(sortlist_ty *list)
{
	assert(list);
	
	return DlistPopFront(list->list);
}

int SortListForEach(sortlist_iter_ty from, sortlist_iter_ty to, Sort_UserFunction_ty user_function, void *parameters)
{
	ASSERT_ITER(from);
	ASSERT_ITER(to);
	assert(user_function);
	
	return DlistForEach(IterToDlistIter(from), IterToDlistIter(to), (UserFunction_ty)user_function, parameters);
}

sortlist_iter_ty SortListFind(sortlist_ty *sortlist, sortlist_iter_ty from, sortlist_iter_ty to, void *data_to_find)
{
	sortlist_iter_ty result = NULL_ITER;
	
	assert(sortlist);
	ASSERT_ITER(from);
	ASSERT_ITER(to);
	
	result = FindFirstNotSmallerThan(sortlist, from, to, data_to_find);
	
	if (0 == sortlist->cmp_func(data_to_find, SortListGetData(result)))
	{
		return result;
	}
	else
	{
		return to;
	}
}

sortlist_iter_ty SortListFindIf(sortlist_iter_ty from, sortlist_iter_ty to, Sort_IsMatch_ty is_match, void *user_data)
{
	sortlist_iter_ty result = NULL_ITER;
	
	ASSERT_ITER(from);
	ASSERT_ITER(to);
	assert(is_match);
	
	result = DlistIterToIter(DlistFind(IterToDlistIter(from), IterToDlistIter(to), (IsMatch_ty)is_match, user_data));
	
	return result;
}

sortlist_ty *SortListMerge(sortlist_ty *dest_list, sortlist_ty *src_list)
{
	sortlist_iter_ty src_head = NULL_ITER;
	sortlist_iter_ty dest_head = NULL_ITER;
	sortlist_iter_ty src_tail = NULL_ITER;
	sortlist_iter_ty dest_tail = NULL_ITER;
	sortlist_iter_ty from = NULL_ITER;
	void *src_data = NULL;
	void *dest_data = NULL;
	
	assert(dest_list);
	assert(src_list);
	
	src_head = SortListBegin(src_list);
	dest_head = SortListBegin(dest_list);
	src_tail = SortListEnd(src_list);
	dest_tail = SortListEnd(dest_list);
	
	/* Splicing should happen until source list has been moved in its entirety */
	while (!SortListIsEmpty(src_list))
	{
		src_data = SortListGetData(src_head);
		dest_data = SortListGetData(dest_head);
		
		/* If data in source is less than data in destination */
		if (0 > dest_list->cmp_func(src_data, dest_data))
		{
			/* Find next in source that is not less than destination,
			* then splice piece from point of origin to point reached */
			from = src_head;
			
			src_head = FindFirstNotSmallerThan(src_list, src_head, src_tail, dest_data);
			
			DlistSplice(IterToDlistIter(from), IterToDlistIter(src_head), IterToDlistIter(dest_head));
		}
		else
		{
			/* Find next in destination that is not less than source */
			dest_head = FindFirstNotSmallerThan(dest_list, dest_head, dest_tail, src_data);
			
			/* If reached end of destination list, splice whatever is left of source */
			if (FALSE != SortListIterIsEqual(dest_head, dest_tail))
			{
				DlistSplice(IterToDlistIter(src_head), IterToDlistIter(src_tail), IterToDlistIter(dest_tail));
			}
		}
	}
	
	return dest_list;
}

static sortlist_iter_ty DlistIterToIter(dlist_iter_ty dlist_iter)
{
	sortlist_iter_ty result = NULL_ITER;
	
	DlistAssertIter(dlist_iter);
	
	result.d_iter = dlist_iter;
	
	return result;
}

static dlist_iter_ty IterToDlistIter(sortlist_iter_ty iter)
{
	return iter.d_iter;
}

static sortlist_iter_ty FindFirstNotSmallerThan(sortlist_ty *list, sortlist_iter_ty from, sortlist_iter_ty to, void *data)
{
	dlist_iter_ty result;
	fv_ty func_and_value;
	
	func_and_value.func = list->cmp_func;
	func_and_value.value = data;
	
	result = DlistFind(IterToDlistIter(from), IterToDlistIter(to), CompFuncNotSmallerThan, &func_and_value);
	
	return DlistIterToIter(result);
}

static int CompFuncNotSmallerThan(void *data, void *fv)
{
	fv_ty *fv_ = fv;
	return (fv_->func(data, fv_->value) >= 0);
}
