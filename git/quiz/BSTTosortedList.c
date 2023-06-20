#include"bst.h"

bst_node_ty *BSTTosortedList(bst_node_ty* root)
{
    bst_node_ty *next = NULL, *prev = NULL, *ret = NULL;
    if(!root)
    {
        return NULL;
    }

    next = BSTNext(root);
    prev = BSTPrev(root);
    BSTTosortedList(root->left);
    BSTTosortedList(root->right);

    if(next)
    {
        root->left = next;
    }
    if(prev)
    {
        root->right = prev;
    }

    return root;
}