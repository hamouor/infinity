#include "ws9.h"
#include "ws9.c"
#include<stdio.h>

int main()
{
	char *c = malloc(50), *d = malloc(50);
	Memset(c, 'c', 10);
	Memset(c+10, 'd', 20);
	printf("%s\n", c);
	Memcpy(d, c, 15);
	printf("%s\n", d);
	Memmove(c, c+8, 16);
	printf("%s\n", c);
	free(c);
	free(d);
	return 0;
}
