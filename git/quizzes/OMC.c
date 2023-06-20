#include<stdio.h>
#include<limits.h>

typedef struct a
{
    int count;
    long int curr_run;
}charcount;

charcount count_lut[UCHAR_MAX] = {0,0};
int curr_max = 0;
long int curr_run = 0;

void CountMax(char c)
{
    if(!c)
    {
        printf("%d\n", curr_max);
        curr_max = 0;
        ++curr_run;
    }
    else
    {
        if(count_lut[c].curr_run == curr_run)
        {
            ++count_lut[c].count;
        }
        else
        {
            count_lut[c].curr_run = curr_run;
            count_lut[c].count = 1;
        }
        
        
        if(count_lut[c].count > curr_max)
        {
            curr_max = count_lut[c].count;
        }
    }
}

int main()
{
    char arr1[] = {'a', 'a', 'g', 'd', 'b', 'a', 'b', 'g', 0};
    char arr2[] = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 0};
    char arr3[] = {'a', 'a', 'g', 'd', 'b', 'g', 'b', 'c', 0};
    int i = 0;

    for(i = 0; i < 9; ++i)
    {
        CountMax(arr1[i]);
    }
    
    for(i = 0; i < 9; ++i)
    {
        CountMax(arr2[i]);
    }
    
    for(i = 0; i < 9; ++i)
    {
        CountMax(arr3[i]);
    }

    return 0;

}