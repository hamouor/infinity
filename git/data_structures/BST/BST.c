#include<stdlib.h>
#include <assert.h>

#include"BST.h"

typedef enum 
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
}children;

struct bst_node
{
    void *data;
    bst_node_ty *parent;
    bst_node_ty *children[NUM_OF_CHILDREN];
};

struct bst
{
    bst_node_ty *root;
    CompFunc comp_func;
    size_t size;
};

/*from node, in the direction of child, go until you reach null and return the node*/
static bst_node_ty* AllTheWay(bst_node_ty* node, children child);

static bst_iter_ty BSTNodeToIter(bst_node_ty* node);

static bst_node_ty *BSTIterToNode(bst_iter_ty iter);
/*returns the first node. not the dummy*/
static bst_node_ty* BSTGetRoot(bst_ty* bst);
/*returns the child of node in the direction child*/
static bst_node_ty* BSTGetChild(bst_node_ty* node, children child);
/*creates new node with data set. all other vals are NULL. returns NULL in case of malloc fail*/
static bst_node_ty* BSTCreateNode(void* data);
/*returns parent of node. in case node is root, returns null*/
static bst_node_ty* BSTGetParent(bst_node_ty* node);
/*returns dummy root according to node (moves up the tree)*/
static bst_node_ty* BSTGetDummy(bst_node_ty* node);

static int IsBadIter(bst_iter_ty iter);

static int IsLeaf(bst_node_ty* node);
/*returns the direction of child according to its parent*/
static children WhosYourDaddy(bst_node_ty *child);
/*frees child, updates parent->children in that direction to be null*/
static void KillChild(bst_node_ty *child);

static bst_iter_ty ClosestByDirection(bst_iter_ty iter, children direction);


const bst_iter_ty BAD_ITER = {NULL};


bst_ty *BSTCreate(CompFunc comp_func)
{
    bst_ty *new_bst = NULL;
    bst_node_ty *dummy = NULL;

    assert(comp_func);

    new_bst = (bst_ty*)malloc(sizeof(bst_ty));
    if(!new_bst)
    {
        return NULL;
    }
    
    dummy = BSTCreateNode((void*)new_bst);

    if(!dummy)
    {
        free(new_bst);
        return NULL;
    }

    dummy->parent = NULL;
    new_bst->root = dummy;
    new_bst->comp_func = comp_func;
    new_bst->size = 0;

    return new_bst;
}

void BSTDestroy(bst_ty *bst)
{
    bst_node_ty *runner = NULL, *temp = NULL;

    assert(bst);
        
    if (!BSTIsEmpty(bst))
    {
        runner = BSTGetRoot(bst);

        while(!BSTIsEmpty(bst))
        {
            while(!IsLeaf(runner))
            {
                runner = AllTheWay(runner, LEFT);
                runner = AllTheWay(runner, RIGHT);
            }
            temp = BSTGetParent(runner);
            KillChild(runner);
            bst->size -= 1;
            runner = temp;
            
        }
    }  
    free(bst->root);
    free (bst);
}

void *BSTRemove(bst_iter_ty iter)
{
    bst_node_ty *current = NULL, *next = NULL, *parent = NULL, *temp = NULL;
    void* ret_data = NULL;
    bst_ty *bst = NULL;

    assert(!(IsBadIter(iter)));

    ret_data = BSTGetData(iter);

    current = BSTIterToNode(iter);

    parent = BSTGetDummy(current);

    bst = BSTGetData(BSTNodeToIter(parent));

    if(IsLeaf(current))
    {
        KillChild(current);
    }
    else
    { /*if and else are same, just with reverse directions (RIGHT/LEFT). this is for cases where we have only right or left child*/
        if(current->children[LEFT])
        {   
            /*next will be deleted later, we need its children to remain in the tree and its parent to be updated*/ 
            next = AllTheWay(BSTGetChild(current, LEFT), RIGHT);
            parent = BSTGetParent(next);
            temp = next->children[LEFT];
            /*finding which side next came from before deleting it, and updating its parent node*/
            if(next->parent == current)
            {
                parent->children[LEFT] = temp;
            }
            else
            {
                parent->children[RIGHT] = temp;
            }
        }
        else
        {
            /*next will be deleted later, we need its children to remain in the tree and its parent to be updated*/ 
            next = AllTheWay(BSTGetChild(current, RIGHT), LEFT);
            parent = BSTGetParent(next);
            temp = next->children[RIGHT];
            /*finding which side next came from before deleting it, and updating its parent node*/
            if(next->parent == current)
            {
                parent->children[RIGHT] = temp;
            }
            else
            {
                parent->children[LEFT] = temp;
            }
        }
        current->data = next->data;
        /*if the deleted node had children- reconnect to tree*/
        if(temp)
        {
            temp->parent = parent;
        }
        KillChild(next);
    }
    bst->size -= 1;
    return ret_data;
}

int BSTIsEmpty(bst_ty *bst)
{
    assert(bst);

    return (!(bst->size));
}

size_t BSTSize(bst_ty *bst)
{
    assert(bst);

    return (bst->size);
}
/*#include<stdio.h>*/
bst_iter_ty BSTInsert(bst_ty *bst, void *data)
{
    CompFunc function;
    bst_node_ty *new_node = NULL, *runner = NULL, *temp = NULL;
    int func_res = 0;

    assert(bst);

    new_node = BSTCreateNode(data);
    if(!new_node)
    {
        return BAD_ITER;
    }

    function = bst->comp_func;
    runner = BSTGetRoot(bst);
    bst->size += 1;
    
    if (!runner)/*tree is empty- set new node as first*/
    {
        bst->root->children[RIGHT] = new_node;
        new_node->parent = bst->root;
        return  BSTNodeToIter(new_node);
    }

    while(1)
    {
        func_res = function(BSTGetData(BSTNodeToIter(runner)), data); 
        
        if(func_res > 0)
        {
            temp = BSTGetChild(runner, LEFT);
            if(!temp)
            {
                runner->children[LEFT] = new_node;
                new_node->parent = runner;
                break;
            }
        }
        else if (func_res < 0)
        {
            temp = BSTGetChild(runner, RIGHT);
            if(!temp)
            {
                runner->children[RIGHT] = new_node;
                new_node->parent = runner;
                break;
            }
        }
        runner = temp;
    }
    /*if (new_node->parent)
    {
        printf("parent:%d\n direction:%d\n child:%d\n", *(int*)(new_node->parent->data),WhosYourDaddy(new_node,new_node->parent), *(int*)(new_node->data));
    }*/
    return  BSTNodeToIter(new_node);

}

bst_iter_ty BSTFind(bst_ty *bst, void *user_data)
{
    CompFunc function;
    bst_node_ty *runner;
    int func_res = 0;

    assert(bst);

    function = bst->comp_func;
    runner = BSTGetRoot(bst);

    while(runner)
    {
        func_res = function(BSTGetData(BSTNodeToIter(runner)), user_data);
        
        if(func_res < 0)
        {
            runner = BSTGetChild(runner, RIGHT);
        }
        else if (func_res > 0)
        {
            runner = BSTGetChild(runner, LEFT);
        }
        else
        {
            return BSTNodeToIter(runner);
        }
    }

    return BAD_ITER;
}

int BSTForEach(bst_iter_ty from, bst_iter_ty to, UserFunction_ty UserFunction, void *parameter)
{
    int res = 0;

    assert(!IsBadIter(from) && !IsBadIter(to));

    while(!BSTIterIsEqual(from, to))
    {
        res = UserFunction(BSTGetData(from), parameter);
        
        if(res)
        {
            return res;
        }
        
        from = BSTNext(from);
    }

    return res;
}

bst_iter_ty BSTPrev(bst_iter_ty iter)
{

    assert(!IsBadIter(iter));

    return ClosestByDirection(iter, LEFT);
}

bst_iter_ty BSTNext(bst_iter_ty iter)/*notes same as prev-just opposite directions*/
{

    assert(!IsBadIter(iter));

    return ClosestByDirection(iter, RIGHT);
}

int BSTIterIsEqual(bst_iter_ty iter1, bst_iter_ty iter2)
{
    return(iter1.node == iter2.node);
}


bst_iter_ty BSTBegin(bst_ty *bst)
{
    bst_node_ty* runner = NULL;
    
    assert(bst && !BSTIsEmpty(bst));

    runner = BSTGetRoot(bst);

    return BSTNodeToIter(AllTheWay(runner, LEFT));
}

bst_iter_ty BSTEnd(bst_ty *bst)
{
    bst_node_ty* runner = NULL;
    
    assert(bst && !BSTIsEmpty(bst));

    runner = BSTGetRoot(bst);

    return BSTNodeToIter(AllTheWay(runner, RIGHT));
}

void *BSTGetData(bst_iter_ty iter)
{
    assert(!IsBadIter(iter));
    return (BSTIterToNode(iter)->data);
}

static bst_iter_ty BSTNodeToIter(bst_node_ty* node)
{
    bst_iter_ty iter = BAD_ITER;
    
    assert(node);

    iter.node = node;

    return iter;
}

static bst_node_ty *BSTIterToNode(bst_iter_ty iter)
{
    return iter.node;
}

static bst_node_ty* BSTGetRoot(bst_ty* bst)
{
    return BSTGetChild(bst->root, RIGHT);
}

static bst_node_ty* BSTGetChild(bst_node_ty* node, children child)
{
    return node->children[child];
}
static bst_node_ty* BSTCreateNode(void* data)
{
    bst_node_ty* new_node = NULL;
    
    assert(data);

    new_node = (bst_node_ty*)malloc(sizeof(bst_node_ty));
    if(!new_node)
    {
        return NULL;
    }

    new_node->data = data;
    new_node->children[RIGHT] = NULL;
    new_node->children[LEFT] = NULL;
    new_node->parent = NULL;

    return new_node;
}
static bst_node_ty* BSTGetParent(bst_node_ty* node)
{
    bst_node_ty* temp = NULL;

    assert(node);

    temp = node->parent;

    if(!temp->parent)
    {
        return NULL;
    }

    return temp;
}

static bst_node_ty* BSTGetDummy(bst_node_ty* node)
{
    bst_node_ty* temp = NULL, *root;

    root = node;
    temp = BSTGetParent(root);
    while(temp)
    {
        root = temp;
        temp = BSTGetParent(root);
    }

    return root->parent;
}

static int IsBadIter(bst_iter_ty iter)
{
    return (iter.node == NULL);
}

static int IsLeaf(bst_node_ty* node)
{
    return (BSTGetChild(node, RIGHT) == BSTGetChild(node, LEFT));
}

static children WhosYourDaddy(bst_node_ty *child)
{
    if(BSTGetChild(child->parent,RIGHT) == child)
    {
        return RIGHT;
    }
    return LEFT;
}

static void KillChild(bst_node_ty *child)
{
    child->parent->children[WhosYourDaddy(child)] = NULL;
    free(child);
}

static bst_node_ty* AllTheWay(bst_node_ty* node, children child)
{
    bst_node_ty *next = NULL;
    while(node)
    {
        next = node;
        node = BSTGetChild(node, child);
    }
    return next;
}

static bst_iter_ty ClosestByDirection(bst_iter_ty iter, children direction)
{
    bst_node_ty *runner = NULL, *temp = NULL;

    assert(!IsBadIter(iter));

    runner = BSTIterToNode(iter);
    temp = BSTGetChild(runner, direction);
    /*if our node had a left child, go all he way right from it- this is next*/
    if(temp)
    {
        runner = AllTheWay(temp, !direction);
        return BSTNodeToIter(runner);
    }
    /*if not, we need to go to parents until one of them is right child- that is next*/
    temp = BSTGetParent(runner);

    while(temp != NULL && WhosYourDaddy(runner) == direction)
    {
        runner = temp;
        temp = BSTGetParent(runner);
    }
    /*making sure we went right one time and didnt get to the root of the tree*/
    if(temp)
    {
        return BSTNodeToIter(temp);
    }

    return BAD_ITER;
}