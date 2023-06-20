/*******************************************************************************
*	                            	SORTED LIST                                                    
*******************************************************************************/
/******************************************************************************
* DESCRIPTION: A sorted list data structure, which
* supports inserting or removing nodes, count nodes, find
* nodes (in specific range to improve efficiency), and 
* sequential access to every node in the list.
* AUTHOR: HDR24
* REVIEWER:
* DATE: 20/04/2022
* VERSION: 0.2.3

*******************************************************************************/
#ifndef __SORTLIST_H__
#define __SORTLIST_H__

#include <stddef.h> /* size_t */

#include "dlist.h"

typedef struct sortlist sortlist_ty;
typedef struct sortlist_iter sortlist_iter_ty;

/* returns 1 if data1 should be after data2, -1 if data2 is after data1, 0 if data1 = data2 */
typedef int(*DataCompare_ty)(const void *data1, const void *data2); 

/* returns 1 in case of match between data and user_data, else returns 0 */
typedef int(*Sort_IsMatch_ty)(void *data, void *user_data); 

/* performs an operation on data, returns 0 for success else 1
   parameter - user parameter                                            */
typedef int(*Sort_UserFunction_ty)(void *data, void *parameter); 



/*******************************************************************************
* Function:         Create a new sorted linked list.
* Arguments:        a sorting function.
* Return value:     A pointer to the new sorted list handler or 
*                   NULL on failure
* Notes: 	        A created list MUST be destroyed after use!
* Complexity:       O(1).
*******************************************************************************/
sortlist_ty *SortListCreate(DataCompare_ty data_comp);

/*******************************************************************************
* Function:         Frees the memory allocated for the list.
* Arguments:        A pointer to the sorted list.   
* Return value:     none
* Notes: 	        Undefiend behavior if list is NULL
* Complexity:       O(n).
*******************************************************************************/
void SortListDestroy(sortlist_ty* list);

/*******************************************************************************
* Function:         Returns an iter to the first valid node in the list.
* Arguments:        A pointer to the list.
* Return value:     An iter to the first node in the list. 
*                   if empty - list END dummy.
* Notes: 	        Undefiend behavior if list in NULL
* Complexity:   O(1).
*******************************************************************************/
sortlist_iter_ty SortListBegin(const sortlist_ty *list);

/*******************************************************************************
* Function:     Returns an iter to the list's tail dummy node.
* Arguments:    A pointer to the list.
* Return value: An iter to the last dummy node in the list.
* Notes:        Undefined behavior if sor_list given is NULL.
* Complexity:   O(1).
*******************************************************************************/
sortlist_iter_ty SortListEnd(const sortlist_ty *list);

/*******************************************************************************
* Function:     Returns an iter to the next node after given iter.
* Arguments:    iter.
* Return value: iter to the next node.
* Notes:        Undefined behavior if iter given is NULL.
*               Undefined behavior - if iter is sor_list END.
* Complexity:   O(1)
*******************************************************************************/
sortlist_iter_ty SortListNext(sortlist_iter_ty iter);

/*******************************************************************************
* Function:     Returns a pointer to the previous node before the given iter.
* Arguments:    iter.
* Return value: iter to the previous node.
* Notes:        Undefined behavior if iter given is NULL.
*               Undefined behavior - if iter is sort_list Begin
* Complexity:   O(1)
*******************************************************************************/
sortlist_iter_ty SortListPrev(sortlist_iter_ty iter);

/*******************************************************************************
* Function:     Returns a pointer to the data in the specified
*               location in the list.
* Arguments:    iter
* Return value: Void pointer to the data in the specified
* location.
* Notes:        Undefined behavior - if iter is sor_list END.
* Complexity:   O(1)
*******************************************************************************/
void *SortListGetData(sortlist_iter_ty iter);

/*******************************************************************************
* Function:     Checks if two iterators are equal (points to the
*               same place) 
* Arguments:    iter1, iter2
* Return value: 1 = equal; 0 = not equal
* Notes: 
* Complexity:   O(1)
*******************************************************************************/
int SortListIterIsEqual(sortlist_iter_ty iter1, sortlist_iter_ty iter2);

/*******************************************************************************
* Function:     counts the number of nodes in the list (excluding dummy nodes).
* Arguments:    pointer to sor_list.
* Return value: number of nodes.
* Complexity:   O(n)
*******************************************************************************/
size_t SortListSize(const sortlist_ty *list);

/*******************************************************************************
* Function:     check the given list to see if it is empty
* Arguments:    A pointer to the list.
* Return value: 1 is empty , 0 if not.
* Notes:        Undefined behavior if sor_list given is NULL.
* Complexity:   O(1)
*******************************************************************************/
int SortListIsEmpty(const sortlist_ty *list);

/* TODO: USE FIND(optional) */
/*******************************************************************************
* Function:         Add a new element to the right place in the sorted list. 
*                   according to data_comp function
* Arguments:        list, void ptr to data.   
* Return value:     A iterator to new node, if allocation failed - returns dummy iter END
* Notes: 	        Undefined behavior if sor_list given is NULL.
* Complexity:       O(n)     
*******************************************************************************/
sortlist_iter_ty SortListInsert(sortlist_ty *list, void *data);

/*******************************************************************************
* Function:     Delete the node in the given location (iter)
* Arguments:    iter
* Return value: iter to the next node
* Notes:        undefined behavior - if iter is sor_list HEAD OR TAIL
* Complexity:   O(1)
*******************************************************************************/
sortlist_iter_ty SortListRemove(sortlist_iter_ty iter);

/*******************************************************************************
* Function:     pop the node at the end of the sorted list.
* Arguments:    pointer to sor_list.
* Return value: the data of the popped node.
* Notes:        Undefined behavior if sor_list given is NULL.
* 		Undefined behavior if sor_list given is empty.
* Complexity:   O(1)
*******************************************************************************/
void *SortListPopBack(sortlist_ty *list);

/*******************************************************************************
* Function:     pop the node at the front of the sorted list
* Arguments:    pointer to sor_list.
* Return value: the data of the popped node.  
* Notes:        Undefined behavior if sor_list given is NULL.
* 		Undefined behavior if sor_list given is empty.
* Complexity:   O(1)
*******************************************************************************/
void *SortListPopFront(sortlist_ty *list);

/*******************************************************************************
* Function:     Iterate over the data in the sorted list through index
*               range [from-to)(to NOT INCLUDED), allowing the user to execute 
*               'user_function' on every data in the specified range. 
*               This function calls UserFunction until fail. if UserFunction
*               fails, it stops looping and returns failure value (1).
*               Otherwise, return success value (0).
* Arguments:    start iter (from), end iter (to), function of type
*               Sort_UserFunction_ty, pointer to parameter to be included in the 
*               given type Sort_UserFunction_ty.              
* Return value: 0 for success, 1 for failure.
* Notes: 	Undefined behavior if Sort_UserFunction_ty given messes up with the
*               sorting algorithem.
* Complexity:   O(n)
*******************************************************************************/
int SortListForEach(sortlist_iter_ty from, sortlist_iter_ty to, Sort_UserFunction_ty user_function, void *parameters);

/*******************************************************************************
* Function:     Searches a specified (SORTED) data in the list through.
* index range   [from, to), according to list's sorting function.
* Arguments:    start iter (from), end iter (to)(to NOT INCLUDED), data.
* Return value: iter if data is found; 
*               If user_data is not found - return iter (to).
* Notes: 
* Complexity:   O(n)
*******************************************************************************/
sortlist_iter_ty SortListFind(sortlist_ty *sortlist, sortlist_iter_ty from, sortlist_iter_ty to, void *data_to_find);

/*******************************************************************************
* Function:     Searches a specified(NOT SORTED RELATED)data in the list through 
*               index range (from, to)(to NOT INCLUDED), according to IsMatch 
*               function, if data is found, return pointer to the MATCHED node.
* Arguments:    start iter (from), end iter (to), IsMatch function, data.
* Return value: pointer to the MATCHED node.
*               If user_data is not found - return iter (to).
* Notes:        
* Complexity:   O(n)
*******************************************************************************/
sortlist_iter_ty SortListFindIf(sortlist_iter_ty from, sortlist_iter_ty to, Sort_IsMatch_ty is_match, void *user_data);

/* TODO: USE DLISTSPLICE()! */
/*******************************************************************************
* Function:     merges 2 sorted lists with the SAME sorting function, into 1 list.
*               return the merged list.
* Arguments:    pointer to dest_list, pointer to src_list.
* Return value: pointer to the new merged sorted list.
* Notes:  	emptys list2.      
*		Undefined behavior if one of the sorted lists given is NULL.
*		undefined behavior if sorting function isnt equal in both lists. 		
* Complexity:   O(n)
*******************************************************************************/
sortlist_ty *SortListMerge(sortlist_ty *dest_list, sortlist_ty *src_list);




/* Nothing to see below this line */

struct sortlist_iter
{
    dlist_iter_ty d_iter;
};



#endif /* __SORTLIST_H__ */