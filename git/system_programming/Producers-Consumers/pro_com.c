#include <stdatomic.h>
#include <pthread.h>
#include <threads.h>
#include<stdatomic.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include"slist.h"
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h> 
#include"cbuffer.h"

void Ex1();
void *ThreadEx1_1(void* arg);
void *ThreadEx1_2(void* arg);
void *ThreadEx2_1(void* arg);
void *ThreadEx2_2(void* arg);
void Ex2();
void Ex3();
void *ThreadEx3_1(void* arg);
void *ThreadEx3_2(void* arg);
void* ThreadEx4_2(void* arg);
void* ThreadEx4_1(void* arg);
void Ex4();
void* ThreadEx5_2(void* arg);
void* ThreadEx5_1(void* arg);
void Ex5();
void* ThreadEx6_2(void* arg);
void* ThreadEx6_1(void* arg);
void Ex6();

sig_atomic_t turn = 0;
sig_atomic_t repeats = 10;
sig_atomic_t repeats2 = 10;

int main()
{
    /*Ex1();*/
    /*Ex2();*/
    /*Ex3();*/
    /*Ex4();*/
    /*Ex5();*/
    Ex6();

    return 0;
}

void Ex1()
{
    pthread_t id[2];
    char message[16] = {0}; 
    
    pthread_create(&id[0], NULL, ThreadEx1_1, (void*)&message);
    pthread_create(&id[1], NULL, ThreadEx1_2, (void*)&message);

    pthread_join(id[1], NULL);
    pthread_join(id[0], NULL);
}

void *ThreadEx1_1(void* arg)
{
    while(repeats-1)
    {
        if(!turn)
        {
            strcpy((char*)arg, "this is message");
            --repeats;
            turn = 1;
        }
    }
    return NULL;
}

void *ThreadEx1_2(void* arg)
{
    char recieved[16] = {0};
    
    while(repeats)
    {
        if(turn)
        {
            strcpy(recieved, (char*)arg);
            printf("%s\n", recieved);
            --repeats;
            turn = 0;
        }
    }
    return NULL;
}

pthread_mutex_t lock;

void Ex2()
{
    pthread_t id[4];
    slist_ty *list = NULL;
    repeats = 10;
    
    list = SlistCreate();
    pthread_mutex_init(&lock, NULL);

    pthread_create(&id[0], NULL, ThreadEx2_1, (void*)list);
    pthread_create(&id[1], NULL, ThreadEx2_1, (void*)list);
    pthread_create(&id[2], NULL, ThreadEx2_2, (void*)list);
    pthread_create(&id[3], NULL, ThreadEx2_2, (void*)list);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    pthread_join(id[2], NULL);
    pthread_join(id[3], NULL);

    SlistDestroy(list);
    pthread_mutex_destroy(&lock);


}

void *ThreadEx2_2(void* arg)
{
    void* out = NULL;
    
    while(repeats2 > 0)
    {   
        pthread_mutex_lock(&lock);
        while(SlistCount((slist_ty*)arg) > 0)
        {
            --repeats2; 
            out = SlistGetData(SlistBegin((slist_ty*)arg));
            SlistRemove(SlistBegin((slist_ty*)arg));
            printf("%c\n", (char*)out);
        }
        pthread_mutex_unlock(&lock);
    }
}

void *ThreadEx2_1(void* arg)
{
    char in = 'c';

    while(repeats > 0)
    {
        pthread_mutex_lock(&lock);
        --repeats;
        SlistInsertBefore(SlistEnd((slist_ty*)arg), (void*)in);
        pthread_mutex_unlock(&lock);
    }
}

sem_t *semi = NULL;

void Ex3()
{
    slist_ty *list = NULL;
    pthread_t id[4];
    
    list = SlistCreate();
    pthread_mutex_init(&lock, NULL);

    semi = sem_open("or", O_CREAT, O_RDWR, 0);

    pthread_create(&id[0], NULL, ThreadEx3_1, (void*)list);
    pthread_create(&id[1], NULL, ThreadEx3_1, (void*)list);
    pthread_create(&id[2], NULL, ThreadEx3_2, (void*)list);
    pthread_create(&id[3], NULL, ThreadEx3_2, (void*)list);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    pthread_join(id[2], NULL);
    pthread_join(id[3], NULL);

    SlistDestroy(list);
    pthread_mutex_destroy(&lock);
}

void *ThreadEx3_2(void* arg)
{
    void* out = NULL;
    
    while(1)
    {   
        sem_wait(semi);
        pthread_mutex_lock(&lock);
        out = SlistGetData(SlistBegin((slist_ty*)arg));
        SlistRemove(SlistBegin((slist_ty*)arg));
        printf("%c\n", (char*)out);
        pthread_mutex_unlock(&lock);
    }
}

void *ThreadEx3_1(void* arg)
{
    char in = 'c';

    while(1)
    {
        pthread_mutex_lock(&lock);
        SlistInsertBefore(SlistEnd((slist_ty*)arg), (void*)in);
        sem_post(semi);
        pthread_mutex_unlock(&lock);
    }
}

sem_t *semi1 = NULL;
sem_t *semi2 = NULL;

void Ex4()
{
    cbuffer_ty *cbuf = NULL;
    pthread_t id[4];
    
    cbuf = CBufCreate(800);
    pthread_mutex_init(&lock, NULL);

    semi1 = sem_open("or", O_CREAT, O_RDWR, 0);
    semi2 = sem_open("hemo", O_CREAT, O_RDWR, 1);

    pthread_create(&id[0], NULL, ThreadEx4_1, (void*)cbuf);
    pthread_create(&id[1], NULL, ThreadEx4_1, (void*)cbuf);
    pthread_create(&id[2], NULL, ThreadEx4_2, (void*)cbuf);
    pthread_create(&id[3], NULL, ThreadEx4_2, (void*)cbuf);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    pthread_join(id[2], NULL);
    pthread_join(id[3], NULL);

    CBufDestroy(cbuf);
    pthread_mutex_destroy(&lock);
}


void* ThreadEx4_1(void* arg)
{
    char in = 'c';

    while(1)
    {
        sem_wait(semi2);
        pthread_mutex_lock(&lock);
        CBufWrite((cbuffer_ty*)arg, (void*)&in, sizeof(char));
        sem_post(semi1);
        pthread_mutex_unlock(&lock);
    }
}

void* ThreadEx4_2(void* arg)
{
    char out;
    
    while(1)
    {   
        sem_wait(semi1);
        pthread_mutex_lock(&lock);
        CBufRead((cbuffer_ty*)arg, (void*)&out, sizeof(char));
        printf("%c\n", out);
        sem_post(semi2);
        pthread_mutex_unlock(&lock);
    }
}

pthread_mutex_t lock2;
pthread_mutex_t lock1;

sem_t *semiex51 = NULL;
sem_t *semiex52 = NULL;

void Ex5()
{
    cbuffer_ty *cbuf = NULL;
    pthread_t id[4];
    
    cbuf = CBufCreate(800);
    
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    semiex51 = sem_open("or", O_CREAT, O_RDWR, 0);
    semiex52 = sem_open("hemo", O_CREAT, O_RDWR, 1);
    
    sem_unlink("or");
    sem_unlink("hemo");

    pthread_create(&id[0], NULL, ThreadEx5_1, (void*)cbuf);
    pthread_create(&id[1], NULL, ThreadEx5_1, (void*)cbuf);
    pthread_create(&id[2], NULL, ThreadEx5_2, (void*)cbuf);
    pthread_create(&id[3], NULL, ThreadEx5_2, (void*)cbuf);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    pthread_join(id[2], NULL);
    pthread_join(id[3], NULL);

    CBufDestroy(cbuf);
    
    sem_close(semiex51);
    sem_close(semiex52);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
}


void* ThreadEx5_1(void* arg)
{
    char in = 'c';

    while(1)
    {
        sem_wait(semiex52);
        pthread_mutex_lock(&lock1);
        CBufWrite((cbuffer_ty*)arg, (void*)&in, sizeof(char));
        pthread_mutex_unlock(&lock1);
        sem_post(semiex51);
    }
}

void* ThreadEx5_2(void* arg)
{
    char out;
    
    while(1)
    {   
        sem_wait(semiex51);
        pthread_mutex_lock(&lock2);
        CBufRead((cbuffer_ty*)arg, (void*)&out, sizeof(char));
        printf("%c\n", out);
        pthread_mutex_unlock(&lock2);
        sem_post(semiex52);
    }
}

pthread_mutex_t lock6;
sem_t *semiex6 = NULL;
pthread_cond_t cond;

void Ex6()
{
    cbuffer_ty *cbuf = NULL;
    pthread_t id[4];
    
    cbuf = CBufCreate(800);
    
    pthread_mutex_init(&lock6, NULL);

    semiex6 = sem_open("or", O_CREAT, O_RDWR, 0);
    
    sem_unlink("or");

    pthread_create(&id[0], NULL, ThreadEx6_1, (void*)cbuf);
    pthread_create(&id[1], NULL, ThreadEx6_2, (void*)cbuf);
    pthread_create(&id[2], NULL, ThreadEx6_2, (void*)cbuf);
    pthread_create(&id[3], NULL, ThreadEx6_2, (void*)cbuf);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    pthread_join(id[2], NULL);
    pthread_join(id[3], NULL);

    CBufDestroy(cbuf);
    
    sem_close(semiex6);

    pthread_mutex_destroy(&lock6);
}


void* ThreadEx6_1(void* arg)
{
    char in = 'c';
    int i = 0;
    int val = 0;
    int num_of_cons = 3;

    while(1)
    {
        for(i = 0; i < num_of_cons; ++i)
        {
            sem_wait(semiex6);
            CBufWrite((cbuffer_ty*)arg, (void*)&in, sizeof(char));
        }
        pthread_cond_broadcast(&cond);
    }
}

void* ThreadEx6_2(void* arg)
{
    char out;
    int val = 0;

    while(1)
    {   
        sem_post(semiex6);
        pthread_mutex_lock(&lock6);
        pthread_cond_wait(&cond, &lock6);
        CBufRead((cbuffer_ty*)arg, (void*)&out, sizeof(char));
        printf("%c\n", out);
        pthread_mutex_unlock(&lock6);
    }
}
