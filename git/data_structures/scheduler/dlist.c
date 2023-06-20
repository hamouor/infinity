#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */
#include "dlist.h"

#define FALSE 0
#define TRUE 1

#define SUCCESS 0
#define FAILURE 1

#define ITER2NODE(iter) (dlist_node_ty *)(iter)
#define NODE2ITER(node) (dlist_iter_ty)(node)

#define NULL_ITER NULL

typedef struct dlist_node dlist_node_ty;

struct dlist_node
{
	void *data;
	dlist_node_ty *next;
	dlist_node_ty *prev;
};

struct dlist                          
{
	dlist_node_ty head;
	dlist_node_ty tail;
};

static dlist_iter_ty GetListTail(dlist_iter_ty iter);

dlist_ty *DlistCreate(void)
{
	dlist_ty *list = NULL;
	
	list = (dlist_ty *)malloc(sizeof(dlist_ty));
	
	if (NULL == list)
	{
		return NULL;
	}
	
	list->head.data = &list;
	list->head.next = &list->tail;
	list->head.prev = NULL;
	
	list->tail.data = &list;
	list->tail.next = NULL;
	list->tail.prev = &list->head;
	
	return list;
}

void DlistDestroy(dlist_ty *list)
{
	dlist_iter_ty begin = NULL_ITER;
	dlist_iter_ty end = NULL_ITER;
	
	assert(list);
	
	begin = DlistBegin(list);
	end = DlistEnd(list);
	
	while(FALSE == DlistIterIsEqual(begin, end))
	{
		begin = DlistRemove(begin);
	}
	
	free(list); 
	list = NULL;
}

dlist_iter_ty DlistInsertBefore(dlist_iter_ty iter, const void *data)
{
	dlist_node_ty *iter_node = NULL;
	dlist_node_ty *new_node = NULL;
	
	assert(ITER2NODE(iter));
	
	new_node = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
	
	if (NULL == new_node)
	{
		return GetListTail(iter);
	}
	
	iter_node = ITER2NODE(iter);
	iter_node->prev->next = new_node;
	new_node->next = iter_node;
	new_node->prev = iter_node->prev;
	iter_node->prev = new_node;
	new_node->data = (void *)data;
	
	return NODE2ITER(new_node);
}

dlist_iter_ty DlistRemove(dlist_iter_ty iter)
{
	dlist_iter_ty result = NULL_ITER;
	dlist_node_ty *iter_node = NULL;
	
	iter_node = ITER2NODE(iter);
	
	assert(iter_node);
	
	iter_node->prev->next = iter_node->next;
	iter_node->next->prev = iter_node->prev;
	
	result = NODE2ITER(iter_node->next);
	
	free(iter_node);
	iter_node = NULL;
	
	return result;
}

dlist_iter_ty DlistPushBack(dlist_ty *list, const void *data)
{
	dlist_iter_ty result = NULL_ITER;
	
	assert(list);
	
	result = DlistInsertBefore(DlistEnd(list), data);
	
	return result;
}

dlist_iter_ty DlistPushFront(dlist_ty *list, const void *data)
{
	dlist_iter_ty result = NULL_ITER;
	
	assert(list);
	
	result = DlistInsertBefore(DlistBegin(list), data);
	
	return result;
}

void *DlistPopBack(dlist_ty *list)
{
	void *result = NULL;
	dlist_iter_ty end = NULL_ITER;
	
	assert(list);
	
	end = DlistPrev(DlistEnd(list));
	result = DlistGetData(end); 
	
	DlistRemove(end);
	
	return result;
}

void *DlistPopFront(dlist_ty *list)
{
	void *result = NULL;
	dlist_iter_ty head = NULL_ITER;
	
	assert(list);
	
	head = DlistBegin(list);
	result = DlistGetData(head); 
	
	DlistRemove(head);
	
	return result;
}

size_t DlistCount(const dlist_ty *list)
{
	size_t result = 0;
	dlist_iter_ty iter = NULL;
	dlist_iter_ty end_iter = NULL;
	
	assert(list);
	
	iter = DlistBegin(list);
	end_iter = DlistEnd(list);
	
	while(FALSE == DlistIterIsEqual(iter, end_iter))
	{
		iter = DlistNext(iter);
		++result;
	}
	
	return result;
}

int DlistIsEmpty(const dlist_ty *list)
{
	assert(list);
	
	return DlistIterIsEqual(DlistBegin(list), DlistEnd(list));
}

dlist_iter_ty DlistBegin(const dlist_ty *list)
{
	assert(list);
	
	return NODE2ITER(list->head.next);
}

dlist_iter_ty DlistEnd(const dlist_ty *list)
{
	assert(list);
	
	return NODE2ITER(&(list->tail));
}

dlist_iter_ty DlistNext(dlist_iter_ty iter)
{
	assert(ITER2NODE(iter));
	
	return NODE2ITER(ITER2NODE(iter)->next);
}

dlist_iter_ty DlistPrev(dlist_iter_ty iter)
{
	assert(ITER2NODE(iter));
	
	return NODE2ITER(ITER2NODE(iter)->prev);
}

int DlistIterIsEqual(dlist_iter_ty iter1, dlist_iter_ty iter2)
{
	assert(ITER2NODE(iter1));
	assert(ITER2NODE(iter2));
	
	return (ITER2NODE(iter1) == ITER2NODE(iter2));
}

void *DlistGetData(dlist_iter_ty iter)
{
	assert(ITER2NODE(iter));
	
	return ITER2NODE(iter)->data;
}

dlist_iter_ty DlistFind(dlist_iter_ty from, dlist_iter_ty to, IsMatch_ty IsMatch, void *user_data)
{
	assert(ITER2NODE(from));
	assert(ITER2NODE(to));
	assert(IsMatch);
	
	while(FALSE == DlistIterIsEqual(from, to))
	{
		if (TRUE == IsMatch(DlistGetData(from), user_data))
		{
			break;
		}
		
		from = DlistNext(from);
	}
	
	return from;
}

int DlistMultiFind(dlist_iter_ty from, dlist_iter_ty to, IsMatch_ty IsMatch, void *user_data, dlist_ty *dest_list)
{
	dlist_iter_ty push_result = NULL_ITER;
	void *data = NULL;
	
	assert(ITER2NODE(from));
	assert(ITER2NODE(to));
	assert(IsMatch);
	assert(dest_list);
	
	/* running from -> to */
	while(FALSE == DlistIterIsEqual(from, to))
	{
		data = DlistGetData(from);
		/* once data found - push in dest list */
		if (TRUE == IsMatch(data, user_data))
		{
			push_result = DlistPushBack(dest_list, data);
			/* if reached end of dest */
			if (DlistIterIsEqual(DlistEnd(dest_list), push_result))
			{
				return FAILURE;
			}
		}
		
		from = DlistNext(from);
	}
	
	return SUCCESS;
}

int DlistForEach(dlist_iter_ty from, dlist_iter_ty to, UserFunction_ty UserFunction, void *parameter)
{
	assert(ITER2NODE(from));
	assert(ITER2NODE(to));
	assert(UserFunction);
	
	while(FALSE == DlistIterIsEqual(from, to))
	{
		if (FAILURE == UserFunction(DlistGetData(from), parameter))
		{
			return FAILURE;
		}
		
		from = DlistNext(from);
	}
	
	return SUCCESS;
}

dlist_iter_ty DlistSplice(dlist_iter_ty from_src, dlist_iter_ty to_src, dlist_iter_ty dest_iter)
{
	dlist_node_ty *from_node = ITER2NODE(from_src);
	dlist_node_ty *to_node = ITER2NODE(to_src);
	dlist_node_ty *dest_node = ITER2NODE(dest_iter);
	dlist_node_ty *temp = NULL;
	
	assert(from_node);
	assert(to_node);
	assert(dest_node);
	
	/* Don't even try to figure this one out, I have a pretty sketch in my notebook on why it's like this. */
	from_node->prev->next = to_node;
	to_node->prev->next = dest_node;
	dest_node->prev->next = from_node;
	temp = from_node->prev;
	from_node->prev = dest_node->prev;
	dest_node->prev = to_node->prev;
	to_node->prev = temp;
	
	return NODE2ITER(from_node);
}

static dlist_iter_ty GetListTail(dlist_iter_ty iter)
{
	assert(ITER2NODE(iter));
	
	while(NULL != ITER2NODE(iter)->next)
	{
		iter = DlistNext(iter);
	}
	
	return iter;
}

#ifndef NDEBUG
void DlistAssertIter(dlist_iter_ty iter)
{
	assert(ITER2NODE(iter));
}
#endif
