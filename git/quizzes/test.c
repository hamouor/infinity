#include<stdio.h>

union person{
long x;
char y[9];
};

int main()
{
	printf("%d\n%d\n", sizeof(union person));
	return 0;
}
