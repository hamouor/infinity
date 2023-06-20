#include <stdio.h>

void Swape(int *num1, int *num2);
void CopyArray(int arr[], int copy[], int size);
void SwapT(size_t *t1, size_t *t2);
size_t Strlen(char* string);
int Strcmp(char* string1, char* string2);

int main()
	{
	int i=0;
	char a[14] = "cASAa";
	char b[14] = "popop";
	i=i+Strcmp(a,b);
	printf("%d" ,i);
	return 0;
	}

void Swape(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void TestSwape()
	{
	int a = 520;
	int b = 10;
	int* ptr1 = &a;
	int* ptr2 = &b;
	printf("before %d  %d\n", a, b);
	Swape(ptr1, ptr2);
	printf("after %d  %d\n", a, b);
	}
	
void CopyArray(int arr[], int copy[], int size)
{
  int i=0;
  for (i = 0; i < size; ++i)
  {
    copy[i] = arr[i];
  }
}

void TestCopyArray()
	{
	int a[] = {0, 1, 2, 3, 4};
	int b[5];
	CopyArray(a, b, sizeof(a));
	printf("after copy %d\n", b);
	}
	
void SwapT(size_t *t1, size_t *t2)
	{
	size_t temp;
	temp = *t1;
	*t1 = *t2;
	*t2 = temp;
	}

void TestSwapT()
	{
	

void SwapTt(size_t **t1, size_t **t2)
	{
	size_t *temp;
	temp = *t1;
	*t1 = *t2;
	*t2 = temp;
	}
	
size_t Strlen(const char* string)
	{
	int i = 0;
	while (*(string+i) != '\0')
		{
		i++;
		}
	return i;
	}
	
int Strcmp(const char* string1, const char* string2)
	{
	int i = 0;
	while(*(string1+i) == *(string2+i) && *(string2+i) != '\0')
		{
		i++;
		}
	return (int)(*(string1+i)-*(string2+i));
	}
