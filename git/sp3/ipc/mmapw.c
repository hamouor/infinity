#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

int main ()
{
    int fd;
    void* file_memory;

    /* Prepare a file large enough to hold an unsigned integer. */
    fd = open ("mmap", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek (fd, FILE_LENGTH+1, SEEK_SET);
    write (fd, "", 1);
    lseek (fd, 0, SEEK_SET);
    /* Create the memory mapping. */
    file_memory = mmap (0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
    close (fd);
    /* Write a random integer to memory-mapped area. */
    sprintf((char*) file_memory, "%s\n", "ping");
    /* Release the memory (unnecessary because the program exits). */
    munmap (file_memory, FILE_LENGTH);
    return 0;
} 