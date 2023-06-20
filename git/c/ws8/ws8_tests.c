#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX2(a, b) ((a > b) ? a : b)
#define MAX3(a, b, c) ((a > c) ? MAX2(a, b) : MAX2(c, b))

#define SIZEOF_VAR(var) ((char *)(&(var) + 1) - (char *)&(var))
#define SIZEOF_TYPE(type) (size_t)((type*)0 + 1)
	
struct AnyPtr;
typedef struct AnyPtr AnyPtr;

typedef void (*funcptr)(AnyPtr*); /*printing function*/
typedef void (*funcptr2)(AnyPtr*, int);/*adding function*/
typedef void (*funcptr3)(AnyPtr*);/*cleaning function*/

struct AnyPtr
{
	void* ptr;
	funcptr func;
	funcptr2 func2;
	funcptr3 func3;
};

static AnyPtr array[3] = {0};

void Init();
void PrintArr();
void AddArr(int num);
void CleanArr();

int main()
{
	int z = 10;
	Init();
	PrintArr();
	AddArr(z);
	PrintArr();
	CleanArr();
	PrintArr();
	return 0;
}

void PrintInt(AnyPtr* num)
{
	printf("%d\n", (int)(long)num->ptr);
}

void PrintFloat(AnyPtr* num)
{
	printf("%f\n", *(float*)&num->ptr);
}

void PrintStr(AnyPtr* str)
{
	printf("%s\n", (char*)str->ptr);
}


void AddInt(AnyPtr* num, int num2)
{
	num->ptr = (void*)(long)((int)(long)(num->ptr) + num2);
}

void AddFloat(AnyPtr* num, int num2)
{
	float result = *(float *)&num->ptr + num2;
	num->ptr = (void *)*(unsigned long *)&result;
}

void AddStr(AnyPtr* str, int str2)
{
	char* p;
	int l=str2, k, f=0;
	while(l != 0)
	{
		l = l/10;
		f+=1;
	}
	p = (char*)malloc(f+2);
	sprintf(p, "%d", str2);
	k = strlen((char*)(str->ptr));
	str->ptr = (char*)realloc(str->ptr, k + f + 2);
	strcat((char*)str->ptr, p);
	free(p);
}

void CleanInt(AnyPtr* num)
{
	num->ptr = NULL;
}

void CleanFloat(AnyPtr* num)
{
	num->ptr = NULL;
}

void CleanStr(AnyPtr* str)
{
	free((char*)str->ptr);
	str->ptr = NULL;
}

void PrintArr()
{
	int i = 0;	
	for (; i < 3; ++i)
	{
		array[i].func(&array[i]);
	}
}

void AddArr(int num)
{
	int i = 0;	
	for (; i < 3; ++i)
	{
		array[i].func2(&array[i], num);
	}
}

void CleanArr()
{
	int i = 0;	
	for (; i < 3; ++i)
	{
		array[i].func3(&array[i]);
	}
}

void Init()
{
	int test_int = 4;
	float test_float = 3.14;
	char test_str[] = "RinaMeet16";


	array[0].ptr = (void*)(long)test_int;
	array[0].func = *PrintInt;
	array[0].func2 = *AddInt;
	array[0].func3 = *CleanInt;
	
	array[1].ptr = (void *)(*((unsigned long *) &test_float));
	array[1].func = *PrintFloat;
	array[1].func2 = *AddFloat;
	array[1].func3 = *CleanFloat;
	
	array[2].ptr = malloc(sizeof(char) * (strlen(test_str) + 1));
	strcpy((char *)array[2].ptr, test_str);
	array[2].func = *PrintStr;
	array[2].func2 = *AddStr;
	array[2].func3 = *CleanStr;
}	
