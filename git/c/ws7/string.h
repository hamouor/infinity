#ifndef __STRING_H__
#define __STRING_H__
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>

char *Strcpy(char *dest, const char *src);

char *Strncpy(char *dest, const char *src, size_t n);

int Strncmp(const char* string1, const char* string2, size_t n);

int Strcasecmp(const char* str1, const char* str2);

char* Strchr(const char* s, int c);

char* Strdup(const char* str);

char *Strncat(char *dest, const char *src, size_t n);

char* Strstr(const char* haystack, const char* needle);

size_t Strspn(const char* s, const char* accept);

int IsPal(const char* str);

#endif



