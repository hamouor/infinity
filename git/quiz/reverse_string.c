#include<stdio.h>
#include<ctype.h>
#include<string.h>

void TF(int num);
void RevLow(char* str);

void TF(int num)
{
	int i = 1;
	int printed = 0; 
	for( ; i < num; ++i)
	{
		if(i % 3 == 0)
		{
			printf("T");
			printed = 1;
		}
		if(i % 5 == 0)
		{
			printf("F");
			printed = 1;
		}
		if(printed == 0)
		{
			printf("%d", i);
		}
		printed = 0;
	}
}

void RevLow(char* str)
{
	int len = strlen(str) - 1;
	int i = 0;
	char temp = '\0';
	for ( ; i <= (len / 2); ++i)
	{
		temp = tolower(*(str + i));
		*(str + i) = tolower(*(str + len - i));
		*(str + len - i) = temp;
	}
}

/* weigh 3 vs 3
	if even, weigh out of the remaining 1v1
		if even its the third
		if one is heavy its the one
	if one pile is heavy weigh 1 v 1 */

	
