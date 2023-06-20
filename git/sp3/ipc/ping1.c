#include <sys/ipc.h>
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <sys/types.h>
#include <fcntl.h>
#include <cstddef>
#include <cstdio>

int main()
{
    sem_t* sem1 = NULL, *sem2 = NULL;
    int count = 0;
    sem_unlink("ping");
    sem_unlink("pong");

    sem1 = sem_open("ping", O_CREAT, 0644, 1);
    sem2 = sem_open("pong", O_CREAT, 0644, 0);

    while(count < 10)
    {
        sem_wait(sem2);
        printf("ping/n");
        sem_post(sem1);
        ++count;
    }

}