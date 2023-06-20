#include <stdio.h>
#include <time.h>

int func(void* a, void* b);

int main()
{
    int arr[5000], arr2[5000];
    int i = 0;
    int size = sizeof(arr) / sizeof(int);
    int arr_size = 5000;
    clock_t timer1, timer2;


    for(i = 0; arr_size > i; ++i)
	{
		arr[i] = rand() % arr_size;
        arr2[i] = arr[i];
	}
	
    timer1 = clock();
    Qsort((void*)arr, size, sizeof(int), func);
    timer1 = clock() - timer1;
	
    timer2 = clock();
	qsort((void*)arr2, size, sizeof(int), func);
	timer2 = clock() - timer2;

    printf("%ld\n%ld\n", timer1, timer2);

    return 0;
}