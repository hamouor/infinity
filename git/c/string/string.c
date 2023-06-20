#include"string.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>


Char *Strcpy(char *dest, const char *src)
	{
	size_t i = 0;
	
	for( ; *(src+i) != '\0'; i++)
		{
		*(dest+i) = *(src+i);
		}
	*(dest+i) = '\0';
	return dest;
	}


/*copies a src string to dest string up to n characters*/	
char *Strncpy(char *dest, const char *src, size_t n)
	{
	size_t i = 0;
	
	for( ; i < n && src[i] != '\0'; i++)
		{
		dest[i] = src[i];
		}
	dest[i] = '\0';
	return dest;
	}
	

/*compares two strings up to n characters and returns the diffarence between the first different one*/
int Strncmp(const char* string1, const char* string2, size_t n)
	{
	size_t i = 0;
	
	while(*(string1+i) == *(string2+i) && *(string2+i) != '\0')
		{
		i++;
		if(i == n)
			{
			break;
			}
		}
	return (int)(*(string1+i)-*(string2+i));
	}
	

/*compares two strings ignoring differences in upper lower cases*/	
int Strcasecmp(const char* str1, const char* str2)
	{
	int result = 0;
	char a = 0;
	char b = 0;
	
	while(result == 0 && *str1 != '\0' && *str2 != 0)
		{
		a = tolower(*str1);
		b = tolower(*str2);
		result = a - b;
		++str1;
		++str2;
		}
	return result;
	}
	

/*finds first occurance of char c in s and returns its pointer*/
char* Strchr(const char* s, int c)
	{
	char* res = NULL;
	int i = 0;
	
	while(*(s + i) != '\0')
		{
		if(*(s + i) == (char)c)
			{
			res = (char*)(s + i);
			break;
			}
		++i;
		}
	if(*s == '\0' && (char)c == *s)
		{
		res = (char*)s;
		}
	return (char*)res;
	}
	

/*duplicates given str and returns pointer to duplicant*/
char* Strdup(const char* str)
	{
	size_t len = 0;
	char* dup = NULL;
	
	len = strlen(str);
	dup = malloc(len + 1);
	dup = strcpy(dup, str);
	return dup;
	}


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
	

