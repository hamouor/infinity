#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc free*/
#include <stdio.h>  /*printf*/

#include "avl.h"

typedef struct avl_node avl_node_ty;

typedef enum 
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
}children;

struct avl_node
{
    void *data;
    avl_node_ty *parent;
    avl_node_ty *children[NUM_OF_CHILDREN];
    unsigned short height;
};

struct avl
{
    avl_node_ty *root;
    CompFunc comp_func;
};

static int printnode(void* data1, void* data2);
static int ForEachPre(avl_node_ty *root, UserFunction_ty UserFunction, void *parameter);
static int ForEachIn(avl_node_ty *root, UserFunction_ty UserFunction, void *parameter);
static int ForEachPos(avl_node_ty *root, UserFunction_ty UserFunction, void *parameter);
static avl_node_ty *SubTreeFind(avl_node_ty *root, CompFunc func, void *user_data);
static void DestroySubTree(avl_node_ty *root);
static size_t SubTreeHeight(avl_node_ty *root);
static size_t SubTreeSize(avl_node_ty *root);
static int IsLeaf(avl_node_ty* node);
static avl_node_ty* GetChild(avl_node_ty* node, children child);
static avl_node_ty *Remove(avl_node_ty *node);
static avl_node_ty* AllTheWay(avl_node_ty* node, children child);
static void KillChild(avl_node_ty *child);
static children WhosYourDaddy(avl_node_ty *child);
static int InsertSubTree(avl_node_ty *root, avl_node_ty *to_insert, CompFunc func);
static size_t max(size_t num1, size_t num2);
static avl_node_ty *SeekAndRemove(avl_node_ty *root, CompFunc func, void *user_data);
static void PropHeight(avl_node_ty *from);
static unsigned short GetHeight(avl_node_ty *node);
void Rot(avl_node_ty *root, children dir);
static avl_node_ty *CheckAndFixImbalance(avl_node_ty *root);




avl_ty *AVLCreate(CompFunc comp_func)
{
    avl_ty *new_avl = NULL;

    assert(comp_func);

    new_avl = (avl_ty*)malloc(sizeof(avl_ty));
    if(!new_avl)
    {
        return NULL;
    }

    new_avl->root = NULL;
    new_avl->comp_func = comp_func;

    return new_avl;
}

void AVLDestroy(avl_ty *avl)
{
    assert(avl);

    DestroySubTree(avl->root);

    free(avl);    
}

size_t AVLSize(avl_ty *avl)
{
    assert(avl);

    if(!avl->root)
    {
        return 0;
    }

    return SubTreeSize(avl->root);
}

unsigned short AVLHeight(avl_ty *avl)
{
    assert(avl);
    
    if(!avl->root)
    {
        return 0;
    }
    
    return avl->root->height;
}

int AVLIsEmpty(avl_ty *avl)
{
    return (avl->root == NULL);
}

int AVLInsert(avl_ty *avl, void *data)
{
    avl_node_ty *new_node = NULL, *new_root_maybe = NULL;

    assert(avl && data);

    new_node = (avl_node_ty*)malloc(sizeof(avl_node_ty));
    
    if(!new_node)
    {
        return 1;
    }

    new_node->data = data;
    new_node->children[RIGHT] = NULL;
    new_node->children[LEFT] = NULL;
    new_node->parent = NULL;
    new_node->height = 1;

    if(!avl->root)
    {
        avl->root = new_node;
        return 0;
    }

    InsertSubTree(avl->root, new_node, avl->comp_func);
    
    new_root_maybe = CheckAndFixImbalance(new_node);
    
    if(new_root_maybe && new_root_maybe->parent && !new_root_maybe->parent->parent)
    {
        avl->root = new_root_maybe->parent;
    }
    
    PropHeight(new_node);

    return 0;
}


void *AVLRemove(avl_ty *avl, void *data)
{
    void *ret_dat = NULL;
    avl_node_ty *to_free = NULL, *new_root_maybe = NULL;
    assert(avl && data);

    to_free = SeekAndRemove(avl->root, avl->comp_func, data);
    ret_dat = to_free->data;

    if(!to_free->parent)
    {
        avl->root = NULL;
        free(to_free);
        return ret_dat;
    }
    new_root_maybe = CheckAndFixImbalance(to_free->parent);
    
    if(new_root_maybe && new_root_maybe->parent && !new_root_maybe->parent->parent)
    {
        avl->root = new_root_maybe->parent;
    }
    --to_free->height;
    PropHeight(to_free->parent);
    if(IsLeaf(to_free))
    {
        KillChild(to_free);
        return ret_dat;
    }
    free(to_free);
    return ret_dat;
}

static avl_node_ty *SeekAndRemove(avl_node_ty *root, CompFunc func, void *user_data)
{
    int comp_res = 0;
    
    assert(func);

    if (!root)
    {
        return NULL;
    }

    comp_res = func(root->data, user_data);

    if (!comp_res)
    {        
        return Remove(root);
    }

    return comp_res > 0 ? SeekAndRemove(GetChild(root,LEFT), func, user_data) : SeekAndRemove(GetChild(root,RIGHT), func, user_data);
    /*root->height = 1 + max(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT]));*/
}

void *AVLFind(avl_ty *avl, void *user_data)
{
    assert(avl && user_data);

    return SubTreeFind(avl->root, avl->comp_func, user_data)->data;
}

int AVLForEach(avl_ty *avl, UserFunction_ty UserFunction, void *parameter, order_ty order_ind)
{
    assert(avl && UserFunction && parameter);

    if(order_ind == PRE_ORDER)
    {
        return ForEachPre(avl->root, UserFunction, parameter);
    }

    if(order_ind == POST_ORDER)
    {
        return ForEachPos(avl->root, UserFunction, parameter);
    }

    if(order_ind == IN_ORDER)
    {
        return ForEachIn(avl->root, UserFunction, parameter);
    }
    return 0;
}

static int ForEachPre(avl_node_ty *root, UserFunction_ty UserFunction, void *parameter)
{
    int res_root = 0, res_r = 0, res_l = 0;

    if(!root)
    {
        return 0;
    }
    
    res_root = UserFunction(root->data, parameter);
    if(res_root)
    {
        return res_root;
    }
    
    res_l = ForEachPre(GetChild(root, LEFT), UserFunction, parameter);
    if(res_l)
    {
        return res_l;
    }

    res_r = ForEachPre(GetChild(root, RIGHT), UserFunction, parameter);
    if(res_r)
    {
        return res_r;
    }

    return 0;
}

static int ForEachIn(avl_node_ty *root, UserFunction_ty UserFunction, void *parameter)
{
    int res_root = 0, res_r = 0, res_l = 0;

    if(!root)
    {
        return 0;
    }
    
    res_l = ForEachIn(GetChild(root, LEFT), UserFunction, parameter);
    if(res_l)
    {
        return res_l;
    }

    res_root = UserFunction(root->data, parameter);
    if(res_root)
    {
        return res_root;
    }

    res_r = ForEachIn(GetChild(root, RIGHT), UserFunction, parameter);
    if(res_r)
    {
        return res_r;
    }

    return 0;
}

static int ForEachPos(avl_node_ty *root, UserFunction_ty UserFunction, void *parameter)
{
    int res_root = 0, res_r = 0, res_l = 0;

    if(!root)
    {
        return 0;
    }
    
    res_l = ForEachPos(GetChild(root, LEFT), UserFunction, parameter);
    if(res_l)
    {
        return res_l;
    }

    res_r = ForEachPos(GetChild(root, RIGHT), UserFunction, parameter);
    if(res_r)
    {
        return res_r;
    }

    res_root = UserFunction(root->data, parameter);
    if(res_root)
    {
        return res_root;
    }

    return 0;
}

static avl_node_ty *SubTreeFind(avl_node_ty *root, CompFunc func, void *user_data)
{
    int comp_res = 0;
    
    assert(func);

    if (!root)
    {
        return NULL;
    }

    comp_res = func(root->data, user_data);

    if (!comp_res)
    {
        return root;
    }

    return comp_res > 0 ? SubTreeFind(GetChild(root,LEFT), func, user_data) : SubTreeFind(GetChild(root,RIGHT), func, user_data);
}

static void DestroySubTree(avl_node_ty *root)
{
    avl_node_ty *sub1 = NULL, *sub2 = NULL;

    if(!root)
    {
        return;
    }

    sub1 = GetChild(root, RIGHT);
    sub2 = GetChild(root, LEFT);
    free(root);

    DestroySubTree(sub1);
    DestroySubTree(sub2);
}

static size_t SubTreeHeight(avl_node_ty *root)
{
    if(!root)
    {
        return 0;
    }

    if(IsLeaf(root))
    {
        return 1;
    }

    return 1 + max(SubTreeHeight(GetChild(root, RIGHT)), SubTreeHeight(GetChild(root, LEFT)));
}

static size_t SubTreeSize(avl_node_ty *root)
{
    if(!root)
    {
        return 0;
    }

    if(IsLeaf(root))
    {
        return 1;
    }

    return 1 + SubTreeSize(GetChild(root, RIGHT)) + SubTreeSize(GetChild(root, LEFT));
}

static int IsLeaf(avl_node_ty* node)
{
    return (GetChild(node, RIGHT) == GetChild(node, LEFT));
}

static avl_node_ty* GetChild(avl_node_ty* node, children child)
{
    return node->children[child];
}


static avl_node_ty *Remove(avl_node_ty *node)
{
    avl_node_ty *current = NULL, *next = NULL, *parent = NULL, *temp = NULL;

    assert(node);

    current = node;

    if(IsLeaf(current))
    {
        return current;
    }
    else
    { /*if and else are same, just with reverse directions (RIGHT/LEFT). this is for cases where we have only right or left child*/
        if(current->children[LEFT])
        {   
            /*next will be deleted later, we need its children to remain in the tree and its parent to be updated*/ 
            next = AllTheWay(GetChild(current, LEFT), RIGHT);
            parent = next->parent;
            temp = next->children[LEFT];
            /*finding which side next came from before deleting it, and updating its parent node*/
            if(parent == current)
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
            next = AllTheWay(GetChild(current, RIGHT), LEFT);
            parent = next->parent;
            temp = next->children[RIGHT];
            /*finding which side next came from before deleting it, and updating its parent node*/
            if(parent == current)
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
        return next;
    }
}

static void PropHeight(avl_node_ty *from)
{
    while(from != NULL)
    {
        from->height = 1 + max(GetHeight(from->children[RIGHT]), GetHeight(from->children[LEFT]));
        from = from->parent;
    }
}

static unsigned short GetHeight(avl_node_ty *node)
{
    if(!node)
    {
        return 0;
    }
    return node->height;
}

static avl_node_ty* AllTheWay(avl_node_ty* node, children child)
{
    avl_node_ty *next = NULL;
    while(node)
    {
        next = node;
        node = GetChild(node, child);
    }
    return next;
}
static void KillChild(avl_node_ty *child)
{
    child->parent->children[WhosYourDaddy(child)] = NULL;
    if(!child->parent->children[!WhosYourDaddy(child)])
    {
        child->parent->height = 1;
    }
    free(child);
}

static children WhosYourDaddy(avl_node_ty *child)
{
    if(GetChild(child->parent,RIGHT) == child)
    {
        return RIGHT;
    }
    return LEFT;

}
static int InsertSubTree(avl_node_ty *root, avl_node_ty *to_insert, CompFunc func)
{
    if (func(root->data, to_insert->data) > 0)
    {
        if(!GetChild(root,LEFT))
        {
            root->children[LEFT] = to_insert;
            to_insert->parent = root;
            if (root->height == 1)
            {
                ++root->height;
            }
        }
        else if (root->height == InsertSubTree(root->children[LEFT], to_insert, func))
        {
            ++root->height;
        }
        return root->height;
 
    }
    if(!GetChild(root,RIGHT))
        {
            root->children[RIGHT] = to_insert;
            to_insert->parent = root;
            if (root->height == 1)
            {
                ++root->height;
            }
        }
    else if (root->height == InsertSubTree(root->children[RIGHT], to_insert, func))
    {
        ++root->height;
    }
    return root->height; 
}

static size_t max(size_t num1, size_t num2)
{
    return num1 > num2 ? num1 : num2;
}

void PrintTree(avl_ty *avl)
{
    int g = 0;
    assert(avl);

    printf("in order:\n");
    ForEachIn(avl->root, printnode, (void*)&g);
    printf("post order:\n");

    ForEachPos(avl->root, printnode, (void*)&g);
}


static int printnode(void* data1, void* data2)
{
    printf("%d\n", *(int*)data1);
    return 0;
}

void Rot(avl_node_ty *root, children dir)
{
    avl_node_ty *participants[5];

    assert(root);

    participants[0] = root->parent;
    participants[1] = root->children[dir];
    participants[2] = root->children[!dir];
    participants[3] = participants[2]->children[!dir];
    participants[4] = participants[2]->children[dir];
    
    participants[2]->parent = participants[0];
    if(participants[0])
    {
        participants[0]->children[WhosYourDaddy(root)] = participants[2];
    }
    root->parent = participants[2];
    participants[2]->children[dir] = root;

    root->children[!dir] = participants[4];
    if(participants[4])
    {
        participants[4]->parent = root; 
        PropHeight(participants[4]);
        return;
    }
    PropHeight(root);
    
}

static avl_node_ty *CheckAndFixImbalance(avl_node_ty *root)
{
    int imba = 0;
    while(root != NULL)
    {
        imba = GetHeight(root->children[LEFT]) - GetHeight(root->children[RIGHT]);

        if (imba >= 2)
        {
            if(GetHeight(root->children[LEFT]->children[LEFT]) >= GetHeight(root->children[LEFT]->children[RIGHT]))
            {
                Rot(root, RIGHT);
            }
            else
            {
                Rot(root->children[LEFT], LEFT);
                Rot(root, RIGHT);
            }
            break;
        }
        else if (imba <= -2)
        {
            if(GetHeight(root->children[RIGHT]->children[RIGHT]) >= GetHeight(root->children[RIGHT]->children[LEFT]))
            {
                Rot(root, LEFT);
            }
            else
            {
                Rot(root->children[RIGHT], RIGHT);
                Rot(root, LEFT);
            }
            break;
        }
        root = root->parent;
    }
    return root;
}