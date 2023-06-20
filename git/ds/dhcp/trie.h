#ifndef __TRIE_H__
#define __TRIE_H__

/******************************************************************************/
/*			               	Trie Tree     		                              */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  
* AUTHOR:       HRD 24
* REVIEWER:
* DATE: 		12.6.22
* VERSION: 		0.0.1
*******************************************************************************/

#include <stddef.h> /* size_t */

typedef struct trie trie_ty;
typedef struct trie_node trie_node_ty;

typedef enum {
	SUCCESSs,
	ALLOCATION_FAILEDs,
	IS_FULLs,
	BAD_IPs
} ERROR_TYPs;

/*******************************************************************************
* Function:     This function creates a new trie tree
* Arguments:    Size of the height of the tree
* Return value: A pointer to tree
* Notes:		Complexity O(1). Returns NULL on failure
*******************************************************************************/
trie_ty *TrieCreate(size_t height);

/*******************************************************************************
* Function:     This function destroyes a given trie tree
* Arguments:    A pointer to the trie tree
* Notes:		Complexity(O(n))
*******************************************************************************/
void TrieDestroy(trie_ty *trie);

/*******************************************************************************
* Function:     This function returns a :3 
* Arguments:    A pointer to trie tree, a path if interested in one
* Return value: A new path is loaded to 'path' , int == status
* Notes:		If path exists, returns the next biggest path. 
*******************************************************************************/
int TrieCreateNewPath(trie_ty *trie, char *path);

/*******************************************************************************
* Function:     This function finds a given path in the trie tree
* Arguments:    A pointer to the trie tree and a path
* Return value: 0101010011
* Notes:		
*******************************************************************************/
int TrieFindPath(trie_ty *trie, char *path);


/*******************************************************************************
* Function:    This function frees a given path 
* Arguments:    A pointer to the trie tree and a path
* Return value: 0 on success, non zero on failure
* Notes:		
*******************************************************************************/
int TrieFreePath(trie_ty *trie, char *path);

/*******************************************************************************
* Function:     
* Arguments:    
* Return value: 
* Notes:		
*******************************************************************************/
size_t TrieSize(trie_ty *trie);

size_t TrieGetHeight(trie_ty *trie);

#endif      /* __TRIE_H__ */