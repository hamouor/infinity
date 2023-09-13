#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

/******************************************************************************/
/*  		                   Generic Singleton      		                  */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  Capable of generic singleton creation for any type of class.
* IMPORTANT:    Make sure that all ctors of class T are private!
*               Make CreateInstance is a friend function of class T!
* def ctor 
* AUTHOR: HRD24
* REVIEWER: -
* DATE: 29/08/2022
* VERSION: 0.1 - initial file
* VERSION: 0.2 - mentor approved
* VERSION: 0.3 - added nested singleton destroyer class
* VERSION: 0.3.1 - added some semicolons where lacked
* VERSION: 0.3.2 - added mutex inclusion
* VERSION: 0.3.3 - Removed return value from SingletonDestroyer cctor
* VERSION: 0.3.4 - SingletonDestsroyer cctor and copy constructor moved to public and deleted for consistency
*******************************************************************************/
#include <mutex>
#include <atomic>

namespace hrd24
{

template<typename T>
class Singleton
{
public:
    static T* GetInstance();
    
    explicit Singleton() = delete;
    Singleton(const Singleton& other_) = delete;
    const Singleton& operator=(const Singleton& other_) = delete;
    ~Singleton() = delete;

private:
    static std::atomic<T*> s_instance;
    static std::mutex s_mutex;

    class SingletonDestroyer
    {
    public:
        explicit SingletonDestroyer(T* toDelete_);
        ~SingletonDestroyer();

        SingletonDestroyer(const SingletonDestroyer& other_) = delete;
        SingletonDestroyer& operator=(const SingletonDestroyer& other_) = delete;

    private:
        T* m_toDelete;
    };
};

template<typename T>
std::atomic<T*> Singleton<T>::s_instance;

template<typename T>
std::mutex Singleton<T>:: s_mutex;

template<typename T>
T* Singleton<T>::GetInstance()
{
    T* tmp = Singleton<T>::s_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (tmp == nullptr) 
    {
        std::lock_guard<std::mutex> lock(Singleton<T>::s_mutex);
        tmp = Singleton<T>::s_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) 
        {
            tmp = new T;
            std::atomic_thread_fence(std::memory_order_release);
            Singleton<T>::s_instance.store(tmp, std::memory_order_relaxed);
            static SingletonDestroyer Dtor(s_instance);
        }
    
    }
    return tmp;
}

template<typename T>
Singleton<T>::SingletonDestroyer::SingletonDestroyer(T* toDelete_):m_toDelete(toDelete_)
{}

template<typename T>
Singleton<T>::SingletonDestroyer::~SingletonDestroyer()
{
    delete m_toDelete;
}

} // namespace hrd24

#endif // __SINGLETON_HPP__