#ifndef __REQUEST_ENGINE_HPP__
#define __REQUEST_ENGINE_HPP__

/******************************************************************************/
/*  		                  Request Engine                       		      */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  API to configure the request engine and operate it
                
* IMPORTANT:    
*
* AUTHOR: HRD24
* REVIEWER: -
* DATE: 12/09/2022
*
* VERSION HISTORY:
* v0.1 - initial file
* v0.2 - mentor approval
*******************************************************************************/
#include <thread>               //thread
#include <utility>              // pair
#include <unordered_map>

// #include "dll_loader.hpp"
// #include "event_channel.hpp"
#include "factory.hpp"
#include "itask.hpp"
#include "singleton.hpp"
#include "thread_pool.hpp"
#include "iinputgw.hpp"
#include "rettask.hpp"

namespace hrd24
{

template<typename Key, typename Args>
class RequestEngineFW final
{

public:
    explicit RequestEngineFW(const std::string& pnpPath_, size_t threadNum_ = std::thread::hardware_concurrency());
    ~RequestEngineFW() = default;

    RequestEngineFW(const RequestEngineFW& other_) = delete;
    RequestEngineFW& operator=(const RequestEngineFW& other_) = delete;
    RequestEngineFW(const RequestEngineFW&& other_) = delete;
    RequestEngineFW& operator=(const RequestEngineFW&& other_) = delete;

    using createFunc = std::function<std::shared_ptr<RETask>(Args)>;

    void ConfigTask(const Key& key_, createFunc func_);
    void ConfigInput(std::shared_ptr<IInputGW<Key,Args>> input_);
    void Run(); //calls Read func
    void Stop();

private:
    std::unordered_map<int, std::shared_ptr<IInputGW<Key, Args>>> m_inputs;
    Factory<ITask, Key, Args>* m_fact;
    ThreadPool m_tp;
    //add all internals
};

template<typename Key, typename Args>
RequestEngineFW<Key,Args>::RequestEngineFW(const std::string& pnpPath_, size_t threadNum_):m_tp(threadNum_)
{
    
    m_fact = Singleton<Factory<ITask, Key, Args>>::GetInstance();
}

template<typename Key, typename Args>
void RequestEngineFW<Key,Args>::ConfigTask(const Key& key_, createFunc func_)
{
    m_fact.Add(key_, func_);
}

template<typename Key, typename Args>
void RequestEngineFW<Key,Args>::ConfigInput(std::shared_ptr<IInputGW<Key, Args>> input_)
{
    m_inputs.insert(input_.GetFD(), input_);
}

template<typename Key, typename Args>
void RequestEngineFW<Key,Args>::Run()
{
    
}


template<typename Key, typename Args>
void RequestEngineFW<Key,Args>::Stop()
{
    
}

} // namespace hrd24

#endif // __REQUEST_ENGINE_HPP__
