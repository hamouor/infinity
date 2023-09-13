#include "itask.hpp"

namespace hrd24
{

ITask::ITask(Priority priority_): m_priority(priority_) {}

bool ITask::operator<(const ITask& other_)
{
    // compare dereferences!!
    return (m_priority < other_.m_priority);
}

} // end of namespace hrd24