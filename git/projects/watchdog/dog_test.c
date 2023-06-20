#include "watchdog.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
    int a = 0;
    time_t to_sleep = 30;

    if(WatchdogEnable(argv))
    {
        return 1;
    }

    while (to_sleep)
    {
        to_sleep = sleep(to_sleep);
    }
    
    
    a = a / 0;
    WatchdogDisable();
    return 0;
}