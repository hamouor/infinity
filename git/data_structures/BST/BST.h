#ifndef __BST_H__
#define __BST_H__

/******************************************************************************/
/*				BINARY SEARCH TREE     		         */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  A Binary Search Tree is a Data Structure, whose internal nodes 
                each store a key greater than all the keys in the node's left 
                subtree and less than those in its right subtree.
* AUTHOR:       HRD 24
* REVIEWER:
* DATE: 		22/5/22
* VERSION: 		0.21
*******************************************************************************/

#include <stddef.h> /* size_t */

typedef struct bst bst_ty; 
typedef struct bst_iter bst_iter_ty;

/* returns negative if data1 < data2. returns positive if data1 > data2, 0 if data1 is equal data2 */
typedef int(*CompFunc)(void* data1, void* data2); 

/* performs an operation on data, returns 0 for success else 1
   parameter - user parameter                                            */
typedef int(*UserFunction_ty)(void *data, void *parameter);

/* DO NOT TOUCH! Subject to change! */
typedef struct bst_node bst_node_ty;

struct bst_iter
{
    bst_node_ty *node;
};

extern const bst_iter_ty BAD_ITER;

/*******************************************************************************
* Function:     Create a new binary search tree.
* Arguments:    CompFunc pointer 
* Return value: A pointer to the new BST; NULL on failure.
* Notes:		Complexity - O(1)
*               undefinde behaviour if illegal compare function address.
*******************************************************************************/
bst_ty *BSTCreate(CompFunc comp_func);

/*******************************************************************************
* Function:     Destroy an existing binary search tree.
* Arguments:    A pointer to the existing binary tree.
* Return value: None
* Notes:        Complexity - O(n)
*               undefinde behaviour if illegal bst address.
*******************************************************************************/
void BSTDestroy(bst_ty *bst);


/*******************************************************************************
* Function:     Determine if the tree is empty
* Arguments:    A pointer to existing binary tree
* Return value: 1 if the BST is empty; 0 if not. 
* Notes: 		Complexity - O(1)
*               undefinde behaviour if illegal bst address.
*******************************************************************************/
int BSTIsEmpty(bst_ty *bst);

/*******************************************************************************
* Function:     Determine the size of the tree.
* Arguments:    A pointer to existing binary tree.
* Return value: The number of the nodes in the tree.
* Notes: 		Complexity - O(1)
*               undefinde behaviour if illegal bst address.
*******************************************************************************/
size_t BSTSize(bst_ty *bst);

/*******************************************************************************
* Function:     Insert a new node into the tree.
* Arguments:    bst - A pointer to the BST;
				data - A void pointer to the data to add
* Return value: Iter to the new node. if node Creating failed - returns BAD_ITER
* Notes:        Best case - O(Log2(N)); Worst case - O(n)
*               (undefinde behaviour if illegal bst address?)\\
*******************************************************************************/
bst_iter_ty BSTInsert(bst_ty *bst, void *data);

/*******************************************************************************
* Function:     Removeing An Existing Node From The Tree
* Arguments:    An iter To the Node We Want To Remove
* Return value: The data of the removed node
* Notes:        undefined behaviour if iter does not exist in the tree.
*               Best case - O(Log(N)); Worst case - O(n)
*******************************************************************************/
void *BSTRemove(bst_iter_ty iter);

/*******************************************************************************
* Function:     Get Data From The Given iter
* Arguments:    iter to a Node
* Return value: data in the node
* Notes:        O(1)/
*               undefinde behaviour if illegal iter address.
*******************************************************************************/
void *BSTGetData(bst_iter_ty iter);

/*******************************************************************************
* Function:     Returns an iter to the node with the smallest data in the tree.
* Arguments:    A pointer to the binary tree.
* Return value: An iter to the root of the tree.
* Notes: 		Complexity - O(n)
*               undefinde behaviour if illegal bst address.
*               undefinde behaviour if BST is empty
*******************************************************************************/
bst_iter_ty BSTBegin(bst_ty *bst);

/*******************************************************************************
* Function:     Returns the Higest value in the tree.
* Arguments:    pointer To The Binary Tree.
* Return value: Returns the Higest value in the tree.
* Notes:        Best case - O(Log(N)); Worst case - O(n)
*               undefinde behaviour if illegal bst address.
*               undefinde behaviour if BST is empty
*******************************************************************************/
bst_iter_ty BSTEnd(bst_ty *bst);

/*******************************************************************************
* Function:     Returning The closest lower value in the tree
* Arguments:    iter To A Node
* Return value: iter Of Requested Node, BAD_ITER if no such iter exist.
* Notes:        Best case - O(Log(N)); Worst case - O(n)
*               undefined behaviour if iter does not exist in the tree.
*******************************************************************************/
bst_iter_ty BSTPrev(bst_iter_ty iter);

/********************************************* Function:     Returning The closest higher value in the tree
* Arguments:    iter To A Node
* Return value: iter Of Requested Node, BAD_ITER if no such iter exist.
* Notes:        Best case - O(Log(N)); Worst case - O(n)
*               undefined behaviour if iter does not exist in the tree.***********************************

*******************************************************************************/
bst_iter_ty BSTNext(bst_iter_ty iter);

/*******************************************************************************
* Function:     Determining If Iters Are Equal
* Arguments:    Two Iters To Be Compared
* Return value: 1 If Equal 0 If Not
* Notes:        O(1)/
*******************************************************************************/
int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2);

/*******************************************************************************
* Function:     Search for the specified data in the tree through sub tree, 
                according to the trees compare function.
* Arguments:    A pointer to the BST.
				user_data - data to search.
* Return value: Iter to the node - if data is found; if not return BAD_ITER
* Notes: 		Complexity - O(n)
*               undefinde behaviour if illegal bst address or user_data is NULL.
*******************************************************************************/
 bst_iter_ty BSTFind(bst_ty *bst, void *user_data);

/*******************************************************************************
* Function:     Iterate Over The Data In The Tree Through sub tree, Allowing The 
*               User To Execute
*               A Function On Every Data In The Specified Range, from the value 
*               of iter 'from' to the value of iter 'to' (not included).
*               This function calls UserFunction Until fail. if UserFunction
*               Fails, It stops Looping And Returns Failure Value (1).
*               Otherwise, Return Success Value (0).
* Arguments:    iters from and to.  Function Of Type UserFunction_ty,
*               Pointer To Parameter To Be Included In The Given Type UserFunction_ty.
* Return value: 0 For Success, 1 for Failure.
* Notes:
* Complexity:   O(n)
*               undefinde behaviour if illegal user function address or
*               if iter from or to do not exist in the tree.
********************************************************\***********************/
int BSTForEach(bst_iter_ty from, bst_iter_ty to, UserFunction_ty UserFunction, void *parameter);



#endif      /* __BST_H__ */