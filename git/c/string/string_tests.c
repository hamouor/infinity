#include"string.h"
#include<stdio.h>

#define UNUSED(x) (void)(x)

void TestStrcpy();
void TestStrncpy();
void TestStrncmp();
void TestStrcasecmp();
void TestStrchr();
void TestStrdup();
void TestStrncat();
void TestStrstr();
void TestStrspn();
void TestIsPal();

void TestStrcpy()
	{
	char src[] = "abcdefg";
	char dest[8];
	
	char* destp = Strcpy(dest, src);
	
	printf("\ncopied string is %s\n", destp);
	}

void TestStrncpy()
	{
	char src[] = "abcdefg";
	char dest[15];
	size_t n = 3;
	char* a = Strncpy(dest, src, n);
	printf("\ncopied string is %s\n", a);
	}

oid TestStrncmp()
	{
	char str1[] = "abcdefg";
	char str2[] = "abcdss";
	size_t n = 3;
	
	printf("\ncompared up to %lu notes is %d\n", n, Strncmp(str1, str2, n));
	}

void TestStrcasecmp()
	{
	char str1[] = "abcdefg";
	char str2[] = "abcdEFG";
	
	printf("\ncomparison non case sensitive %d\n", Strcasecmp(str1, str2));
	}

void TestStrchr()
	{
	int c = (int)'f';
	char s[] = "blumpghflpof";
	char* res = Strchr(s, c);
	
	printf("\n%c\n", *res);
	}

void TestStrdup()
	{
	char str[] = "blumpghflpof";
	char *dup = NULL;
	
	dup = Strdup(str);
	printf("\n%s\n", dup);
	}

void TestStrncat()
	{
	char dest[15] = "aaassd";
	char src[] = "edcba";
	char* destp = NULL;
	size_t n = 10;

	destp = Strncat(dest, src, n);
	printf("\ncat says %s\n", destp);
	}

void TestStrstr()
	{
	char str1[] = "abcdefghiiiihi";
	char str2[] = "efg";
	
	printf("\nfirst occurance %s\n", Strstr(str1, str2));
	}

void TestStrspn()
	{
	char str1[] = "abcabcbbcdefghiiiihi";
	char str2[] = "abc";
	
	printf("\nlen of initial seg %lu\n", Strspn(str1, str2));
	}	

void TestIsPal()
	{
	char str1[] = "abcdefggfedcba";
	printf("%d", IsPal(str1));
	}

