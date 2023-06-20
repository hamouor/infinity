#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include"exercises.h"

int main(int argc, char **argv, char **envp)
{
    void* f = NULL, *g = NULL;
    int (*b)(int, char**, char**);
    int a = 3;

    printf("\nstack %p\n", &a);

    g = malloc(4);

    printf("\nheap %p\n", g);

    free(g);

    foo(argc, argv, envp);

    f = dlopen("./libexercises.so", RTLD_LAZY);

    b = (int (*)(int,  char **, char **))dlsym(f, "foo");

    b(argc, argv, envp);

    dlclose(f);

    return 0;
}