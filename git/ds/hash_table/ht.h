#ifndef __HASH_H__
#define __HASH_H__

/******************************************************************************/
/*  		                      HASH hash table             		          */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  A hash table data structure which support data encoding by user	                * TODO *
				given function. This data structure supports inserstion of the
				encoded data and removal.
* AUTHOR: Shlomo Artzi
* REVIEWER: Aviv Gefen
* DATE: 06/06/2022
* VERSION: 0.1
*******************************************************************************/

#include <stddef.h> /* size_t */


typedef struct hash_table ht_ty;


typedef int(*HashFunc_ty)(const void* data); 

/* Performs user func on the data using param, returns 0 for success else 1   */
typedef int(*is_match_ty)(void *data1, void *data2);

/* Performs user func on the data using param, returns 0 for success else 1   */
typedef int(*UserFunctionn_ty)(void *data, void *param);


/*******************************************************************************
* Function:     Creates a new hash table.
* Arguments:    A compare function to sort the hash table.
* Return value: A pointer to the new hash table; NULL on failure.
* Notes:		Complexity - O(1).
*******************************************************************************/
ht_ty *HTCreate(HashFunc_ty hash_func, is_match_ty comp_func, const size_t hash_len);

/*******************************************************************************
* Function:     Destroy an existing hash table.
* Arguments:    A pointer to the existing hash table.
* Return value: None.
* Notes:        Complexity - O(n). (n - the amount of values in the hash table)
*******************************************************************************/
void HTDestroy(ht_ty *ht);

/*******************************************************************************
* Function:     Determines the size of the hash table.
* Arguments:    A pointer to existing hash table.
* Return value: The number of the elements in the hash table.
* Notes: 		Complexity - O(1).
*******************************************************************************/
size_t HTSize(const ht_ty *ht);

/*******************************************************************************
* Function:     Determines if the hash table is empty.
* Arguments:    A pointer to existing hash table.
* Return value: 1 if the hash table is empty; zero if not. 
* Notes: 		Complexity - O(1).
*******************************************************************************/
int HTIsEmpty(const ht_ty *ht);

/*******************************************************************************
* Function:     Inserts a new element into the hash table.
* Arguments:    hash table - A pointer to the hash table.
				data - A void pointer to the data to add.
* Return value: 0 on success, 1 on failure.
* Notes:        Complexity - O(1).
*******************************************************************************/
int HTInsert(ht_ty *ht, const void *data);

/*******************************************************************************
* Function:     Removes an existing element from the hash table.
* Arguments:    ht - a pointer to the hash table.
				comp_func - comp function.
				data - data to remove.
* Return value: The data of the removed element; NULL on failure (element wasn't found) 
* Notes:        Complexity - average case O(1), worst case O(n).
*******************************************************************************/
void *HTRemove(ht_ty *ht, const void *data);

/*******************************************************************************
* Function:     Checks if the given data is already in the hash table.
* Arguments:    ht - a pointer to the hash table.
				comp_func - comp function.
				data - data to search.
* Return value: void pointer to data found and is stored in hash table. NULL if unfound. 
* Notes: 		Complexity - average case O(1), worst case O(n).
*******************************************************************************/
void *HTFind(const ht_ty *ht, const void *data);

/*******************************************************************************
* Function:     Performs the given function with the given data on every element in
                the specific order which was requested.
* Arguments:    A pointer to the hash table.
				UserFunction - function of type UserFunction_ty.
*               parameter - void ptr to UserFunction parameters.
* Return value: 0 For Success, 1 for Failure.
* Notes:        Complexity - O(n).
*******************************************************************************/
int HTForEach(ht_ty *ht, UserFunctionn_ty function, void *param);


/* ADVANCED */                                                                                  /* TODO */
double HTLoadFactor(const ht_ty *ht);

double HTStdDev(const ht_ty *ht); /* wtf */
/* END OF ADVANCED */



#endif      /* __HASH_H__ */





