/*******************************************************************************
*		DOUBLY LINKED LIST                                                    
*******************************************************************************/
/********************************************************
* DESCRIPTION: A Doubly linked list data structure, which
* supports inserting or removing nodes, count nodes, find
* nodes (in specific range to improve efficiency), and 
* sequential access to every node in the list.
* AUTHOR: HDR24
* REVIEWER:
* DATE: 19/04/2022
* VERSION: 0.2
* Time of last Change: 16:09
*******************************************************************************/


#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

typedef struct dlist dlist_ty;
typedef struct dlist_node* dlist_iter_ty;

/* returns 1 in case of match between data and user_data, else returns 0 */
typedef int(*IsMatch_ty)(void *data, void *user_data); 

/* performs an operation on data, returns 0 for success else 1
   parameter - user parameter                                            */
typedef int(*UserFunction_ty)(void *data, void *parameter); 

#ifndef NDEBUG
void AssertIter(dlist_iter_ty iter);
#endif  /* NDEBUG */

/*******************************************************************************
* Function:     Create a new doubly linked list.
* Arguments: 
* Return value: A pointer to the new linked list handler or 
*               NULL on failure
* Notes:        A created list MUST be destroyed after use!
* Complexity:   O(1)
*******************************************************************************/
dlist_ty *DlistCreate(void);


/*******************************************************************************
* Function:     Frees the memory allocated for the dlist.
* Arguments:    A pointer to the linked list.
* Return value: None
* Notes:        Undefiend behavior if list in NULL
* Complexity:   O(n)
*******************************************************************************/
void DlistDestroy(dlist_ty *list);


/*******************************************************************************
* Function:     Add a new element before the specified location
*               (iter) in the list.
* Arguments:    iter, void ptr to data.
* Return value: A iterator to new node, if allocation failed - returns dummy iter END
* Notes:
* Complexity:   avg_case O(1), worst_case O(n)
*******************************************************************************/
dlist_iter_ty DlistInsertBefore(dlist_iter_ty iter,const void *data);


/*******************************************************************************
* Function:     Delete the node in the given location (iter)
* Arguments:    iter
* Return value: iter to the next node
* Notes:        undefined behavior - if iter is slist END
* Complexity:   O(1)
*******************************************************************************/
dlist_iter_ty DlistRemove(dlist_iter_ty iter);


/*******************************************************************************
* Function:     Returns an iter to the first valid node in the list.
* Arguments:    A pointer to the list.
* Return value: An iter to the first node in the list. 
*               if empty - dlist END dummy.
* Notes:        Undefined behavior if dlist given is NULL.
* Complexity:   O(1)
*******************************************************************************/
dlist_iter_ty DlistBegin(const dlist_ty *list);


/*******************************************************************************
* Function:     Returns an iter to the list's tail dummy node.
* Arguments:    A pointer to the list.
* Return value: An iter to the last dummy node in the list.
* Notes:        Undefined behavior if dlist given is NULL.
* Complexity:   O(1).
*******************************************************************************/
dlist_iter_ty DlistEnd(const dlist_ty *list);


/*******************************************************************************
* Function:     Returns a pointer to the next node after given iter.
* Arguments:    iter.
* Return value: iter to the next node.
* Notes:        Undefined behavior if iter given is NULL.
*               Undefined behavior - if iter is slist END.
* Complexity:   O(1)
*******************************************************************************/
dlist_iter_ty DlistNext(dlist_iter_ty iter);


/*******************************************************************************
* Function:     Returns a pointer to the previous node before the given iter.
* Arguments:    iter.
* Return value: iter to the previous node.
* Notes:        Undefined behavior if iter given is NULL.
*               Undefined behavior - if iter is the first node of the list.
* Complexity:   O(1)
*******************************************************************************/
dlist_iter_ty DlistPrev(dlist_iter_ty iter);

/*******************************************************************************
* Function:     check the given list to see if it is empty
* Arguments:    A pointer to the list.
* Return value: 1 is empty , 0 if not.
* Notes:        Undefined behavior if dlist given is NULL.
* Complexity:   O(1)
*******************************************************************************/
int DlistIsEmpty(const dlist_ty *list);

/*******************************************************************************
* Function:     counts the number of nodes in the list (excluding dummy nodes).
* Arguments:    pointer to dlist.
* Return value: number of nodes.
* Complexity:   O(n)
*******************************************************************************/
size_t DlistCount(const dlist_ty *list);

/*******************************************************************************
* Function:     Returns a pointer to the data in the specified
*               location in the list.
* Arguments:    iter
* Return value: Void pointer to the data in the specified
* location.
* Notes:        Undefined behavior - if iter is dlist END.
* Complexity:   O(1)
*******************************************************************************/
void *DlistGetData(dlist_iter_ty iter);

/*******************************************************************************
* Function:     Checks if two iterators are equal (points to the
*               same place) - returns 1 if equal, 0 if not.
* Arguments:    iter1, iter2
* Return value: 1 = equal; 0 = not equal
* Notes: 
* Complexity:   O(1)
*******************************************************************************/
int DlistIterIsEqual(dlist_iter_ty iter1, dlist_iter_ty iter2);


/*******************************************************************************
* Function:     push the given data to the end of the dlist.
* Arguments:    pointer to dlist, and void pointer to data.
* Return value: iter to the new node at dlist end.
* Notes:        Undefined behavior if dlist given is NULL.
	            On Fail - Dlist Dummy node
* Complexity:   O(1), worst_case O(n)
*******************************************************************************/
dlist_iter_ty DlistPushBack(dlist_ty *list, const void *data);

/*******************************************************************************
* Function:     push the given data to the start of the dlist
* Arguments:    pointer to dlist, and void pointer to data.
* Return value: iter to the new node at dlist start.
* Notes:        Undefined behavior if dlist given is NULL.
	            On Fail - Dlist Dummy node
* Complexity:   avg_case O(1), worst_case O(n)
*******************************************************************************/
dlist_iter_ty DlistPushFront(dlist_ty *list, const void *data);

/*******************************************************************************
* Function:     pop the node at the end of the dlist.
* Arguments:    pointer to dlist.
* Return value: the data of the popped node.
* Notes:        Undefined behavior if dlist given is NULL. --empty--
* Complexity:   O(1)
*******************************************************************************/
void *DlistPopBack(dlist_ty *list);

/*******************************************************************************
* Function:     pop the node at the front of the dlist
* Arguments:    pointer to dlist.
* Return value: the data of the popped node.
* Notes:        Undefined behavior if dlist given is NULL. --empty--
* Complexity:   O(1)
*******************************************************************************/
void *DlistPopFront(dlist_ty *list);


/*******************************************************************************
* Function:     insert the nodes in the specified range (from_src - to_src)
*               (node to_src NOT INCLUDED) before (dest_iter node) in dlist.
* Arguments:    start iter (from_src), end iter (to_src), destination iter (dest_iter).
* Return value: an iter to the first node inserted, incase of failure returns dummy iter.
* Notes:        empty the dlist from the nodes given(from_src-to_src).
* Complexity:   O(1)
*******************************************************************************/
dlist_iter_ty DlistSplice(dlist_iter_ty from_src, dlist_iter_ty to_src, dlist_iter_ty dest_iter);


/*******************************************************************************
* Function:     Searches a specified data in the list through 
* index range   (from, to), according to IsMatch function.
* Arguments:    start iter (from), end iter (to)(to NOT INCLUDED),
*               IsMatch function ,data.
* Return value: iter if data is found; 
*               If user_data is not found - return iter (to).
* Notes: 
* Complexity:   O(n)
*******************************************************************************/
dlist_iter_ty DlistFind(dlist_iter_ty from, dlist_iter_ty to, IsMatch_ty IsMatch, void *user_data);


/*******************************************************************************
* Function:     Searches a specified data in the list through 
*               index range (from, to)(to NOT INCLUDED), according to IsMatch 
*               function, if data is found, add it to the dest_list given 
*               by the user.
* Arguments:    start iter (from), end iter (to), IsMatch function, data, empty dlist.
* Return value: 0 for success , else 1
*               If user_data is not found - return iter (to).
* Notes:        Undefined behavior - if dest_list is NULL or dest_list isn't empty.
*               if dest_list wasn't empty - previous data stored in it could be lost.
* Complexity:   O(n)
*******************************************************************************/
int DlistMultiFind(dlist_iter_ty from, dlist_iter_ty to, IsMatch_ty IsMatch, void *user_data, dlist_ty *dest_list);

/*******************************************************************************
* Function:     Iterate over the data in the list through index
*               range (from-to)(to NOT INCLUDED), allowing the user to execute 
*               a function on every data in the specified range. 
*               This function calls UserFunction until fail. if UserFunction
*               fails, it stops looping and returns failure value (1).
*               Otherwise, return success value (0).
* Arguments:    start iter (from), end iter (to), function of type UserFunction_ty, 
*               pointer to parameter to be included in the given type UserFunction_ty.              
* Return value: 0 for success, 1 for failure.
* Notes: 
* Complexity:   O(n)
*******************************************************************************/
int DlistForEach(dlist_iter_ty from, dlist_iter_ty to, UserFunction_ty UserFunction, void *parameter);


#endif /* __DLIST_H__ */