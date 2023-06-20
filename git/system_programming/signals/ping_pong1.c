#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


sig_atomic_t flag1 = 1, flag2 = 0, ppcount = 0;

void handler1 (int signal_number)
{
    ++flag1;
    ++ppcount;
}

void handler2 (int signal_number)
{
    ++flag2;
}

int main ()
{
    pid_t child_pid;

    child_pid = fork();
    
    if(!child_pid)
    {
        struct sigaction sa2;
        pid_t par_pid = getppid();
        memset (&sa2, 0, sizeof (sa2)); 

        sa2.sa_handler = &handler2;
        sigaction (SIGUSR1, &sa2, NULL);

        while(ppcount < 20)
        {
            if(flag2)
            {
                sleep(2);
                printf("pong\n");
                flag2 = 0;
                kill(par_pid, SIGUSR2);
            }
            pause();
        }
    }
    
    else
    {
        struct sigaction sa1;
        
        memset (&sa1, 0, sizeof (sa1)); 
        sa1.sa_handler = &handler1;

        sigaction (SIGUSR2, &sa1, NULL);

        while(ppcount < 20)
        {
            if(flag1)
            {
                sleep(2);
                kill(child_pid, SIGUSR1);
                printf("ping\n");
                flag1 = 0;
            }
            pause();

        }
    }
    return 0;
} 