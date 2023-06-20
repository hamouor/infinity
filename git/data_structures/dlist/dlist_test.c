#include <stdio.h>          /* printf */

#include "dlist.h"

void TestErrting();
int IsMatch(void *data, void *user_data);
int UserFunction(void *data, void *parameter);

int main()
{
    void TestErrting();
    printf("is this your only print? good, yalla bye.\nno? hahahahahaha good luck\n");
    return 0;
}

void TestErrting()
{
    dlist_ty *list = NULL, *list2 = NULL, *temp = NULL;
    dlist_iter_ty iter = NULL, iter1 = NULL;
    size_t count = 0;
    int first = 1, second = 2, third = 3, for_each_success = 3;

    /* create a new list */
    list = DlistCreate();

    /* iter to start & insert first var*/
    iter = DlistBegin(list);
    iter1 = DlistInsertBefore(iter, &first);

    /* step to next & enter a new var*/
    iter1 = DlistNext(iter1);
    DlistInsertBefore(iter1, &second);

    /* iter to start & print current list  */
    iter = DlistBegin(list);
    if (1 != *(int *)DlistGetData(iter))
        printf("creation & insert are making balagan - first val\n");
    if (2 != *(int *)DlistGetData(DlistNext(iter)))
        printf("creation & insert are making balagan - second val\n");

    /* iter to end & insert 3 */
    iter = DlistEnd(list);
    iter = DlistInsertBefore(iter, &third);
    
    /* print & count */
    if (3 != *(int *)DlistGetData(iter))
        printf("creation & insert are making balagan - third val\n");
    if (3 != DlistCount(list))
        printf("count is making balagan\n");

    /* remove 3 & print */
    DlistRemove(iter);
    iter = DlistBegin(list);
    if(1 != *(int *)DlistGetData(iter) && 2 != DlistCount(list))
        printf("remove is making balagan\n");
    iter = DlistBegin(list);
    iter1 = DlistEnd(list);

    /* check if start & end are equal, then check start & start */
    if (0 != DlistIterIsEqual(iter, iter1))
        printf("not equal is making balagan\n");
    if (1 != DlistIterIsEqual(iter, iter))
        printf("equal is making balagan\n");

    /* find 2 in the list & print */
    iter = DlistFind(iter, iter1, IsMatch, (void *)&second);
    if (2 != *(int *)DlistGetData(iter))
        printf("find is making balagan\n");
    iter = DlistBegin(list);

    /* foreach *3 & print */
    for_each_success = DlistForEach(iter, iter1, UserFunction, (void *)&third);
    if (1 != for_each_success || 3 != *(int *)DlistGetData(iter) || 6 != *(int *)DlistGetData(DlistNext(iter)))
        printf("for each is making balagan\n");

    iter = DlistBegin(list);

    /* create new list with 2, 2, 3, 3 */
    list2 = DlistCreate();
    iter1 = DlistBegin(list2);
    temp = DlistCreate();

    /* push & pop tests */
    iter1 = DlistPushBack(list2, &third);
    iter1 = DlistEnd(list2);
    if (1 != DlistCount(list2) && 3 != *(int *)DlistGetData(iter1)) 
        printf("DlistPushBack is making balagan");
    iter1 = DlistPushBack(list2, &third);
    iter1 = DlistPushFront(list2, &second);
    iter1 = DlistBegin(list2);
    if (3 != DlistCount(list2) && 2 != *(int *)DlistGetData(iter1)) 
        printf("DlistPushFront is making balagan");     
    iter1 = DlistPushFront(list2, &second);
    if (2 != *(int *)DlistPopFront(list2)) 
        printf("DlistPopFront is making balagan");
    if (3 != *(int *)DlistPopBack(list2)) 
        printf("DlistPopBack is making balagan");   
    
    /* test multifind */
    if (1 != DlistMultiFind(DlistBegin(list2), DlistEnd(list2), IsMatch, (void *)&first, temp))
        printf("1multifind is making balagan");
    if (0 != DlistCount(list2))
        printf("2multifind is making balagan");        
    if (0 != DlistMultiFind(DlistBegin(list2), DlistEnd(list2), IsMatch, (void *)&third, temp))
        printf("3multifind is making balagan");  
    if (2 != DlistCount(list2))
        printf("4multifind is making balagan"); 

    /* test splice */
    count = DlistCount(list);
    iter = DlistNext(DlistBegin(list));
    if (2 != *(int *)DlistGetData(DlistSplice(DlistBegin(list2), DlistEnd(list2), iter))) 
        printf("1DlistSplice is making balagan");
    if (0 != DlistCount(list2))
        printf("2DlistSplice is making balagan");  
    if ((count + 2) != DlistCount(list))
        printf("3DlistSplice is making balagan"); 

    /* dextroy list */
    DlistDestroy(list);
    DlistDestroy(list2);

}


int IsMatch(void *data, void *user_data)
{
    if ((int *)data == (int *)user_data)
    {
        return 1;
    }
    else return 0;
}

int UserFunction(void *data, void *parameter)
{
    *(int *)data *= *(int *)parameter;
    return 1;
}