#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert       */
#include <math.h>       /*pow           */

#include "trie.h"

/*enum create*/
typedef enum stat{
	FAIL,
    SUCCESS
}status;

#define BITS_IN_CHAR 8

typedef enum direction{
	ZERO,
	ONE,
	NUM_BITS
}direction_ty;

struct trie_node /* Verify padding */
{
    char                is_full;
    trie_node_ty        *children[NUM_BITS];
};

struct trie
{
    size_t              height;
    trie_node_ty        *root;
};


static void RecKillNodeNKids(trie_node_ty *node);
static trie_node_ty *NodeGetChild(trie_node_ty *parent, direction_ty direction);
static trie_node_ty *GetRoot(trie_ty *trie);
static trie_node_ty *CreateNode();
static void PathToPtr(char* path, int local_path, size_t height);
static int PtrToPath(char* ptr, size_t height);
static trie_node_ty *NewPath(trie_node_ty* root, int *path, size_t height);
static void UpdateFull(trie_node_ty* root);
static void UpdatePath(int* path, int numofbits);
static int FreePathRec(trie_node_ty *root, int path, size_t height);
static size_t SizeRec(trie_node_ty *root, size_t height);






size_t TrieGetHeight(trie_ty *trie)
{
    return trie->height;
}

trie_ty *TrieCreate(size_t height)
{
    trie_ty *new_trie = (trie_ty *)malloc(sizeof(trie_ty));

    assert(0 < height);

    /* handle failure */
    if (!new_trie)
    {
        return NULL;
    }    
    
    /* set initial values */
    new_trie->root = NULL;
    
    new_trie->height = height;

    return new_trie;
}

void TrieDestroy(trie_ty *trie)
{   
    assert(trie);
    
    if (GetRoot(trie))
    {
        /* call recursive function */
        RecKillNodeNKids(GetRoot(trie));
    }
    
    /* after emptying - delete trie */
    free(trie);
    trie = NULL;
}

static void RecKillNodeNKids(trie_node_ty *node)
{
    trie_node_ty *zero = NULL;
    trie_node_ty *one = NULL;

    if (!node)
    {
        return;
    }
    
    /* save children */
    zero = NodeGetChild(node, ZERO);
    one = NodeGetChild(node, ONE);

    /* destroy cur node */
    free(node);
    node = NULL;

    /* take it mafia style n kill the rest */
    RecKillNodeNKids(zero);
    RecKillNodeNKids(one);
}

int TrieCreateNewPath(trie_ty *trie, char *path)
{
    size_t height = 0;
    trie_node_ty *runner = NULL;
    int local_path = 0, return_path = 0;

    assert(trie);

    height = trie->height;
    runner = trie->root;
    local_path = PtrToPath(path, height);
    return_path = local_path;
    
    if(!runner)
    {
        trie->root = CreateNode();
        if(!trie->root)
        {
            return 1;
        }
        runner = trie->root;
    }

    runner = NewPath(runner, &return_path, height);
    
    PathToPtr(path, return_path, trie->height);
    
    if(!runner)
    {
        return 1;
    }

    return 0;    
}

static trie_node_ty *NewPath(trie_node_ty* root, int *path, size_t height)
{
    int bit = 0;
    trie_node_ty *ret_val = NULL;
    int step = 0;
    int right_bit = height - 1;

    bit = (*path >> right_bit) & 1;
    step = bit;
    
    if(!height)
    {
        root->is_full = 1;
        return root;
    }

    if(!root->children[bit])/*there is no child in the requested direction - create child and move to it*/
    {
        root->children[bit] = CreateNode();
        if (root->children[bit])
        {
            ret_val = NewPath(root->children[bit], path, height - 1);
        }
        else
        {
            *path = 0;
            return NULL;
        }
    }
    
    else if(!root->children[bit]->is_full)/*there is a child in the requested direction and its free - move to it*/
    {
        ret_val = NewPath(root->children[bit], path, height - 1);
    }
    
    else if(bit)/*there is a child, its in the ONE direction and it full*/
    {
        return NULL;
    }

    else if(root->children[!bit])/*there is a child in the ZERO direction and its full and there is a child in the one direction- move to it and update path*/
    {
        step = !bit;
        UpdatePath(path, right_bit);
        ret_val = NewPath(root->children[!bit], path, height - 1);
    }

    else/*there is a child in the ZERO direction and its full and there is'nt a child in the one direction- create child and move to it and update path*/
    {
        root->children[!bit] = CreateNode();
        if (root->children[!bit])
        {
            step = !bit;
            UpdatePath(path, right_bit);
            ret_val = NewPath(root->children[!bit], path, height - 1);
        }
        else
        {
            *path = 0;
            return NULL;
        }
    }

    if(!ret_val && bit) /*recursion returned NULL- and the direction i stepped in is ONE - keep returning NULL*/
    {
        return NULL;
    }

    else if(!ret_val && root->children[!bit] && !root->children[!bit]->is_full) /*recursion returned NULL, and the direction i stepped in is ZERO and ONE direction is free - move to ONE and update path*/
    {
        UpdatePath(path, right_bit);
        step = !bit;
        ret_val = NewPath(root->children[!bit], path, height - 1);
    }

    else if(!ret_val && root->children[!bit] && root->children[!bit]->is_full)/*recursion returned NULL, and the direction i stepped in is ZERO and ONE direction is full*/
    {
        return NULL;
    }


    else if(!ret_val)/*recursion returned NULL and the direction i stepped in is ZERO and there isnt a child in the ONE direction - create child and move to it*/
    {
        root->children[!bit] = CreateNode();
        if (root->children[!bit])
        {
            step = !bit;
            UpdatePath(path, right_bit);
            ret_val = NewPath(root->children[!bit], path, height - 1);
        }
        else
        {
            *path = 0;
            return NULL;
        }
    }
    if(ret_val)
    {
        UpdateFull(root);
    }
    
    *path = *path | (step << right_bit);
    
    
    return ret_val;
}

static void UpdatePath(int* path, int numofbits)
{
    *path = (*path >> numofbits) << numofbits;
}

static void UpdateFull(trie_node_ty* root)
{
    if(root->children[ONE] && root->children[ZERO] && root->children[ONE]->is_full && root->children[ZERO]->is_full)
    {
        root->is_full = 1;
    }
    else
    {
        root->is_full = 0;
    }
    
}

int TrieFreePath(trie_ty *trie, char *path)
{
    trie_node_ty *runner = NULL;
    int status = 0, path_int = 0;
    size_t height = 0;

    assert(trie && path);

    height = trie->height;
    runner = GetRoot(trie);
    path_int = PtrToPath(path, height);
    status = FreePathRec(runner, path_int, height);

    if (status == -1)
    {
        status = 3;
    }

    if (status == 1)
    {
        trie->root = NULL;
    }
    /* walk down as path shows */
    /* check is full on every node > if full, cool. */
    /* else > return didnt find */

    return status;     
}

static int FreePathRec(trie_node_ty *root, int path, size_t height)
{
    int right_bit = 0;
    int bit = 0;
    int ret_val = 0;

    right_bit = height - 1;
    bit = (path >> right_bit) & ONE;

    if(!root)
    {
        return -1;
    }

    if(!height)
    {
        free(root);
        return 1;
    }

    ret_val = FreePathRec(root->children[bit], path, height - 1);
    
    if( ret_val == 1)
    {
        root->children[bit] = NULL;
        if(!root->children[!bit])
        {
            free(root);
            return 1;
        }

        root->is_full = 0;
        return 0;
    }

    if (ret_val == 0)
    {
        root->is_full = 0;
        return 0;
    }

    return -1;
}

static int PtrToPath(char* ptr, size_t height)
{
    int local_path = 0;
    int i = 0;
    int numofchars = height / BITS_IN_CHAR - 1;
    int curr = '\0';

    for(;i <= numofchars ; ++i)
    {
        local_path <<= BITS_IN_CHAR;
        curr = *(ptr + i);
        local_path |= curr;
    }
    return local_path;
}

static void PathToPtr(char* path, int local_path, size_t height)
{
    int i = 0;
    int numofchars = height / BITS_IN_CHAR - 1;

    *path = 0;
    for(; i <= numofchars; ++i)
    {
        *(path + i) |= (local_path >> (BITS_IN_CHAR * (numofchars - i)));
    }
}

static trie_node_ty *CreateNode()
{
    trie_node_ty *new_node = NULL;

    new_node = (trie_node_ty*)malloc(sizeof(trie_node_ty));

    if (!new_node)
    {
        return NULL;
    }
    new_node->is_full = 0;
    new_node->children[ZERO] = NULL;
    new_node->children[ONE] = NULL;

    return new_node;
}


static trie_node_ty *NodeGetChild(trie_node_ty *parent, direction_ty direction)
{
    return parent->children[direction];
}

static trie_node_ty *GetRoot(trie_ty *trie)
{
    return trie->root;
}

size_t TrieSize(trie_ty *trie)
{
    return SizeRec(trie->root, trie->height);
}

static size_t SizeRec(trie_node_ty *root, size_t height)
{
    if(!root)
    {
        return 0;
    }

    if(root->is_full)
    {
        return pow(2, height);
    }

    return SizeRec(root->children[ONE], height - 1) + SizeRec(root->children[ZERO], height - 1);
}
    
