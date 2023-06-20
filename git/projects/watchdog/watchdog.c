/*#define _POSIX_C_SOURCE 199309L*/
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <pthread.h>

#include "watchdog.h"
#include "shared_sched.h"

#define WAIT_DOG 10;
extern char** environ;

int clearenv(void);
int setenv(const char *name, const char *value, int overwrite);
void* RunComp(void*);
char* ListToStr(char** arguments);
char *  itoa ( int value, char * str, int base );
char pid_str[20];

int WatchdogEnable(char *argv[])
{
    pid_t my_pid; 
    pthread_t id;
    sem_t *semi = NULL;
    char* envi = NULL;
    struct timespec abs_timeout;
    int ret = 0, err = 0;

    sem_unlink("orr");
    /*mask sigusr 1 and 2*/
    clock_gettime(CLOCK_REALTIME, &abs_timeout);
    abs_timeout.tv_sec += WAIT_DOG;
    
    /*set semaphore of 0*/
    semi = sem_open("orr", O_CREAT, O_RDONLY, 0);
    if(SEM_FAILED == semi)
    {
        printf("failed to open semaphore\n");
        return 1;
    }

    /*set char* value for setenv with argv, mypid, my adress*/
    envi = ListToStr(argv);
    
    /*setenv with my adress, my pid, argv*/

    /*XXX check args. if NULL -set*/
    if(!getenv("papa"))
    {
        setenv("args", envi, 1);
        free(envi);
        my_pid = getpid();
        sprintf(pid_str, "%d" ,my_pid);
        if(setenv("papa", pid_str, 1))
        {
            return 1;
        }
        /*printf("papa: env:%s, pidstr:%s, pid:%d\n", getenv("papa"), pid_str, my_pid);*/
        if(setenv("id", "papa",1))
        {
            return 1;
        }
    }
    /*open new thread that will call SSRun*/
    ret = pthread_create(&id, NULL, RunComp, NULL);
    if(ret)
    {
        return 1;
    }
    /*semaphore timed wait for two posts*/
    ret = sem_timedwait(semi, &abs_timeout);
    if(ret)
    {
        printf("first wait didnt work\n");
        return 1;
    }
    clock_gettime(CLOCK_REALTIME, &abs_timeout);
    abs_timeout.tv_sec += WAIT_DOG;
    ret = sem_timedwait(semi, &abs_timeout);
    if(ret)
    {   
        printf("second wait didnt work\n");
        fflush(stdout);
        return 1;
    }

    printf("finished both timedwait\n");

    return 0;
    /*return*/
    
}


int WatchdogDisable(void)
{

    kill(atoi(getenv("pooch")),SIGUSR1);
    raise(SIGUSR1);

    return 0;
}

void* RunComp(void* a)
{
    if(SSRun())
    {
        return NULL;
    }
}

char* ListToStr(char** arguments)
{
    char* out = NULL, *runner = NULL;
    int i = 0;
    size_t len = 0, total_len = 0;

    while(arguments[i])
    {
        total_len += strlen(arguments[i]) + 1;
        ++i;
    }
    
    out = malloc(total_len + 1);
    i = 0;
    runner = out;

    while(arguments[i])
    {
        memcpy(runner, arguments[i], strlen(arguments[i]) + 1);
        runner += strlen(arguments[i]) + 1;
        ++i;
    }

    return out;
}
