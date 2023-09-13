#include"Singleton.hpp"
#include <iostream>
using namespace hrd24;

int* foo()
{
    std::cout<<"kaki"<<std::endl;
    int* a = Singleton<int>::GetInstance();
    return a;
}