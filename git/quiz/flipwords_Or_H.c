#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void FlipWords(char* string);

int main()
{
	char string[] = "suck your mom";
	FlipWords(string);
	printf("%s\n", string);
	return 0;	
}

void FlipWords(char* string)
{
	char * buff = NULL;
	char* index = NULL;
	char* str = string;
	int len = 0;
	buff = (char*)malloc(strlen(str));
	buff += strlen(str);
	*buff = '\0';
	--buff;
	while(*str != '\0')
	{
		len = 1;
		index = str;
		while(*str != ' ' && *str != '\0')
		{
			++str;
			--buff;
			++len; 
		}

		strncpy(buff, index, len);
	}
	string = buff;
	free((void*)buff); buff = NULL;
}
