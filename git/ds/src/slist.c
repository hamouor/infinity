#include"slist.h"

#include <stdlib.h> /*malloc*/
#include <assert.h> /*you guess*/

struct slist
{
	slist_node_ty 	*head;
	slist_node_ty 	*tail;
};

struct slist_node
{
	void *data;
	slist_node_ty *next;
};

#define ITERTONODE(iter) (slist_node_ty*)iter
#define NODETOITER(node) (slist_iter_ty)node

slist_iter_ty find_end(slist_iter_ty iter);

slist_ty *SlistCreate(void)
{
	slist_ty *new_slist = NULL;
	slist_node_ty *dummy = NULL;
	
	new_slist = (slist_ty*)malloc(sizeof(slist_ty));
	dummy = (slist_node_ty*)malloc(sizeof(slist_node_ty));
	if (new_slist == NULL || dummy == NULL)
	{
		free(new_slist); new_slist = NULL;
		free(dummy); dummy = NULL;
		return NULL;
	}
	new_slist -> head = dummy;
	new_slist -> tail = dummy;
	dummy -> data = (void*)new_slist;
	dummy -> next = NULL;
	
	return new_slist;
}

void SlistDestroy(slist_ty *list)
{
	slist_node_ty* current = NULL, *temp = NULL;
	
	assert(list);
	
	temp = SlistBegin(list);
	while(temp != NULL)
	{
		current = temp;
		temp = SlistNext(current);
		free(ITERTONODE(current));
	}
	current = NULL;
	free(list); list = NULL;
}

slist_iter_ty SlistInsertBefore(slist_iter_ty iter, void *data)
{
	slist_node_ty *new_node = NULL;
	
	assert(iter);

	new_node = (slist_node_ty*)malloc(sizeof(slist_node_ty));
	if (new_node == NULL)
	{
		iter = find_end(iter);
		return iter;
	}
	if (SlistNext(iter) == NULL)
	{
		(*(slist_ty *)(iter -> data)).tail = new_node;
	}

	SlistSetData(new_node, SlistGetData(iter));
	new_node -> next = SlistNext(iter);
	SlistSetData(iter, data);
	iter -> next = new_node;
	
	return iter;
}

slist_iter_ty SlistRemove(slist_iter_ty iter)
{
	slist_node_ty *temp = NULL;
	
	assert(iter);
	
	temp = ITERTONODE(SlistNext(iter));
	if (temp == NULL)
	{
		return iter;
	}
	SlistSetData(iter, SlistGetData(SlistNext(iter)));;
	(ITERTONODE(iter))->next =SlistNext(SlistNext(iter));
	free(temp);
	
	return iter;
}

size_t SlistCount(const slist_ty *list)
{
	slist_node_ty *current = NULL;
	size_t len = 0;
	
	assert(list);
	
	current = ITERTONODE(SlistBegin(list));
	while(SlistNext(NODETOITER(current)) != NULL)
	{
		++len;
		current = ITERTONODE(SlistNext(NODETOITER(current)));
	}
	
	return len;
}

slist_iter_ty SlistFind(slist_iter_ty from, slist_iter_ty to, IsMatch_ty IsMatch, void *user_data)
{
	slist_node_ty *current = NULL;
	
	assert(from);
	assert(to);
	assert(IsMatch);
	
	current =  ITERTONODE(from);
	if (SlistNext(current) == NULL)
	{
		return NULL;
	}
	do 
	{
		if (IsMatch(SlistGetData(NODETOITER(current)), user_data))
		{
			return NODETOITER(current);
		}
		current = ITERTONODE(SlistNext(current));
			
	}while (SlistIterIsEqual(NODETOITER(current), to) && SlistNext(current) != NULL);
	
	return NODETOITER(current);
}

int SlistForEach(slist_iter_ty from, slist_iter_ty to, UserFunction_ty UserFunction, void *parameter)
{
	slist_node_ty *current = from;
	
	assert(from);
	assert(to);
	assert(UserFunction);
	
	if (SlistNext(current) == NULL)
	{
		return 0;
	}
	do 
	{
		if (!(UserFunction(current -> data, parameter)))
		{
			return 0;
		}
		current = current -> next;
	}while (current != to && current -> next != NULL);
	
	return 1;
}

slist_iter_ty SlistBegin(const slist_ty *list)
{
	assert(list);
	return list -> head;
}

slist_iter_ty SlistEnd(const slist_ty *list)
{
	assert(list);
	return list -> tail;
}

slist_iter_ty SlistNext(slist_iter_ty iter)
{
	assert(iter);
	
	if (iter -> next == NULL)
	{
		return iter;
	}

	return iter -> next;
}

void *SlistGetData(slist_iter_ty iter)
{
	assert(iter);
	
	return iter -> data;
}

void SlistSetData(slist_iter_ty iter, void *new_data)
{
	assert(iter);
	assert(new_data);
	
	if (iter -> next != NULL)
	{
		iter -> data = new_data;
	} 
}

int SlistIterIsEqual(slist_iter_ty iter1, slist_iter_ty iter2)
{
	return (iter1 == iter2);
}

slist_iter_ty find_end(slist_iter_ty iter)
{
	while(iter -> next != NULL)
	{
		iter = iter -> next;
	}
	return iter;
}

slist_ty *SlistAppend(slist_ty *list1, slist_ty *list2)
{
	slist_iter_ty iter_tail_1 = NULL;
	slist_iter_ty iter_head_2 = NULL;

	assert(list1);
	assert(list2);

	iter_tail_1 = SlistEnd(list1);
	iter_head_2 = SlistBegin(list2);

	/* move head 2 content to list 1 tail, update tail1 */ 
	(iter_tail_1 -> next) = (iter_head_2 -> next);
	(iter_tail_1 -> data) = (iter_head_2 -> data);
	(list1 -> tail) = SlistEnd(list2);

	/* create new tail 2 and update in list 2 (head)  */
	(iter_head_2 -> data) = list2;
	(iter_head_2 -> next) = NULL;
	(list2 -> tail) = iter_head_2;

	return list1;
}
