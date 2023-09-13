#include <iostream>
#include <thread>
#include <vector>
#include "singleton.hpp"

using namespace hrd24;

class Adam
{
public:
    void Eat() { }
    void Sleep() { totalHealth += 10; }
    void Print() { }
    int GetHealth() { return totalHealth; }

private:
    
    friend Adam* Singleton<Adam>::GetInstance();

    int totalHealth = 50; 
};


void FeedMe()
{
    Adam *adam = Singleton<Adam>::GetInstance();
    adam->Eat();
    adam->Sleep();
    adam->Print();
}


int main()
{
    std::vector<std::thread> ThreadVector;
    std::cout << "Enter multi fred" << std::endl;
    
    for(int i = 0; i < 100; ++i)
    {
        try
        {
            std::thread fred = std::thread([](){ FeedMe(); });
            ThreadVector.push_back(std::move(fred));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }   

    
    for(auto& fred : ThreadVector)
    {
        fred.join();
    }

    Adam *adam = Singleton<Adam>::GetInstance();
    if(adam->GetHealth() != 1050)
    {
        std::cout << "Somthing's wrong i can feel it" << std::endl;
        std::cout << adam->GetHealth() << " is not 1050" << std::endl;
    }
    else
    {
        std::cout << "Success(?)" << std::endl;
    }


    return 0;
}