#include<stdio.h>   /*printf*/
#include<string.h> /*strcmp*/
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdlib.h>
#include<errno.h>

void SemX(sem_t* semi);
void SemV(sem_t* semi);
void SemI(sem_t* semi, char* num);
void SemD(sem_t* semi, char* num);

int sem_size = 5;
int undo = 0;

int main(int argc, char** argv)
{
    char command[20];
    sem_t *semi = NULL;
    char* token = NULL;

    if(argc < 2)
    {
        printf("must select name for semaphore\n");
        return 0;
    }
    
    semi = sem_open(argv[1], O_CREAT, O_RDWR, sem_size);
    
    if(semi == SEM_FAILED)
    {
        printf("Fail%d\n", errno);
        return 0;
    }


    while (strcmp(command, "X")) 
    {
        printf("what is your command?\n");
        gets(command);
        token = strtok(command, " ");
        
        if(strcmp(token, argv[1]))
        {
            printf("no such semaphore\n");
        }
        
        else
        {
            token = strtok(NULL, " ");
            if(!strcmp(token, "D"))
            {
                SemD(semi, strtok(NULL, " "));
            }
            else if(!strcmp(token, "I"))
            {
                SemI(semi, strtok(NULL, " "));
            }
            else if(!strcmp(token, "V"))
            {
                SemV(semi);
            }
            else if(!strcmp(token, "X"))
            {
                SemX(semi);
                break;
            }
        }
    }
   return 0;         
}

void SemD(sem_t* semi, char* str)
{
    int n = 0;
    int curr = 0;
    char* und = NULL, *num = NULL;

    sem_getvalue(semi, &curr);
    
    und = strtok(NULL, " ");

    n = atoi(str);

    if(n > curr)
    {
        n = curr;
    }

    if(und && !strcmp(und, "undo"))
    {
        undo += n;
    }

    for(; n > 0; --n)
    {
        sem_wait(semi);
    }
}

void SemI(sem_t* semi, char* str)
{
    int n = 0;
    int curr = 0;
    char* und = NULL, *num = NULL;

    sem_getvalue(semi, &curr);

    und = strtok(NULL, " ");

    n = atoi(str);

    if((curr + n) > sem_size)
    {
        n = sem_size - curr;
    }
    
    if(und && !strcmp(und, "undo"))
    {
        undo -= n;
    }
    
    for(; n > 0; --n)
    {
        sem_post(semi);
    }
}

void SemV(sem_t* semi)
{
    int n = 0;

    if(!sem_getvalue(semi, &n))
    {
        printf("%d\n", n);
    }
    else
    {
        printf("failed getting value\n");
    }
}

void SemX(sem_t* semi)
{
    char to_und[20];

    if(undo > 0)
    {
        sprintf(to_und, "%d", undo);
        SemI(semi, to_und);
        undo = 0;
    }
    else if(undo < 0)
    {
        sprintf(to_und, "%d", -undo);
        SemD(semi, to_und);
        undo = 0;
    }
}