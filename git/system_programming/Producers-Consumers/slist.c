#include <stdlib.h> /* malloc() etc. */
#include <assert.h> /* assert() */

#include "slist.h"

#define SUCCESS 0
#define FAILURE 1

#define TRUE 1
#define FALSE 0

#define UNUSED(x) (void)(x)

#define NODE_TO_ITER(node) (slist_iter_ty)(node)
#define ITER_TO_NODE(iter) (slist_node_ty*)(iter)
#define IS_END_ITER(iter) (NULL == (ITER_TO_NODE(iter))->next)
#define NULL_ITER NULL
#define ITER_DATA(iter) (ITER_TO_NODE(iter)->data)
#define ITER_NEXT(iter) (ITER_TO_NODE(iter)->next)

struct slist
{
	slist_node_ty 	*head;
	slist_node_ty 	*tail;
};

struct slist_node
{
	void 			*data;
	slist_node_ty 	*next;
};

static slist_iter_ty GetListEnd(slist_iter_ty iter);

slist_ty *SlistCreate(void)
{
	slist_ty *list = NULL;
	slist_node_ty *tail = NULL;
	
	/* allocate space for list struct */
	list = (slist_ty *)malloc(sizeof(slist_ty));
	
	if (NULL == list)
	{
		return NULL;
	}
	
	/* allocate space for tail dummy node */
	tail = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	if (NULL == tail)
	{
		free(list), list = NULL;
		return NULL;
	}
	
	/* tail points to NULL, contains pointer to list */
	tail->data = (void *)list;
	tail->next = NULL;
	
	/* in an empty list, the head and tail are the same */
	list->head = list->tail = tail;
	
	return list;
}

void SlistDestroy(slist_ty *list)
{
	slist_iter_ty next = NULL_ITER;
	
	assert(list);
	
	next = NODE_TO_ITER(list->head);
	
	while (FALSE == SlistIterIsEqual(next, NODE_TO_ITER(list->tail)))
	{
		next = SlistRemove(next);
	}
	
	free(list->tail); /* free dummy node */
	free(list); /* free list struct */
}

slist_iter_ty SlistInsertBefore(slist_iter_ty iter, const void *data)
{
	slist_node_ty *new_node = NULL;
	slist_node_ty *iter_node = ITER_TO_NODE(iter);
	assert(iter);
	
	/* create new node */
	new_node = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	if (NULL == new_node)
	{
		return GetListEnd(iter); 
	}
	
	/* put data and pointer from given iter to new node */
	new_node->data = ITER_DATA(iter);
	new_node->next = ITER_NEXT(iter);
	
	/* put new data in given iter, point it to new node */
	iter_node->data = (void *)data;
	iter_node->next = new_node;
	
	/* if given iter is the dummy node, update the tail in the list struct */
	if(IS_END_ITER(NODE_TO_ITER(new_node)))
	{
		((slist_ty *)new_node->data)->tail = new_node; 
	}
	
	/* return iter with given node */
	return iter;
}

slist_iter_ty SlistRemove(slist_iter_ty iter)
{
	slist_node_ty *to_free = NULL;
	slist_node_ty *iter_node = ITER_TO_NODE(iter);
	
	assert(iter);
	
	to_free = ITER_NEXT(iter);
	
	if (IS_END_ITER(to_free))
	{
		iter_node->data = to_free->data;
		iter_node->next = NULL;
		((slist_ty *)ITER_DATA(iter))->tail = iter; 
	}
	else
	{
		/* set data and pointer in given node to data and pointer from next node */
		iter_node->data = ITER_NEXT(iter)->data;
		iter_node->next = ITER_NEXT(iter)->next;
	}
	
	/* free next node */
	free(to_free);
	to_free = NULL;
	
	/* return given node */
	return iter;
}

size_t SlistCount(const slist_ty *list)
{
	size_t count = 0;
	slist_iter_ty iter = NULL_ITER;
	
	assert(list);
	
	iter = NODE_TO_ITER(list->head);
	
	while(FALSE == SlistIterIsEqual(iter, NODE_TO_ITER(list->tail)))
	{
		iter = SlistNext(iter);
		++count;
	}
	
	return count;
}

slist_iter_ty SlistFind(slist_iter_ty from, slist_iter_ty to, IsMatch_ty IsMatch, void *user_data)
{
	assert(from);
	assert(to);
	assert(IsMatch);
	
	/* go over nodes and return iterator once is_match returns true */
	while (FALSE == SlistIterIsEqual(from, to))
	{
		if(TRUE == IsMatch(from->data, user_data))
		{
			break;
		}
		
		from = SlistNext(from);
	}
	
	return from;
}

int SlistForEach(slist_iter_ty from, slist_iter_ty to, UserFunction_ty UserFunction, void *parameter)
{
	assert(from);
	assert(to);
	assert(UserFunction);
	
	/* go over nodes and call user_function on each node */
	while (FALSE == SlistIterIsEqual(from, to))
	{
		if(FAILURE == UserFunction(from, parameter))
		{
			/* if user_function fails anywhere, return fail at the end */
			return FAILURE;
		}
		
		from = SlistNext(from);
	}
	
	return SUCCESS;
}

slist_iter_ty SlistBegin(const slist_ty *list)
{
	assert(list);
	
	return NODE_TO_ITER(list->head);
}

slist_iter_ty SlistEnd(const slist_ty *list)
{
	assert(list);
	
	return NODE_TO_ITER(list->tail);
}

slist_iter_ty SlistNext(slist_iter_ty iter)
{
	assert(iter);
	
	return NODE_TO_ITER(ITER_NEXT(iter));
}

void *SlistGetData(slist_iter_ty iter)
{
	assert(iter);
	
	return ITER_DATA(iter);
}

void SlistSetData(slist_iter_ty iter, void *new_data)
{
	slist_node_ty *iter_node = ITER_TO_NODE(iter);
	
	assert(iter);
	
	iter_node->data = new_data;
}

int SlistIterIsEqual(slist_iter_ty iter1, slist_iter_ty iter2)
{
	assert(iter1);
	assert(iter2);
	
	return iter1 == iter2;
}

static slist_iter_ty GetListEnd(slist_iter_ty iter)
{
	assert(iter);
	
	while(FALSE == IS_END_ITER(iter))
	{
		iter = SlistNext(iter);
	}
	
	return iter;
}
