#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


sig_atomic_t flag2 = 0;

void handler2 (int signal_number)
{
    ++flag2;
}

int main()
{
    struct sigaction sa2;
    pid_t par_pid = getppid();
    memset (&sa2, 0, sizeof (sa2)); 

    sa2.sa_handler = &handler2;
    sigaction (SIGUSR1, &sa2, NULL);

    while(flag2 < 99)
    {
        if(flag2)
        {
            sleep(2);
            printf("pong\n");
            kill(par_pid, SIGUSR2);
        }
        pause();
    }
    return 0;
}