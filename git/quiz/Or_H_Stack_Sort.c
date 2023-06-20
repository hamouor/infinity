#include"stack.h"

enum popflag{didntpush = 0, didpush=1};

stack_ty *Stack_Sort(stack_ty* stack)
{
    /*general algo: we are going to pop from stack 1, check if the top element it stack 2 is smaller or equal, 
    if it is push to stack 2, if not pop from stack 2 and push to stack 1. recheck*/
    stack_ty* stack2 = NULL;
    void* elem1 = NULL, *elem2 = NULL;
    int pushflag = didntpush;
    /*create new stack of same size*/
    stack2 = StackCreate(sizeof(int), StackCapacity(stack));
    /*while stack 1 is not empty*/
    while(!StackIsEmpty(stack))
    {
        /*pop from stack 1 (element 1) and evaluate:*/
        if(pushflag)
            {
                pushflag = didntpush;
                elem1 = StackPeek(stack);
                StackPop(stack);
            }
        
        /*if stack 2 is empty or element1 is bigger then top element in stack 2:*/
        if(StackIsEmpty(stack2) || *(int*)elem1 <= *(int*)StackPeek(stack2))
        {
            /*push to stack 2*/
            StackPush(stack, elem1);
            pushflag = didpush;
        }
        /*else: pop from stack 2 and push to stack 1 and re-evaluate*/
        else
        {
            StackPush(stack, StackPeek(stack2));
            StackPop(stack2);
        }
            /*note: if pushed from stack 1 to 2- re pop if not re evaluate*/
    }
    while(!StackIsEmpty(stack2))
    {
        StackPush(stack, StackPeek(stack2));
        StackPop(stack2);
    }
    StackDestroy(stack2);
    return stack;
    /*return stack 2*/
}