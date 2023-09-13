#include <functional> // std::function
#include <exception>  // exception
#include <iostream>

#include "thread_pool.hpp"

namespace hrd24
{

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^ EXCEPTIONS CLASSES ^^^^^^^^^^^^^^^^^^^^^^^^^^

// const std::exception& pause

class PauseException : public std::exception
{
public:
    PauseException(): justForFun(1) {}

    int justForFun;
};

// const std::exception& stop

class StopException : public std::exception
{
public:
    StopException(): justForFun2(5) {}

    int justForFun2;
};

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^ PAUSE & STOP TASKS ^^^^^^^^^^^^^^^^^^^^^^^^^^

class PauseTask : public ITask
{
public:
    PauseTask(): ITask(ADMIN) {}

    void Execute() 
    {
        PauseException e;
        throw e;
    }
};

class StopTask : public ITask
{
public:
    StopTask(): ITask(ADMIN) {}

    void Execute() 
    {
        StopException a;
        throw a;
    }
};

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

bool Compare(std::shared_ptr<ITask> lhs_, std::shared_ptr<ITask> rhs_);

ThreadPool::ThreadPool(size_t size_)
{
    // create a pool of threads without assigning a function to do
    for(size_t i = 0; i < size_; ++i)
    {
        m_threads.push_back(std::thread([this]() { ThreadFunc() ;}) );
    }
}

void ThreadPool::ThreadFunc()
{
    std::shared_ptr<ITask> task;

    while(true)
    {
        try
        {
            m_tasks.Pop(task);
            task->Execute();
        }
        catch(const StopException& e)
        {
            std::cout << "hi i am stop" << std::endl;
            break;
        }
        catch(const PauseException& e)
        {
            std::cout << "hi i am pause" << std::endl;
            std::unique_lock<std::mutex> ul(m_mutex);
            m_cvr.wait(ul);
        }
    }
}

ThreadPool::~ThreadPool() 
{
    Stop();

    for(auto& thread : m_threads)
    {
        thread.join();
    }
}

void ThreadPool::AddTask(std::shared_ptr<ITask> newTask_)
{
    m_tasks.Push(newTask_);
}

bool Compare(std::shared_ptr<ITask> lhs_, std::shared_ptr<ITask> rhs_)
{
    return (lhs_->m_priority < rhs_->m_priority);
}

void ThreadPool::Pause()
{
    std::shared_ptr<PauseTask> pause = std::make_shared<PauseTask>();

    for(auto& thread : m_threads)
    {
        AddTask(pause);
    }
}

void ThreadPool::Stop()
{
    std::shared_ptr<StopTask> stop = std::make_shared<StopTask>();

    for(auto& thread : m_threads)
    {
        AddTask(stop);
    }
}

void ThreadPool::Resume()
{
    m_cvr.notify_all();
}


} // end of namespace hrd24