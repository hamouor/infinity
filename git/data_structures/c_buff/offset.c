#include<stdio.h>
#include<stddef.h>

#define Offsetof(a,b) ((size_t)(&(((a*)(0))->b)))

struct foo{
	int a;
	int b;
	int c;
};

int main()
{
	printf("%lu\n", Offsetof(struct foo,a));	
	return 0;
}
