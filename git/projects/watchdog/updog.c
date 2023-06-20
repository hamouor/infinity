#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "shared_sched.h"

int main(int argc, char** argv)
{
    printf("a pooch is born\n");
    return SSRun();
}

/*gd updog.c shared_sched.c -pthread scheduler_pq.c heap.c heap_pq.c schedtask.c uid.c vector.c*/

