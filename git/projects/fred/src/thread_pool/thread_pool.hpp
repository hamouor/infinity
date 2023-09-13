#ifndef __THEARD_POOL_HPP__
#define __THEARD_POOL_HPP__

/******************************************************************************/
/*  		                   Theard Pool            		                  */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  
* IMPORTANT:    
*
* AUTHOR: Or Hamou
* REVIEWER: 
* DATE: 01/09/2022
*
* VERSION HISTORY:
* v0.1 - initial file
*******************************************************************************/
#include <thread> // std::thread
#include <memory> // shared_ptr
#include <chrono> // force stop
#include <vector> // vector
#include <functional> // function

#include "itask.hpp"
#include "wpq.hpp"

namespace hrd24
{

// using CompFunc = std::function<bool(std::shared_ptr<ITask>, std::shared_ptr<ITask>)>;

class ThreadPool
{
public:
    explicit ThreadPool(size_t size_ = (std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 1));
    ~ThreadPool();

    void AddTask(std::shared_ptr<ITask> newTask_);

    // This function safetly stops the threadpool. Can't be resumed
    void Stop();

    // This function abruptly stops the threadpool. Can't be resumed
    void ForceStop(std::chrono::milliseconds timeout_);

    // These functions pauses/resumes the threadpool
    void Pause();
    void Resume();

    // This function changes the number of threads in the threadpool
    void SetSize(size_t newSize_);

    ThreadPool(const ThreadPool& other_) = delete;
    ThreadPool& operator=(const ThreadPool& other_) = delete;
    
private:
    WPriorityQueue< std::shared_ptr<ITask> > m_tasks;
    std::vector<std::thread> m_threads;
    std::condition_variable m_cvr;
    std::mutex m_mutex;

    void ThreadFunc();
};

} // namespace hrd24

#endif // __THEARD_POOL_HPP__