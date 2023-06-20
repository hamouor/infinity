#include "ws8.h"
#include<stdio.h>

typedef void (*funcptr)(void*);
typedef void (*funcptr2)(void*);


typedef struct AnyPtr
{
	void* ptr;
	funcptr func;
};

static struct AnyPtr array[10] = {0};

void PrintInt(void* num)
{
	printf("%d\n", *(int*)num);
}

void PrintFloat(float* num)
{
	printf("%f\n", *num);
}

void PrintStr(char* str)
{
	printf("%s\n", str);
}


void AddInt(int* num, int num2)
{
	*num += num2;
}

void AddFloat(float* num, float num2)
{
	*num += num2;
}

void init()
{
	array[0].ptr = (void*)4;
	array[0].func = *PrintInt;
}	
