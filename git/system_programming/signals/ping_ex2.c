#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


sig_atomic_t flag1 = 1, ppcount = 0;

void handler1 (int signal_number)
{
    ++flag1;
    ++ppcount;
}

int main ()
{
    pid_t child_pid;

    child_pid = fork();
    
    if(!child_pid)
    {
        execvp("./pong", NULL);
    }
    
    else
    {
        struct sigaction sa1;
        
        printf("%d\n", child_pid);
        memset (&sa1, 0, sizeof (sa1)); 
        sa1.sa_handler = &handler1;

        sigaction (SIGUSR2, &sa1, NULL);

        while(ppcount < 98)
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