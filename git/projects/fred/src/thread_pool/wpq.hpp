/*****************************************************************************/
/*  		                PRIORITY QUEUE WRAPPER     		                 */
/*****************************************************************************/
/******************************************************************************
* DESCRIPTION:  Make std::p_q thread safe.
* AUTHOR: Or Hamou
* REVIEWER: 
* DATE: 01/09/2022
*
* VERSION HISTORY:
* v0.1 - initial file
* v0.2 - mentor approval
******************************************************************************/

#ifndef __PQW_HPP__
#define __PQW_HPP__

#include <queue> // priority_queue
#include <cstddef> // size_t
#include <condition_variable> // condition_variable
#include <mutex> // mutex
#include <atomic> // atomic

namespace hrd24
{

template<typename T, 
        typename Container = std::vector<T>, 
        typename Compare = std::less<typename Container::value_type> >
	
class WPriorityQueue
{
public:

    explicit WPriorityQueue(const Compare& compare_ = Compare());
    ~WPriorityQueue() = default;

    WPriorityQueue(const WPriorityQueue& other_) = delete;
    WPriorityQueue& operator=(const WPriorityQueue& other_) = delete;

    // this function returns false if timeout
    bool Pop(T& ret_, std::chrono::milliseconds timeout_);

    // this function is blocking forever
    void Pop(T& ret_);

    void Push(const T& data_);
    size_t Size() const;
    bool IsEmpty() const;

private:
    std::priority_queue<T, Container, Compare> m_pq;
    mutable std::condition_variable m_cvr;
    mutable std::mutex m_mutex;
};

// ^^^^^^^^^^^^^^^^^^^^^^^^^^ END OF HEADER ^^^^^^^^^^^^^^^^^^^^^^^^^^

template<typename T, typename Container, typename Compare>
WPriorityQueue<T, Container, Compare>::WPriorityQueue(const Compare& compare_): m_pq(compare_) {}

template<typename T, typename Container, typename Compare>
bool WPriorityQueue<T, Container, Compare>::Pop(T& ret_, std::chrono::milliseconds timeout_)
{
    bool retVal = true;

    std::unique_lock<std::mutex> ul(m_mutex);

    if (retVal = (m_cvr.wait_for(ul, timeout_, [this]{ return !m_pq.empty(); })) )
    {
        ret_ = m_pq.top();
        m_pq.pop();
    }

    return retVal;
}

template<typename T, typename Container, typename Compare>
void WPriorityQueue<T, Container, Compare>::Pop(T& ret_)
{
    std::unique_lock<std::mutex> ul(m_mutex);
    m_cvr.wait(ul, [this]{ return !m_pq.empty(); });

    // critical section
    ret_ = m_pq.top();
    m_pq.pop();
}

template<typename T, typename Container, typename Compare>
void WPriorityQueue<T, Container, Compare>::Push(const T& data_)
{
    std::unique_lock<std::mutex> ul(m_mutex);
    
    m_pq.push(data_);
    m_cvr.notify_one();
}

template<typename T, typename Container, typename Compare>
size_t WPriorityQueue<T, Container, Compare>::Size() const
{
    std::unique_lock<std::mutex> ul(m_mutex);

    return m_pq.size();
}

template<typename T, typename Container, typename Compare>
bool WPriorityQueue<T, Container, Compare>::IsEmpty() const
{
    std::unique_lock<std::mutex> ul(m_mutex);

    return m_pq.empty();
}

} // namespace hrd24

#endif // __WPQ_HPP__