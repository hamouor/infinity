#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


sig_atomic_t flag1 = 0, ppcount = 0;
pid_t child_pid;

void handler1 (int signum, siginfo_t *inf, void *ptr)
{
    ++flag1;
    ++ppcount;
    child_pid = inf->si_pid;
}

int main ()
{
    struct sigaction sa1;
        
    printf("%d\n", getpid());
    memset (&sa1, 0, sizeof (sa1)); 
    sa1.sa_flags |= SA_SIGINFO;
    sa1.sa_sigaction = &handler1;

    sigaction (SIGUSR2, &sa1, NULL);

    while(ppcount < 98)
    {
        pause();
        if(flag1)
        {
            sleep(2);
            kill(child_pid, SIGUSR1);
            printf("ping\n");
            flag1 = 0;
        }

    }
    return 0;
}
