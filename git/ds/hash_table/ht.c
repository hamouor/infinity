#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc free*/

#include "dlist.h"
#include "ht.h"

struct hash_table
{
	HashFunc_ty hash_func;
	is_match_ty comp_func;
	size_t size;
	size_t hash_len;
	dlist_ty *arr[1];
};

ht_ty *HTCreate(HashFunc_ty hash_func, is_match_ty comp_func, const size_t hash_len)
{
    ht_ty* new_ht = NULL;
    int i = 0;

    assert(hash_func);

    new_ht = (ht_ty*)malloc(sizeof(ht_ty) + (hash_len - 1) * sizeof(dlist_ty*));
    if(!new_ht)
    {
        return NULL;
    }

    for(; i < hash_len; ++i)
    {
        new_ht->arr[i] = DlistCreate();
        if(!(new_ht->arr[i]))
        {
            for(; i >= 0; --i)
            {
                DlistDestroy(new_ht->arr[i]);
            }
            free(new_ht);
            return NULL;
        }
    }

    new_ht->hash_func = hash_func;
    new_ht->comp_func = comp_func;
    new_ht->size = 0;
    new_ht->hash_len = hash_len;

    return new_ht;
}

void HTDestroy(ht_ty *ht)
{
    int i = 0;
    assert(ht);

    for(; i < ht->hash_len; ++i)
    {
        DlistDestroy(*(ht->arr + i));
    }
    free(ht);
}

size_t HTSize(const ht_ty *ht)
{
    assert(ht);

    return ht->size;
}

int HTIsEmpty(const ht_ty *ht)
{
    assert(ht);

    return(!ht->size);
}

int HTInsert(ht_ty *ht, const void *data)
{
    int index = 0;

    assert(ht && data);

    index = ht->hash_func(data);
    DlistPushFront(ht->arr[index], data);

    ++ht->size;
    return 0;
}
#include<stdio.h>
void *HTFind(const ht_ty *ht, const void *data)
{
    int index = 0;
    dlist_iter_ty iter;

    assert(ht && data);

    index = ht->hash_func(data);
    iter = DlistFind(DlistBegin(ht->arr[index]), DlistEnd(ht->arr[index]),ht->comp_func, (void*)data);

    if (DlistIterIsEqual(iter , DlistEnd(ht->arr[index])))
    {
        return NULL;
        printf("returned null\n");
    }
    
    return DlistGetData(iter);
}

void *HTRemove(ht_ty *ht, const void *data)
{
    int index = 0;
    dlist_iter_ty iter;
    void *ret_dat = NULL;

    assert(ht && data);

    index = ht->hash_func(data);

    --ht->size;
    iter = DlistFind(DlistBegin(ht->arr[index]), DlistEnd(ht->arr[index]),ht->comp_func, (void*)data);
    
    if (DlistIterIsEqual(iter , DlistEnd(ht->arr[index])))
    {
        return NULL;
    }
    
    ret_dat = DlistGetData(iter);
    DlistRemove(iter);
    return ret_dat;
}

int HTForEach(ht_ty *ht, UserFunctionn_ty function, void *param)
{
    int res = 0, i = 0;

    assert(ht && function);

    for(; i < ht->hash_len; ++i)
    {
        if(res = DlistForEach(DlistBegin(ht->arr[i]), DlistEnd(ht->arr[i]), function, param))
        {
            break;
        }
    }

    return res;
}