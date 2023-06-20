#include"exercises.h"

#include <stdio.h>
#include <stdlib.h>

static int static_func()
{
    printf("\n1\n");
    return (0);
}

int extern_func()
{
    printf("\n1\n");
    return (0);
}

int nc_local;
const int const_global = 15;
int nc_global = 15;

static const int static_const_global = 15;
static int static_nc_global = 15;

int foo(int argc, char **argv, char **envp)
{
    const int const_local = 15;
    int nc_local_init = 0;
    static const int static_local = 15;
    static int nc_static_local = 15;

    char *sliteral = "literal";

    char *env = envp[2];
    
    char *clargs = argv[1];
    
    char *heap = malloc(100);
    
    extern_func();
    static_func();
    

    
    printf("\nThe address of static_func is: %p\n", &static_func);
    printf("\nThe address of extern_func is: %p\n", &extern_func);
    printf("\nThe address of const_global is: %p\n", &const_global);
    printf("\nThe address of nc_global is: %p\n", &nc_global);
    printf("\nThe address of nc_local is: %p\n", &nc_local);
    printf("\nThe address of static_local is: %p\n", &static_local);
    printf("\nThe address of nc_static_local is: %p\n", &nc_static_local);
    printf("\nThe address of static_const_global is: %p\n", &static_const_global);
    printf("\nThe address of static_nc_global is: %p\n", &static_nc_global);
    printf("\nThe address of heap is: %p\n", heap);
    printf("\nThe address of sliteral is: %p\n", sliteral);
    printf("\nThe address of env is: %p\n", env);
    printf("\nThe address of clargs is: %p\n", clargs);
    printf("\nThe address of nc_local_init is: %p\n", &nc_local_init);
    printf("\nThe address of const_local is: %p\n", &const_local);
    printf("\nThe address of print_func is: %p\n", &printf);
    
    
    
    free(heap);
    
    return (0);
}

