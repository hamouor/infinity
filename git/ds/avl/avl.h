#ifndef __AVL_H__
#define __AVL_H__

/******************************************************************************/
/*  		                        AVL TREE            		              */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  An AVL tree is a data structure of type Binary Search Tree which
                support insertion and removal of data according to a given sort
                function.
* AUTHOR: Isaac "Bougie" Herzog
* REVIEWER: Matanyahu Englman
* DATE: 31/05/2022
* VERSION: 0.1
*******************************************************************************/

#include <stddef.h> /* size_t */

typedef enum
{
     PRE_ORDER,
     IN_ORDER,
     POST_ORDER
} order_ty;


typedef struct avl avl_ty;

/*returns > 0 if data1 > data2. returns < 0 if data1 < data2. 0 if data1 = data2*/
typedef int(*CompFunc)(void* data1, void* data2); 

/* Performs user func on the data using param, returns 0 for success else 1   */
typedef int(*UserFunction_ty)(void *data, void *parameter);

/*******************************************************************************
* Function:     Creates a new avl tree.
* Arguments:    A compare function to sort the avl tree.
* Return value: A pointer to the new avl; NULL on failure.
* Notes:		Complexity - O(1).
*******************************************************************************/
avl_ty *AVLCreate(CompFunc comp_func);

/*******************************************************************************
* Function:     Destroy an existing avl tree.
* Arguments:    A pointer to the existing avl tree.
* Return value: None.
* Notes:        Complexity - O(n).
*******************************************************************************/
void AVLDestroy(avl_ty *avl);

/*******************************************************************************
* Function:     Determines the size of the tree.
* Arguments:    A pointer to existing avl tree.
* Return value: The number of the nodes in the tree.
* Notes: 		Complexity - O(n).
*******************************************************************************/
size_t AVLSize(avl_ty *avl);

/*******************************************************************************
* Function:     Determines the height of the tree.
* Arguments:    A pointer to existing avl tree.
* Return value: The max number of the nodes from root to leaf.
* Notes:        Complexity - O(1)
*******************************************************************************/
unsigned short AVLHeight(avl_ty *avl);

/*******************************************************************************
* Function:     Determines if the tree is empty.
* Arguments:    A pointer to existing avl tree.
* Return value: 1 if the avl is empty; zero if not. 
* Notes: 		Complexity - O(1).
*******************************************************************************/
int AVLIsEmpty(avl_ty *avl);

/*******************************************************************************
* Function:     Inserts a new node into the tree.
* Arguments:    avl - A pointer to the avl.
				data - A void pointer to the data to add.
* Return value: 0 on success, 1 on failure.
* Notes:        Complexity - O(log n).
*******************************************************************************/
int AVLInsert(avl_ty *avl, void *data);

/*******************************************************************************
* Function:     Removes an existing node from the tree.
* Arguments:    An avl and the data to remove.
* Return value: The data of the removed node; NULL on failure (node wasn't found) 
* Notes:        Complexity - O(log n).
*******************************************************************************/
void *AVLRemove(avl_ty *avl, void *data);

/*******************************************************************************
* Function:     Checks if the given data is already in the avl.
* Arguments:    A pointer to the avl.
				user_data - data to search.
* Return value: void pointer to data found and is stored in avl. NULL if unfound.
* Notes: 		Complexity - O(log n)
*******************************************************************************/
 void *AVLFind(avl_ty *avl, void *user_data);

/*******************************************************************************
* Function:     Performs the given function with the given data on every node in
                the specific order which was requested.
* Arguments:    A pointer to the avl.
				UserFunction - function of type UserFunction_ty.
*               parameter - void ptr to UserFunction parameters.
				order_ind - PRE_ORDER, IN_ORDER or POST_ORDER (enum).
* Return value: 0 For Success, 1 for Failure.
* Notes:        Complexity - O(n).
*******************************************************************************/
int AVLForEach(avl_ty *avl, UserFunction_ty UserFunction, void *parameter, order_ty order_ind);

void PrintTree(avl_ty *avl);


#endif      /* __AVL_H__ */


