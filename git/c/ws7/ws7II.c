#include"string.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>
/*duplicates given str and returns pointer to duplicant up to n characters*/
char *Strncat(char *dest, const char *src, size_t n)
	{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		{
		dest[dest_len + i] = src[i];
		}
	dest[dest_len + i] = '\0';
	return dest;
	}


/*finds first occurance of needle string in haystack string and returns pointer to its beginning in haystack or null if missing */	
char* Strstr(const char* haystack, const char* needle)
	{
	char* a = NULL;
	size_t i = 1;
	
	a = Strchr(haystack , (int)(*needle));
	if (strlen(a) < strlen(needle))
		{
		return NULL;
		}
	for( ; i<strlen(needle)-1; ++i)
		{
		if(*(a+i) != *(needle+i))
			{
			a = Strchr(a+1, (int)(*needle));
			if (strlen(a) < strlen(needle))
				{
				return NULL;
				}
			i = 1;
			}
		}
	if(i == strlen(needle)-1 && *(a+i) == *(needle+i))
		{
		return a;
		}
	return NULL;
	}
		


