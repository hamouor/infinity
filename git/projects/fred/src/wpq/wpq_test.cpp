#include <functional>
#include <iostream>
#include <thread>
#include <atomic>

#include "wpq.hpp"

using namespace hrd24;

using f_t = std::function<void()>;

static std::atomic<int> i;

void Print()
{
    ++i;
}

class Task
{  
public:
    Task(f_t func_ = Print, int important_ = 1): m_func(func_), m_importantness(important_) {}
    friend bool operator< (const Task& lhs_, const Task& rhs_);
    void operator()() { m_func(); }
    //inline bool operator> (const X& lhs, const X& rhs) { return rhs < lhs; }

private:
    f_t m_func;
    int m_importantness;    
};

inline bool operator< (const Task& lhs_, const Task& rhs_)
{
    if(lhs_.m_importantness < rhs_.m_importantness)
    {
        return true;
    }
    return false;
}

void forever(WPriorityQueue<Task>* pq)
{
    Task ret;
    pq->Pop(ret);
    ret();
}
void timeout(WPriorityQueue<Task>* pq)
{
    Task ret;
    bool retval = pq->Pop(ret, std::chrono::milliseconds(2000));
    if(retval != false)
    {
        std::cout << "Returned true? expected timeout. Did you pop?\n";
    }
}


int main()
{
    WPriorityQueue<Task> *pq = new WPriorityQueue<Task>;
    f_t func = Print;
    std::vector<std::thread> ThreadVector;

    Task t1, t2;

    pq->Push(t1);
    
    for(int i = 0; i < 100; ++i)
    {
        try
        {
            std::thread fred(forever, pq);
            ThreadVector.push_back(std::move(fred));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }  

    for(int i  = 0; i < 99; ++i)
    {
        pq->Push(t1);
    }

    for(auto& fred : ThreadVector)
    {
        fred.join();
    }

    std::thread fred2(timeout, pq);
    fred2.join();

    if(i != 100)
    {
        std::cout << "Didn't call the fun 100 times? got " << i << std::endl;
    }
    std::cout << "Testing passed! You didn't deadlock!\n";

    return 0;
}