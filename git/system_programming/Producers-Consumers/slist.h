#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h> /* size_t */

/******************************************************************************/
/*				SINGLY LINKED LIST     		         */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A singly linked list data structure, which supports inserting or
*              removing nodes, count nodes, find nodes (in specific range to
*              improve efficiency), and sequential access to every node in the list.
* AUTHOR: HRD 24
* REVIEWER:
* DATE: 12/04/2022
* VERSION: 1.3
*******************************************************************************/

typedef struct slist slist_ty;
typedef struct slist_node slist_node_ty;
typedef slist_node_ty* slist_iter_ty;

/* returns 1 in case of match between data and user_data, else returns 0      */
typedef int (*IsMatch_ty)(void *data, void *user_data); 

/* performs an operation on data, returns 1 for success else 0
   parameter - user parameter                                                 */
typedef int (*UserFunction_ty)(void *data, void *parameter); 


/*******************************************************************************
* Function: Create a new singly linked list.
* Arguments: 
* Return value: A pointer to the new linked list handler.
* Notes: A created list MUST be destroyed after use!
* Complexity: O(1)
*******************************************************************************/
slist_ty *SlistCreate(void);


/*******************************************************************************
* Function: Frees the memory allocated for the slist.
* Arguments: A pointer to the linked list.
* Return value: None
* Complexity: O(n)
*******************************************************************************/
void SlistDestroy(slist_ty *list);


/*******************************************************************************
* Function: Adds a new element before the specified location (iter) in the list.
* Arguments: iter, void ptr to data.
* Return value: An iterator to new node
* Notes: if allocation failed - returns an iterator pointing to dummy node (END).
* Complexity: O(1); In case allocation failed - O(n)
*******************************************************************************/
slist_iter_ty SlistInsertBefore(slist_iter_ty iter, const void *data);


/*******************************************************************************
* Function: Deletes the node in the given location (iter)
* Arguments: iter
* Return value: iter to the next node
* Notes: undefind behavior - if iter points to slist END
* Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistRemove(slist_iter_ty iter);


/*******************************************************************************
* Function: Returns the current number of nodes in the linked list.
* Arguments: A pointer to the list.
* Return value: The number of nodes in the list.
* Notes:
* Complexity: O(n)
*******************************************************************************/
size_t SlistCount(const slist_ty *list);


/*******************************************************************************
* Function: Searches a specified data in the list through index range (from, to)
*           according to IsMatch function.
* Arguments: start iter (from), end iter (to), void pointer to data
* Return value: iter if data is found; 
*               If user_data is not found - return iter pointing to (to).
* Notes:
* Complexity: O(n)
*******************************************************************************/
slist_iter_ty SlistFind(slist_iter_ty from, slist_iter_ty to, IsMatch_ty IsMatch, void *user_data);


/*******************************************************************************
* Function: Iterate over the data in the list through index range (from-to), 
*           allowing the user to execute a function on every data in the 
*           specified range. This function calls UserFunction until fail. if 
*           UserFunction fails, it stops looping and returns failure value (1).
*           Otherwise, return success value (0).
* Arguments: start iter (from), end iter (to), pointer to function of type 
*            UserFunction_ty, void pointer to user parameter.
* Return value: 0 for success, 1 for failure.
* Notes: 
* Complexity: O(n)
*******************************************************************************/
int SlistForEach(slist_iter_ty from, slist_iter_ty to, UserFunction_ty UserFunction, void *parameter);


/*******************************************************************************
* Function: Returns an iter to the first node in the list.
* Arguments: A pointer to the list.
* Return value: An iter to the first node in the list. 
*               if empty - return an iter to slist END dummy.
* Notes: 
* Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistBegin(const slist_ty *list);


/*******************************************************************************
* Function: Returns an iter to the last dummy node in the list.
* Arguments: A pointer to the list.
* Return value: An iter to the last dummy node in the list.
* Notes: 
* Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistEnd(const slist_ty *list);


/*******************************************************************************
* Function: Returns an iter points to the next node in the list.
* Arguments: An iter to a node in the list.
* Return value: An iter points to the next node in the list.
* Notes: Undefined behavior - if iter is slist END.
* Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistNext(slist_iter_ty iter);


/*******************************************************************************
* Function: Returns a pointer to the data in the specified iter in the list.
* Arguments: An iter to a node in the list.
* Return value: Void pointer to the data in the specified location.
* Notes: Undefined behavior - if iter points to slist END.
* Complexity: O(1)
*******************************************************************************/
void *SlistGetData(slist_iter_ty iter);


/*******************************************************************************
* Function: Set the data in the specified iter in the list.
* Arguments: iter, void ptr to new_data
* Notes: Undefined behavior - if iter points to slist END.
* Complexity: O(1)
*******************************************************************************/
void SlistSetData(slist_iter_ty iter, void *new_data);


/*******************************************************************************
* Function: Checks if two iterators are equal (points to the same node) - 
*           returns 1 if equal, 0 if not.
* Arguments: iter1, iter2
* Return value: 1 = equal; 0 = not equal
* Notes: 
* Complexity: O(1)
*******************************************************************************/
int SlistIterIsEqual(slist_iter_ty iter1, slist_iter_ty iter2);

slist_ty *SlistAppend(slist_ty *list1, slist_ty *list2);


#endif /* __SLIST_H__ */
