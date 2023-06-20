#include"stack.h"

void *Enqueue(stack_ty* stack, void* value)
{
    StackPush(stack, value);
}

void *Deququ(stack_ty* stack, size_t element_size)
{
    stack_ty* temp StackCreate(StackSize(stack), element_size);
    void* ret = NULL;
    while(!StackIsEmpty(stack))
    {
        StackPush(temp,StackPeek(stack));
        StackPop(stack);
    }
    ret = StackPeek(temp);
    StackPop(temp);
    while(!StackIsEmpty(temp))
    {
        StackPush(stack,StackPeek(temp));
        StackPop(temp);
    }
    StackDestory(temp);
    return ret;
}