#define _POSIX_C_SOURCE  199309L

#include <pthread.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <omp.h>

#define alot 100000
#define ATW 1000

int arr[ATW] = {0};
long int monster = 1234567890;

typedef struct rang
{
    long int from;
    long int to;
    long int res;
}range;

void *Thread(void* i);

long int Loop(long int num);


int main()
{
    pthread_t id[ATW];
    int i = 0;
    range t[ATW];
    long int res = 0;
    time_t diff = 0;
    time_t start = time(0);

    for(; i < ATW - 1; ++i)
    {   
        t[i].from = (monster / ATW) * i;
        t[i].to = (monster / ATW) * (i + 1);
        pthread_create(&id[i], NULL, Thread, (void*)&t[i]);
    }

    t[i].from = (monster / ATW) * i;
    t[i].to = monster;
    pthread_create(&id[i], NULL, Thread, (void*)&t[i]);

    for(i = 0; i < ATW; ++i)
    {
        pthread_join(id[i], NULL);
        res += t[i].res;
    }
    diff = time(0) - start;

    printf("%ld\n", diff);

    start = time(0);

    Loop(monster);

    diff = time(0) - start;

    printf("%ld\n", diff);
    
    return 0;
}

void *Thread(void* i)
{
    long int k = 0;
    long int sum_of = 0;
    range t = *(range*)i;

    k = t.from + 1;

    for(; k <= t.to; ++k)
    {
        if(!(monster % k))
        {
            sum_of += k;
        } 
    }
    ((range*)i)->res =sum_of;

}

long int Loop(long int num)
{
    long int k = 1;
    long int sum_of = 0;

#pragma omp parallel for 
    for(k = 1; k <= num; ++k)
    {
        if(!(num % k))
        {
            sum_of += k;
        } 
    }
    return sum_of;
}