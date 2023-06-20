#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100
int main ()
{
    int fd;
    void* file_memory;
    char buffer[5];
    /* Open the file. */
    fd = open ("mmap", O_RDWR, S_IRUSR | S_IWUSR);
    /* Create the memory mapping. */
    file_memory = mmap (0, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close (fd);
    
    sscanf ((char*)file_memory, "%s", &buffer);
    printf ("%s\n", buffer);
    /* Release the memory (unnecessary because the program exits). */
    munmap (file_memory, FILE_LENGTH);
    return 0;
} 