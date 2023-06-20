#include <stdio.h>          /* printf */
#include <stdlib.h>

#include "cbuffer.h"

void CBufPrintArr(cbuffer_ty *cbuffer);
int CBStrNCmp(cbuffer_ty *cbuffer, char *str, size_t n);

int main()
{
    cbuffer_ty *new_cbuff = NULL;
    ssize_t temp = 0;
    size_t capacity = 5, count4 = 4, count1 = 1, count5 =5;
    int i = 0;
    char input_arr[7] = "STOPF", o = 'F', output_arr[7] = {0}, after_loop[] = "FFFPF", empty[1];

    new_cbuff = CBufCreate(capacity);
    if (0 != CBufSize(new_cbuff))
        printf("1CBufSize(%lu) is making balagan\n",CBufSize(new_cbuff));
    if (5 != CBufFreeSpace(new_cbuff))
        printf("2CBufFreeSpace(%lu) is making balagan\n",CBufFreeSpace(new_cbuff));
    if (1 != CBufIsEmpty(new_cbuff))
        printf("3CBufIsEmpty(%d) is making balagan\n",CBufIsEmpty(new_cbuff));
    if ((-1) != (temp = CBufRead(new_cbuff, (void *)output_arr, count1)))
        printf("4CBufRead(%lu) is making balagan\n",temp);

    if (4 != (temp = CBufWrite(new_cbuff, (void *)input_arr, count4)))
        printf("5CBufWrite(%lu) is making balagan\n",temp);    
    if (1 != (temp = CBufWrite(new_cbuff, (void *)&o, count1)))
        printf("6CBufWrite(%lu) is making balagan\n",temp);
    if (-1 != (temp = CBufWrite(new_cbuff, (void *)&o, count1)))
        printf("7CBufWrite(%lu) is making balagan\n",temp);        
    if (0 != CBStrNCmp(new_cbuff, input_arr, CBufSize(new_cbuff))) 
        printf("strings arent equal 1"); 

    if (5 != CBufSize(new_cbuff))
        printf("8CBufSize(%lu) is making balagan\n",CBufSize(new_cbuff));
    if (0 != CBufFreeSpace(new_cbuff))
        printf("9CBufFreeSpace(%lu) is making balagan\n",CBufFreeSpace(new_cbuff));
    if (0 != CBufIsEmpty(new_cbuff))
        printf("10CBufIsEmpty(%d) is making balagan\n",CBufIsEmpty(new_cbuff));    
    
    for (i = 0; i < 3; ++i)
    {
        if (1 != (temp = CBufRead(new_cbuff, (void *)output_arr, count1)))
            printf("11CBufRead(%lu) is making balagan\n",temp);
      
        if (4 != CBufSize(new_cbuff))
            printf("12CBufSize(%lu) is making balagan\n",CBufSize(new_cbuff));
        if (1 != CBufFreeSpace(new_cbuff))
            printf("13CBufFreeSpace(%lu) is making balagan\n",CBufFreeSpace(new_cbuff));
        if (0 != CBufIsEmpty(new_cbuff))
            printf("14CBufIsEmpty(%d) is making balagan\n",CBufIsEmpty(new_cbuff));    
        
        if (1 != (temp = CBufWrite(new_cbuff, (void *)&o, count1)))
            printf("15CBufWrite(%lu) is making balagan\n",temp); 
    }   
    
    if (5 != CBufSize(new_cbuff))
        printf("8CBufSize(%lu) is making balagan\n",CBufSize(new_cbuff));
    if (0 != CBufFreeSpace(new_cbuff))
        printf("9CBufFreeSpace(%lu) is making balagan\n",CBufFreeSpace(new_cbuff));
    if (0 != CBufIsEmpty(new_cbuff))
        printf("10CBufIsEmpty(%d) is making balagan\n",CBufIsEmpty(new_cbuff));   
    if (0 != CBStrNCmp(new_cbuff, after_loop, CBufSize(new_cbuff))) 
        printf("strings arent equal 2");     

    if (5 != (temp = CBufRead(new_cbuff, (void *)output_arr, count5)))
        printf("11CBufRead(%lu) is making balagan\n",temp);
    if (0 != CBStrNCmp(new_cbuff, empty, CBufSize(new_cbuff))) 
        printf("strings arent equal 3");   

    CBufDestroy(new_cbuff);
    printf("no print? no problem.\nyes print? go fix it bitch\n");

    return 0;
}