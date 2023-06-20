#include<stdlib.h>
#include<stdio.h>
int main()
{
static int s_i = 7;
int i =7;
int *ptr = &i;
int *ptr2 = (int *)malloc(sizeof(int));
if (ptr)
{
	int **ptr3 = &ptr;
	printf("\n %p", ptr3);
	ptr3=(int**)15;
	printf("\n %p", ptr3);
	printf("\n %d", i);
}
//printf("\n %ls", &ptr);

//printf("\n %ls", &i);
printf("\n %d", *ptr2);
free(ptr2);
return 0;
}
