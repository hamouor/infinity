#include<stdio.h>
#include <stdlib.h>

#include"fsa.h"

int main()
{
    size_t suggres = 0;
    fsa_ty* test_fsa = NULL;
    void* ptr = NULL, *ptr2 = NULL, *ptr3 = NULL, *ptr4 = NULL;


    suggres = FSASuggestSize(4,4);
    printf("%ld\n", suggres);

    test_fsa = malloc(suggres);
    test_fsa = FSAInit((void*)test_fsa, 72, 4);

    suggres = FSACountFree(test_fsa);
    printf("%ld\n", suggres);

    ptr = FSAAlloc(test_fsa);
    ptr2 = FSAAlloc(test_fsa);

    suggres = FSACountFree(test_fsa);
    printf("%ld\n", suggres);

    ptr3 = FSAAlloc(test_fsa);
    ptr4 = FSAAlloc(test_fsa);

    suggres = FSACountFree(test_fsa);
    printf("%ld\n", suggres);

    FSAFree(test_fsa, ptr2);

    suggres = FSACountFree(test_fsa);
    printf("%ld\n", suggres);

    free(test_fsa);
    return 0;
}