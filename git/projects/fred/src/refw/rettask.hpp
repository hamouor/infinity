#ifndef __RETTASK_HPP__
#define __RETTASK_HPP__

#include "itask.hpp"
namespace hrd24
{
class RETask: public ITask
{
public:
    //Possible priorities: LOW, NORMAL, HIGH
    explicit RETask(Priority priority_ = LOW);
    virtual ~RETask() = default;

    RETask(const RETask& other_) = default;
    RETask& operator=(const RETask& other_) = default;
    RETask(RETask&& other_) = default;
    RETask& operator=(RETask&& other_) = default;

private:
    virtual void Execute() = 0;
};

RETask::RETask(Priority priority_):ITask(priority_){}
}

#endif // __RETTASK_HPP__