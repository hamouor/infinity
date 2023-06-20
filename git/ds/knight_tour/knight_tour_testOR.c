#include <stdio.h>

#include"knight_tour.h"

int main()
{
    int path[64] = {0};
    int i = 0;
    KnightTour(path, 49);

    for(; i < 64; ++i)
    {
        printf("%d\n", path[i]);
    }

 
    return 0;
}