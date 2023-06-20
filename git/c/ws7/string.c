#include"string.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>


char *Strcpy(char *dest, const char *src)
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



