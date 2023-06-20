#include <stdlib.h>
#include <stdio.h>

#include"vsa.h"

 int main()
 {
    void* test_mem = NULL, *test_mem2 = NULL, *test_mem3 = NULL, *test_mem4 = NULL;
    vsa_ty* test_vsa = NULL;
    int a =6;

    test_mem = malloc(100);
    test_vsa = VSAInit(test_mem, 100);

    test_mem2 = VSAAlloc(test_vsa, 50);
    printf("should be 34 : %ld\n", VSALargestAvailable(test_mem));
    test_mem3 = VSAAlloc(test_vsa, 34);
    printf("should be 0 : %ld\n", VSALargestAvailable(test_mem));
    VSAFree(test_mem2);
    VSAFree(test_mem3);
    printf("should be 92 : %ld\n", VSALargestAvailable(test_mem));
    test_mem2 = VSAAlloc(test_vsa, 26);
    test_mem3 = VSAAlloc(test_vsa, 25);
    test_mem4 = VSAAlloc(test_vsa, 23);
    VSAFree(test_mem2);
    VSAFree(test_mem4);
    VSAFree(test_mem3);
    printf("should be 92 : %ld\n", VSALargestAvailable(test_mem));






    free(test_mem);
    return 0;
 }