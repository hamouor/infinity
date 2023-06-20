#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h> 

int Forking(char* init_command);
int Sysing(char* init_command);


int main(int argc, char** argv)
{
    char command[20];
    int ret_val = 0;
    
    if(argc < 2)
    {
        printf("must select system or fork. please try again\n");
        return 0;
    }

    printf("what is your command?\n");
    gets(command);
    
    if(!strcmp(argv[1], "fork"))
    {
        ret_val = Forking(command);
    }
    
    else if(!strcmp(argv[1], "system"))
    {
        ret_val = Sysing(command);
    }

    return ret_val;
}

int Forking(char* init_command)
{
    int ret_val = 0;
    char command[20];
    pid_t child_pid;
    char s[2] = " ", *token = NULL;
    char *args[] = {NULL, NULL, NULL, NULL};
    int i = 0;
    
    strcpy(command, init_command);
    
    while(strcmp(command, "exit"))
    {
        for(i= 0 ; i < 4; ++i)
        {
            args[i] = NULL;
        }
        i = 0;
        token = strtok(command, s);
        while(token)
        {
            args[i] = token;
            token = strtok(NULL, s);
            ++i;
        }
        child_pid = fork();
        if(!child_pid)
        {
            execvp(args[0], args);
            return 0;
        }
        printf("what is your command?\n");
        gets(command);
    }

    return ret_val;
}

int Sysing(char* init_command)
{
    int ret_val = 0;
    char command[20];

    strcpy(command, init_command);
    
    while(strcmp(command, "exit"))
    {
        ret_val = system(command);
        printf("what is your command?\n");
        gets(command);
    }

    return ret_val;
}