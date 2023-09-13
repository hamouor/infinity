#ifndef __ITASK_HPP__
#define __ITASK_HPP__

/******************************************************************************/
/*  		                   ITask                		                  */
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

#include <memory> // shared_ptr

namespace hrd24
{

class ITask
{
public:
    enum Priority { 
        LOW,
        MEDIUM,
        HIGH,
        ADMIN
    };

    explicit ITask(Priority priority_ = LOW);
    virtual ~ITask() = default;

    ITask(const ITask& other_) = default;
    ITask& operator=(const ITask& other_) = default;
    bool operator<(const ITask& other_); // Don't forget to compare dereference

private:
    virtual void Execute() = 0;
    friend class ThreadPool;
    
    friend bool Compare(std::shared_ptr<ITask> lhs_, std::shared_ptr<ITask> rhs_);

    Priority m_priority;
};

} // namespace hrd24

#endif // __ITASK_HPP__
