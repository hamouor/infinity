#include<string.h>
#include<stdio.h>

int IsRot(char* s1, char* s2);

int main()
{
	char s1[] = "1122";
	char s2[] = "1112";
	int a = IsRot(s1,s2);
	printf("%d",a);
	return 0;
}

int IsRot(char* s1, char* s2)
{
	int i = 0;
	int j = strlen(s1);
	if (j == (int)strlen(s2))
	{
		for(; i < j; ++i)
		{
			if ((strncmp(s1 + i, s2, j - i) == 0) && (strncmp(s1, s2 + j - i, i)) == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
