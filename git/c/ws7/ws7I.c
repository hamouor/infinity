#include"string.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>
/*returns the length of substring in s from the beginning is comprised solely of chars from accept */	
size_t Strspn(const char* s, const char* accept)
	{
	size_t len = 0;
	size_t i = 0;
	while(i < strlen(accept))
		{
		if (*(s + len) == *(accept +i))
			{
			++len;
			i = 0;
			}
		else
			{
			++i;
			}
		}
	return len;
	}
	

int IsPal(const char* str)
	{
	size_t i = 0;
	size_t mid = 0;
	size_t mid2 = 0;
	mid = strlen(str) / 2;
	if(strlen(str) % 2 == 0)
		{
		mid2 = mid -1;
		}
	else
		{
		mid2 = mid;
		}
	for ( ; i < strlen(str) / 2; i++)
		{
		if (*(str+mid-i) != *(str+mid2+i))
			{
			return 1;
			}
		}
	return 0;
	}
	

