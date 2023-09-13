/******************************************************************************/
/*  		                   Generic Factory      		                  */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  Capable of generic factory creation for any type of class.
* IMPORTANT:    - In order to create a factory, you need to provide a create
*                 function with the following signature:
*                   std::function<std::shared_ptr<Base>(Args)>
*
* AUTHOR: HRD24
* REVIEWER: -
* DATE: 31/08/2022
*                                                                          
* VERSION HISTORY:
* v0.1 - initial file
* v0.2 - mentor approval
*******************************************************************************/

#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <unordered_map> // unordered_map
#include <functional> // function
#include <memory> // shared_ptr

#include "singleton.hpp"

namespace hrd24
{

template<typename Base, typename Key, typename Args>
class Factory
{
public:
    using creatorFunc = std::function<std::shared_ptr<Base>(Args)>;

    // Add() and Create() can throw bad_alloc exception

    // If the key already exists, this function updates the creator function
    void Add(const Key& key_, creatorFunc func_);

    // Undefined behavior - if key wasn't found
    std::shared_ptr<Base> Create(const Key& key_, Args args_);
    
    Factory(const Factory& other_) = delete;
    const Factory& operator=(const Factory& other_) = delete;

private:
    explicit Factory() = default;
    ~Factory() = default;

    friend class Singleton<Factory<Base, Key, Args>>;

    std::unordered_map<Key, creatorFunc> m_creators;
};


template<typename Base, typename Key, typename Args>
void Factory<Base, Key, Args>::Add(const Key& key_, creatorFunc func_)
{
    m_creators[key_] = func_;
}

template<typename Base, typename Key, typename Args>
std::shared_ptr<Base> Factory<Base, Key, Args>::Create(const Key& key_, Args args_)
{
    return m_creators[key_](args_);
}

} // namespace hrd24

#endif // __FACTORY_HPP__