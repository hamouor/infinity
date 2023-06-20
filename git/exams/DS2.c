#include<stdio.h>
#include<string.h>
#include <stdlib.h> /*malloc*/

#include"slist.c"
#include"slist.h"

#include"stack.c"
#include"stack.h"

typedef struct st{
    int buy;
    int sell;
    int sum;
}res;

slist_node_ty *FlipListIt(slist_node_ty* head);
slist_node_ty *FlipListRec(slist_node_ty* head);
void q1(void);


void Rev(char* org, char** dest);
void q7(void);

void q2(void);
res MaxSub(int* arr, size_t size);

void strrem(char* str1, int index, char* str2);
void Perm(char* str);
void q8(void);

int main()
{
    /*q1();*/
    q7();
    /*q2();
    q8();*/
    
    return 0;
}


/*Q1a*/
slist_node_ty *FlipListIt(slist_node_ty* head)
{
    slist_node_ty* prev = NULL, *curr = NULL, *next = NULL;

    assert(head);

    curr = head;
    next = head->next;
    
    while(next)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;

    return curr;
}

void q1(void)
{
    slist_node_ty arr[5];
    int vals[4] = {1, 2, 3, 4}, i = 0;

    for(; i < 4; ++i)
    {
        arr[i].data = (void*)&vals[i];
        arr[i].next = &arr[i+1];
    }
    arr[3].next = NULL;

    arr[4] = *FlipListIt(&arr[0]);
    for(i = 0; i < 4; ++i)
    {
        printf("%d\n", *(int*)arr[4].data);
        if(arr[4]. next)
        {
            arr[4] = *arr[4].next;
        }
    }

    arr[4] = *FlipListRec(&arr[3]);
    
        for(i = 0; i < 4; ++i)
    {
        printf("%d\n", *(int*)arr[4].data);
        if(arr[4]. next)
        {
            arr[4] = *arr[4].next;
        }
    }
}


/*Q1b*/

slist_node_ty *FlipListRec(slist_node_ty* head)
{
    slist_node_ty* ret_val = NULL;

    assert(head);

    if(!head->next)
    {
        return head;
    }

    ret_val = FlipListRec(head->next);

    if(!head->next->next)
    {
        head->next->next = head;
        head->next = NULL;
    }
    
    return ret_val;
}

/*Q7*/

void Rev(char* org, char** dest)
{
    printf("%c\n", **dest);
    if(*(org + 1) != '\0')
    {
        Rev(org + 1, dest);
    }
    **dest = *org;
    ++*dest;
    **dest = '\0';
}

void q7(void)
{
    char str1[] = "abcde";
    char str2[6];
    char *a = NULL;

    a = &str2[0];

    Rev(str1, &a);

    printf("%s\n", str2);

}


res MaxSub(int* arr, size_t size)
{
    res out, opt;
    size_t i = 0;

    out.buy = i;
    out.sell = i;
    out.sum = arr[i];
    opt.buy = i;
    opt.sell = i;
    opt.sum = arr[i];

    for(i = 1; i < size; ++i)
    {
        if(arr[i] > 0)
        {
            opt.sell = i;
            opt.sum  += arr[i];
            if(opt.sum < arr[i])
            {
                opt.buy = i;
                opt.sell = i;
                opt.sum = arr[i];
            }
        }
        else
        {
            if(opt.sum + arr[i] > 0)
            {
                opt.sell = i;
                opt.sum += arr[i];
            }
            else
            {
                opt.buy = i;
                opt.sell = i;
                opt.sum = arr[i];
            }
        }
        if(opt.sum > out.sum)
        {
            out = opt;
        }
    } 
    return out;
}

void q2(void)
{
    int inp[] = {16,-15,200};
    res a = {0,0,0};

    a = MaxSub(inp, 3);

    printf("%d\n", a.sum);
}


void Perm(char* str)
{
    int len = 0, i = 0;
    char* str2 = NULL;

    len = strlen(str);

    if(len == 1)
    {
        printf("%c\n", *str);
        return;
    }

    str2 = malloc(len);

    for(i = 0; i < len; ++i)
    {
        printf("%c", str[i]);
        strrem(str, i, str2);
        Perm(str2);
    }

    free(str2);
}

void strrem(char* str1, int index, char* str2)
{
    int len = 0;

    len = strlen(str1);

    strcpy(str2, str1);

    str2[index] = '\0';

    strcat(str2, str2 + index + 1);
}

void q8(void)
{
    char str[] = "abc";

    Perm(str);
}
/*
void StackInsert(stack_ty* st, int to_ins)
{
    int val = 0;

    val = StackPeek(st);
    StackPop(st);

    if(to_ins < val)
    {
        StackInsert(st, to_ins);
        StackPush(st, val);
    }

    else
    {
        StackPush(st, val);
        StackPush(st, to_ins);
    }
}

void StackSort(stack_ty* st)
{
    int curr = 0;
    stack_ty *aux = NULL;

    aux = StackCreate(sizeof(int), StackSize(st));

    while(!StackIsEmpty(st))
    {
        curr = StackPeek(st);
        StackPop(st);
        
        if(StackIsEmpty(aux) || curr < StackPeek(aux))
        {
            StackPush(aux, curr);
        }
        else
        {
            StackPush(st, StackPeek(aux));
            StackPush(aux);
            StackPush(st, curr);
        }
    }

    while (StackIsEmpty(aux))
    {
        StackPush(st, StackPeek(aux));
        StackPop(aux);
    }
}
*/