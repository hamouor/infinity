#include <string.h>  /* strlen  strstr  strcat  strcpy strcmp   */
#include <stdio.h>  /*printf*/

#include"stack.h"

typedef struct Node Node;
struct Node {
    int data;
    Node *next;
};

int Fibonacci(int element_index);
Node* FlipList(Node *node);
size_t StrLenR(char* str);
int StrCmpR(char *s1, char *s2);
char *StrCpyR(char *dest, char *src);
char *StrCatR(char *dest, char *src);
char *StrStrR(char *haystack, char *needle);
void StackSortInsert(stack_ty *stack, int elem);
void StackSortR(stack_ty *stack);

/*void StackOver(void);


void TestFlipList(void) {

    Node node1, node2, node3, node4, node5, *test = NULL;
    int i = 5;

    printf("TestFlipList start\n");

    node1.data = 1;
    node2.data = 2;
    node3.data = 3;
    node4.data = 4;
    node5.data = 5;

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = NULL;

    test = FlipList(&node1);

    while(test) {
        if(i != test->data) {
            printf("flipnode failed. \n");
            return;
        }
        --i;
        test = test->next;
    }
}
int po = 520000;
int main()
{
    char str[] = "this is my test12345";
    char str3[21] = "this is m";
    char str4[] = "y test12";
    char str2[21];
    stack_ty *stack;
    int i = 0, j=0;
    int arr[] = {5,3,6,9,1,4,0,11,2,8};
    size_t a[1000000];
    
    printf("my strlen:%ld\nsys strlen:%ld\n", StrLenR(str), strlen(str));
    printf("%s\n%s\n%s\n",StrCpyR(str2, str),str2,str);
    printf("strcmp:%d\n", StrCmpR(str, str2));
    printf("%s\n%s\n",StrCatR(str3, str4), str3);
    if(StrStrR(str,str4))
    {
        printf("%s\n", StrStrR(str,str4));
    }
    
    stack = StackCreate(sizeof(int), 10);

    for(; i < 10; ++i)
    {
        StackPush(stack, (void*)&arr[i]);
    }

 
    
    for(i = 0; i < 10; ++i)
    {
        printf("stack pre sorting:%d\n",*(int*)StackPeek(stack));
        StackPop(stack);
    }
    for(i = 0; i < 10; ++i)
    {
        StackPush(stack, (void*)&arr[i]);
    }
    StackSortR(stack);

    for(i = 0; i < 10; ++i)
    {
        printf("stack post sorting:%d\n",*(int*)StackPeek(stack));
        StackPop(stack);
    }

    TestFlipList();
    StackDestroy(stack);
    StackOver();
    return 0;
}
void StackOver(void)
{
    if(po > 0)
    {
        --po;
        StackOver();
    }
}*/
int Fibonacci(int element_index)
{
    if(element_index == 1)
    {
        return 0;
    }
    else if (element_index == 2)
    {
        return 1;
    }
    else
    {
        return (Fibonacci(element_index - 1) + Fibonacci(element_index - 2));
    }
}

Node* FlipList(Node *node)
{
    Node *node2;

    if(node->next == NULL)
    {
        return node;
    }

    node2 = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;
    return node2;
}

size_t StrLenR(char* str)
{
    if(*str == '\0')
    {
        return 0;
    }
    return (1 + StrLenR(str + 1));
}

int StrCmpR(char *s1, char *s2)
{
    int retval = *s1 -*s2;
    if(*s1 == '\0' || *s2 == '\0')
    {
        return retval;
    }
    if (!!retval)
    {
        return retval;
    }
    return (StrCmpR(s1 + 1, s2 + 1));
}

char *StrCpyR(char *dest, char *src)
{
    if (*src == '\0')
    {
        *dest = '\0';
    }
    else
    {
        *dest = *src;
        StrCpyR(dest + 1, src + 1);
    }
    return dest;
}

char *StrCatR(char *dest, char *src)
{
    if(*src == '\0')
    {
        *dest = *src;
    }
    else if(*dest == '\0')
    {
        *dest = *src;
        *(dest + 1) = '\0';
        StrCatR(dest + 1, src + 1);
    }
    else
    {
        StrCatR(dest + 1, src);
    }
    return dest;
}

char *StrStrR(char *haystack, char *needle)
{
    if (*needle == '\0')
    {
        return haystack;
    }
    if (*haystack == '\0')
    {
        return NULL;
    }
    if (*needle == *haystack && StrStrR(haystack + 1, needle + 1))
    {
        return haystack;
    }
    return StrStrR(haystack + 1, needle);
    
}

void StackSortR(stack_ty *stack)
{
    int temp = 0;
    if(StackIsEmpty(stack))
    {
        temp = *(int*)StackPeek(stack);
        StackPop(stack);
        StackSortR(stack);
        StackSortInsert(stack, temp);
    }
}

void StackSortInsert(stack_ty *stack, int elem)
{
    int temp = 0;

    if(!StackIsEmpty(stack) || elem > *(int*)StackPeek(stack))
    {
        StackPush(stack, (void*)&elem);
    }
    else
    {
        temp = *(int*)StackPeek(stack);
        StackPop(stack);
        StackSortInsert(stack, elem);
        StackPush(stack, (void*)&temp);
    }
}

