#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc*/
#include <stdio.h>/*printf*/
#include "ws9.h"

#define WORD 8

/* Memset will recieve a destination pointer, value casted to unsigned char to change the memory to pointed to by dest and len suggesting the amount of bytes to change.
step I cast val to unsigned char. check alignment by dest%8. 8- dest%8 is the number of individual steps needed to recieve alignment. (len - that)/8 number of words to set. (len - that)%8 number of individual steps to perform at the end*/ 

void* Memset(void* dest, int val, unsigned int len)
{
	size_t word_loops = 0, byte_loopsI = 0, byte_loopsII = 0, i = 0; /*byte loopsI to reach alignment, word loops to insert wordsize chunks, byte loops II the reminder of len after both operations*/
	unsigned char wordsize_arr[8] = {0};/*will house a wordsize chunk of data*/
	char *buff = (char*)dest;
	unsigned char c = (unsigned char)val;
	long wordsize_data = 0;
	long * wordsize_ptr = NULL;/*will point to an 8 byte data portion*/
	if ((unsigned long)dest % WORD == 0)/*checking alignment and calculating the loops accordingly*/
	{
		word_loops = len / WORD;
		byte_loopsI = 0;
		byte_loopsII = len % WORD;
	}
	else
	{
		byte_loopsI = WORD - ((unsigned long)dest % WORD);
		if (len > byte_loopsI)
		{
			len = len - byte_loopsI;
			word_loops = len / WORD;
			byte_loopsII = len % WORD;
		}
		else
		{
		byte_loopsI = len;
		}
	}
	for(; byte_loopsI > 0; --byte_loopsI)
	{
		*(unsigned char*)buff = c;
		++buff;
	}
	if (word_loops > 0)
	{
		for(;i < WORD; ++i)/*creating my wordsize datat all composed of c*/
		{
			wordsize_arr[i] = c;
		}
	wordsize_data = *(long*)&wordsize_arr[0];
	wordsize_ptr = (long*)buff;
	}
	for(; word_loops > 0; --word_loops)
	{
		*wordsize_ptr = wordsize_data;
		++wordsize_ptr;
	}
	buff = (char*)wordsize_ptr;
	for(; byte_loopsII > 0; --byte_loopsII)
	{
		*(unsigned char*)buff = c;
		++buff;
	}
	return (void*)dest;
}


/*assuming dest and src are aligned. checking the %8 of n and /8. /8 times a full word and %8 times a singe byte*/

void *Memcpy(void *dest, const void * src, size_t n)
{
	int word_loop = 0, byte_loop = 0;
	long *wordsize_ptr_dest = NULL, *wordsize_ptr_src = NULL;
	char *bytesize_ptr_dest = NULL, *bytesize_ptr_src = NULL;
	
	word_loop = n / WORD;
	byte_loop = n % WORD;
	wordsize_ptr_dest = (long*)dest;/*beginning with wordsize data insertion*/
	wordsize_ptr_src = (long*)src;
	bytesize_ptr_dest = ((char*)dest+(WORD*word_loop));/*after wordsize datat insert, bytesize data pointer*/
	bytesize_ptr_src = ((char*)src+(WORD*word_loop));
	for(; word_loop > 0; --word_loop)
	{
		*wordsize_ptr_dest = *wordsize_ptr_src;
		++wordsize_ptr_dest;
		++wordsize_ptr_src;
	}


	for (; byte_loop > 0; --byte_loop)
	{
		*bytesize_ptr_dest = *bytesize_ptr_src;
		++bytesize_ptr_dest;
		++bytesize_ptr_src;
	}
	return dest;
}

void *Memmove(void *dest, const void * src, size_t n)
{
	int word_loop = 0, byte_loop = 0;
	long *wordsize_ptr_dest = NULL, *wordsize_ptr_src = NULL;
	char *bytesize_ptr_dest = NULL, *bytesize_ptr_src = NULL;
	word_loop = n / WORD;
	byte_loop = n % WORD;
	wordsize_ptr_dest = (long*)dest;
	wordsize_ptr_src = (long*)src;
	bytesize_ptr_dest = ((char*)dest+(WORD*word_loop));
	bytesize_ptr_src = ((char*)src+(WORD*word_loop));
	if ((unsigned long)dest > (unsigned long)src)
	{
		for (; byte_loop > 0; --byte_loop)/*same as memcpy but running backwords*/
		{
			*(bytesize_ptr_dest + byte_loop) = *(bytesize_ptr_src + byte_loop);
			--bytesize_ptr_dest;
			--bytesize_ptr_src;
		}
		for(; word_loop > 0; --word_loop)
		{
			*(wordsize_ptr_dest + word_loop) = *(wordsize_ptr_src + word_loop);
			--wordsize_ptr_dest;
			--wordsize_ptr_src;
		}
	}
	else
	{
		Memcpy(dest, src, n);
	}
	return dest;
}
	
