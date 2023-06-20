#include "ws10.h"
#include<stdio.h> /*printf*/
#include<stdlib.h>/*malloc*/
#include<string.h>/*strlen*/


#define IS_LITTLE_ENDIAN ((union { unsigned short int X; unsigned char Y; }) { .X = 1 } .Y)

void reverse(char *s);

/*extracting the last digit of num, interprets it to digit or char according to the base and inserts it to str. reverses the string to recieve correct order*/
char *IntToStr(int num, char* str, int base)
{
	int digit = 0, counter = 0;
	char gap = '0';
	while (num > 0)
	{
		digit = num % base;
		num = num / base;
		if (digit > 9)
		{
			digit += 7; /*shift towards alphabetical rep*/
		}
		*(str + counter) = gap + (char)digit;
		counter += 1;
	}
	*(str + counter) = '\0';
	reverse(str);
	return str;
}

/* extracts extracts character one by one, and adds their value 1-36, multiplyes the result each time according to base*/
int StrToInt(const char *str, int base)
{
	int answer = 0;
	char* buff = (char*)str;
	while (*buff != '\0')
	{
		*buff -= '0';
		if ((int)*buff > 9)
		{
			answer -= 7;/*shift towards alphabetical rep*/
		}
		answer += (int)*buff;
		answer *= base;
		++buff;
	}
	answer /= base;
	return answer;
}

void reverse(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = strlen(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}
/*creates an array to signify all char options, adds number of instances of each char according to their respective place through int casting. summation signifying appearance in arr1 and 2 and not 3 will cause printing*/
void OnlyInTwo(char* arr1, char* arr2, char* arr3, int len1, int len2, int len3)
{
	char *arr4 = NULL;
	arr4 = (char*)malloc(256);

	for(--len3; len3 >= 0; --len3)
	{
		*(arr4 + (int)*(arr3 +len3)) = 'A';

	}
	for(--len2; len2 >= 0; --len2)
	{
		if (*(arr4 + (int)*(arr2 +len2)) != 'A')
		{	
			*(arr4 + (int)*(arr2 +len2)) = 'B';
 		}
 	}
 	for(--len1; len1 >= 0; --len1)
	{
		if (*(arr4 + (int)*(arr1 + len1)) == 'B')
		{
			printf("%c\n", *(arr1+len1));
		}
 	}
}
 
 
/*determining big or little endian system by checking the first byte saved on an integer*/
void BigLitEndi()
{
	int i = 1;
	if(*(char*)&i == 1)
	{
		printf("big\n");
	}
	else
	{
		printf("liitle\n");
	}
}
