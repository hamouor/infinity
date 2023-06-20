#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    char data[] = "pong";
    char fifoPath[] = "myfif";
    int fd = 0, counter = 0;
    char buffer[5];

    while(counter < 5)
    {
        fd = open(fifoPath, O_RDONLY);
        read(fd, buffer, strlen(data) + 1);
        close(fd);
        printf("%s\n", buffer);
        
        fd = open(fifoPath, O_WRONLY);
        write(fd, data, strlen(data) + 1);
        close(fd);


        /*
        fifoR = fopen (fifoPath, "r");
        fscanf (fifoR, "%s", buffer);
        fclose (fifoR); 
        */
       ++counter;
    }
    return 0;

}