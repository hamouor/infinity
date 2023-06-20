#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>
#include <time.h>

#include "scheduler_pq.h"
#include "shared_sched.h"
#include "scheduler_pq.h"
#include "uid.h"

#define INTERVAL1 0
#define INTERVAL2 0
#define GRACE 5

int sig_counter = GRACE;
char kill_flag = 0, just_revived = 0;
static scheduler_ty *sched = NULL;
static pid_t companion_pid;
char* exec_path = NULL;
char** arguments = NULL;
extern char** environ;
sem_t *semi = NULL;
struct timespec interval0;
char me[5];
char* arguments_pooch[1] = {NULL};
char sudo[5] = "sudo";

int setenv(const char *name, const char *value, int overwrite);
char *getenv(const char *name);
char* strdup(const char* s);
void handler1 (int signal_number);
void handler2 (int signal_number);
int WasSigRec(void* a);
int SendSig(void* a);
int revive(char* exec_path, char** arguments);
char** StrToL(char* str);
int Sema(void* a);



int SSRun(void)
{
    struct sigaction sa1, sa2;
    pid_t my_pid; 
    char* pid_str = NULL;
    struct timespec interval1, interval2;

    interval0.tv_sec = 0;
    interval0.tv_nsec = 2000;

    interval1.tv_sec = INTERVAL1;
    interval1.tv_nsec = 1000000000;

    interval2.tv_sec = INTERVAL2;
    interval2.tv_nsec = 2000000000;
    /*chack*/
 
    strcpy(me, getenv("id"));
    
    sched = SchedulerCreate();
    if(!sched)
    {
        return 1;
    }
    if(!strcmp(me , "papa"))
    {

        exec_path = "./updog";
        arguments = arguments_pooch;
        if(!getenv("pooch"))
        {
            printf("making first dog\n");
            if(revive(exec_path, arguments))
            {
                return 1;
            }
        }
        else
        {
            companion_pid =  atoi(getenv("pooch"));
        }
    }
    else
    {
        arguments = StrToL(getenv("args"));
        if(!arguments)
        {
            return 1;
        }
        exec_path = arguments[0];
        companion_pid = atoi(getenv("papa"));
    }

    memset (&sa2, 0, sizeof (sa2));
    sa2.sa_handler = &handler2;
    sa2.sa_flags = 0;
    if(sigaction (SIGUSR2, &sa2, NULL))
    {
        return 1;
    }

    memset (&sa1, 0, sizeof (sa1));
    sa1.sa_handler = &handler1;
    sa1.sa_flags = 0;
    if(sigaction (SIGUSR1, &sa1, NULL))
    {
        return 1;
    }
    
    semi = sem_open("orr", O_CREAT, O_RDWR, 0);
    if(SEM_FAILED == semi)
    {
        printf("failed to open semaphore\n");
        return 1;
    }

    
    /*open scheduler and add task/s -(( send sigusr2))*/

    if(UIDIsBadUid(SchedulerAdd(sched, SendSig, NULL, interval1)))
    {
        return 1;
    }
    if(UIDIsBadUid(SchedulerAdd(sched, WasSigRec, NULL, interval2)))
    {
        return 1;
    }
    if(UIDIsBadUid(SchedulerAdd(sched, Sema, NULL, interval0)))
    {
        return 1;
    }
    
    printf("ready to run %s with size:%ld\n", me, SchedulerSize(sched));
    /*run scheduler*/
    SchedulerRun(sched);
    printf("done running\n");
    SchedulerDestroy(sched);
    
    return 0;
}


void handler1 (int signal_number)
{
    __sync_fetch_and_add(&kill_flag, 1);
}
void handler2 (int signal_number)
{
    __sync_fetch_and_add(&sig_counter, 1);
    just_revived = 0;
}

int WasSigRec(void* a)
{
    /*checks signal counter value and kill flag*/
    /*printf("listen companion pid:%d, my pid:%d\n", companion_pid, getpid());*/
    if(kill_flag)
    {
        return -1;
    }
    --sig_counter;
    if(sig_counter < 1 && !just_revived)
    {
        if(revive(exec_path, arguments))
        {
            printf("revival failed\n");
            return -1;
        }
        
        sig_counter = GRACE;
        just_revived = 1;
        
        /*if(UIDIsBadUid(SchedulerAdd(sched, Sema, NULL, interval0)))
        {
            return -1;
        }*/
        sem_post(semi);
    }
    else if(sig_counter > GRACE)
    {
        sig_counter = GRACE;
    }
    /*if val indicates signal recieved- add SendSig to scheduler and zero down the sigusr2 counter*/
    return 1;
}

int SendSig(void* a)
{
    /*send sigusr2 to companion*/
    /*printf("sending from %s\n", me);*/

    if(kill(companion_pid, SIGUSR2))
    {
        printf("sending failed");
    }

    return 1;
}

/*fork and run update companion pid*/


int revive(char* exec_path, char** arguments)
{
    pid_t child_pid, my_pid;
    char pid_str[20];
    int i = 0;

    printf("revive at %s to path %s\n", me, exec_path);
    my_pid = getpid();
    sprintf(pid_str, "%d" ,my_pid);

    if(!strcmp(me , "papa"))
    {
        setenv("papa", pid_str, 1);
        setenv("id", "pooch", 1);
    }
    else
    {
        setenv("pooch", pid_str, 1);
        setenv("id", "papa", 1);
    }
    
    if(getenv("pooch"))
    {
        kill(companion_pid, SIGKILL);
        printf("kill preformed to %d\n", companion_pid);
    }

    child_pid = fork();
    
    if(!child_pid)
    {   
        if(execvp(exec_path, arguments))
        {
            printf("execution failed\n");
            return 1;
        }
    }
    
    else
    {
        companion_pid = child_pid;
    }
    
    return 0;
}

char** StrToL(char* str)
{
    char** ret_val;
    char* token = NULL;
    int i = 0;

    token = str;

    while( *token ) 
    {
        token += strlen(token) + 1;
        ++i;
    }

    ret_val = malloc(i * sizeof(char*));
    
    token = str;
    i = 0;

    while( *token ) 
    {
        ret_val[i] = strdup(token);
        token += strlen(token) + 1;
        ++i;
    }
    ret_val[i] = NULL;
    
    return ret_val;
}
/*create task sem_post*/

int Sema(void* a)
{
    printf("posting semi at %s\n", me);
    sem_post(semi);
    return 0;
}