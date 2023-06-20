#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>
#include <time.h>

int kill_flag = 0;
int sig_counter = 0;

void handler1 (int signal_number);
void handler2 (int signal_number);

int main()
{
    struct sigaction sa1, sa2;

    memset (&sa2, 0, sizeof (sa2));
    sa2.sa_handler = &handler2;
    if(sigaction (SIGUSR2, &sa2, NULL))
    {
        return 1;
    }

    memset (&sa1, 0, sizeof (sa1));
    sa1.sa_handler = &handler1;
    if(sigaction (SIGUSR1, &sa1, NULL))
    {
        return 1;
    }

    printf("killflag = %d, counter = %d\n", kill_flag, sig_counter);
    raise(SIGUSR1);
    raise(SIGUSR2);
    printf("killflag = %d, counter = %d\n", kill_flag, sig_counter);
    return 0;
    
    
}

void handler1 (int signal_number)
{
    __sync_fetch_and_add(&kill_flag, 1);
}
void handler2 (int signal_number)
{
    __sync_fetch_and_add(&sig_counter, -1);

}