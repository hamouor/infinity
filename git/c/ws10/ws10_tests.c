#include "ws10.h"
#include "ws10.c"
#include<stdio.h>      /*printf, malloc*/
#include<stdlib.h>     /*atoi*/
#include<string.h>     /*strlen*/

int main()
{
	char test_arr[] = "1F0";
	int  test_int = 496;
	int test_base = 16;
	char* buff = NULL;
	int test_res = 0;
	
	char arr1[] = "abcdefg";
	char arr2[] = "abcdefg";
	char arr3[] = "gf";
	
	buff = malloc(4);
	buff = IntToStr(test_int, buff, test_base);
	printf("%s\n", buff);
	
	test_res = StrToInt(test_arr, test_base);
	printf("%d\n", test_res);
	
	OnlyInTwo(arr1, arr2, arr3, strlen(arr1), strlen(arr2), strlen(arr3));
	
	BigLitEndi();
	
	return 0;
}
