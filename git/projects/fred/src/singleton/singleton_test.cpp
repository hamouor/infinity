#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "Singleton.hpp"

using namespace hrd24;

typedef int* (*func_ty)();

int main()
{
    int* a = Singleton<int>::GetInstance();
    int* b = Singleton<int>::GetInstance();

    if (a != b)
    {
        std::cout << "blowme" << std::endl;
    }

    void *handle;
    func_ty func;

    handle = dlopen ("./so.so", RTLD_LAZY);
    func = (func_ty)(dlsym(handle, "_Z3foov"));
 
    b = func();
    std::cout<<"kaka"<<std::endl;
    if (a != b)
    {
        std::cout << "blowme" << a << std::endl << b << std::endl;
    }
    
    dlclose(handle);

    return 0;
}

