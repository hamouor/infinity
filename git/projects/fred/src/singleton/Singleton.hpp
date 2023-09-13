#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

/******************************************************************************/
/*  		                   Generic Singleton      		                  */
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION:  Capable of generic singleton creation for any type of class.
* make sure that all ctors of class T are private!
* make CreateInstance is a friend function of class T
* def ctor 
* AUTHOR: HRD24
* REVIEWER: -
* DATE: 29/08/2022
* VERSION: 0.1 - initial file
* VERSION: 0.2 - mentor approved
* VERSION: 0.3 - added nested singleton destroyer class
*******************************************************************************/

#include <mutex>        /*  mutex   */
#include <atomic>       /*  atomic  */

#include <iostream>

#include <sys/ipc.h>    /*  shm     */
#include <sys/shm.h>    /*  shm     */
#include <stdio.h>      /*  write   */
#include <cstring>      /*  strcpy  */

namespace hrd24
{

template<typename T>
class Singleton
{
public:
    static T* GetInstance();
    
    explicit Singleton() = delete;
    Singleton(const Singleton& other_) = delete;
    Singleton& operator=(const Singleton& other_) = delete;
    ~Singleton() = delete;

private:
    static std::atomic<T*> s_instance;
    static std::mutex s_mutex;

    class SingletonDestroyer
    {
    public:
        SingletonDestroyer(int shmid_);
        ~SingletonDestroyer();
    private:
        SingletonDestroyer(const SingletonDestroyer& other_);
        SingletonDestroyer& operator=(const SingletonDestroyer& other_);
        int m_shmid;
    };
};

template<typename T>
Singleton<T>::SingletonDestroyer::SingletonDestroyer(int shmid_): m_shmid(shmid_) {}

template<typename T>
Singleton<T>::SingletonDestroyer::~SingletonDestroyer()
{
    delete s_instance;
    shmctl(m_shmid,IPC_RMID,NULL);
}

template<typename T>
std::atomic<T*> Singleton<T>::s_instance;

template<typename T>
std::mutex Singleton<T>::s_mutex;

template<typename T>
T* Singleton<T>::GetInstance()
{
    /* Open shared memory */
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    T* mem_location = (T*) shmat(shmid, 0, 0);
    /* Initalize tmp to get/store s_instance, and a barrier */
    T* tmp = mem_location;
    std::atomic_thread_fence(std::memory_order_acquire);

    if(!tmp) 
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        tmp = s_instance.load(std::memory_order_relaxed);
    
        if(!tmp) 
        {
            tmp = new T;
            std::atomic_thread_fence(std::memory_order_release);
            s_instance.store(tmp, std::memory_order_relaxed);

            static SingletonDestroyer destroyer(shmid); //Will make sure the singleton is destroyed 
            memcpy(mem_location, s_instance, 8);   //Write the address to the shm
        }
    }

    shmdt(mem_location); 
    return tmp;
}

} 

#endif 