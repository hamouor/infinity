#include <stddef.h>		/*size_t*/ /*ssize_t*/ /*NULL*/
#include <assert.h>		/*guess*/
#include <stdlib.h>		/*malloc free*/

#include "cbuffer.h"

struct cbuffer 
{
	char *read;
	char *write; /*will point to NULL if array is full*/
	size_t capacity;
	char *arr;
};

char *nextelem(cbuffer_ty* cbuff, char* elem);

cbuffer_ty *CBufCreate(size_t capacity)
{
	cbuffer_ty* new = (cbuffer_ty*)malloc(sizeof(cbuffer_ty) + capacity);
	
	if(new == NULL)
	{
		return NULL;
	}
	new -> read = (void*)(new + 1);
	new -> write = (void*)(new + 1);
	new -> capacity = capacity;
	new -> arr = (char*)(new + 1);
	
	return new;
}

void CBufDestroy(cbuffer_ty *cbuffer)
{
	assert(cbuffer);
	
	free(cbuffer);
	cbuffer = NULL;
}

size_t CBufFreeSpace(const cbuffer_ty *cbuffer)
{
	int write_to_read_offset = 0;
	
	assert(cbuffer);
	
	if (cbuffer -> write == NULL)
		{
			return (size_t)0;
		}

	write_to_read_offset =  (cbuffer -> write) - (cbuffer -> read);

	if (write_to_read_offset >= 0) /*write is after read in the array*/
	{
		return ((cbuffer -> capacity) - write_to_read_offset );
	}

	return (-(write_to_read_offset)); /*read is after write*/
}

size_t CBufSize(const cbuffer_ty *cbuffer)
{
	assert(cbuffer);

	return ((cbuffer -> capacity) - CBufFreeSpace(cbuffer));
}

ssize_t CBufRead(cbuffer_ty *cbuffer, void *output_buf, size_t count)
{
	size_t counter = 0;
	char *runner = cbuffer -> read, *out = output_buf;

	assert(cbuffer);
		
	if (CBufSize(cbuffer) == 0)
	{
		return (ssize_t)(-1);
	}
	
	if (count > CBufSize(cbuffer))	/*making sure count does not try to read more than i have*/
	{
		count = CBufSize(cbuffer);
	}
	
	for(; counter < count; ++counter)
	{
		*out = *runner;
		runner = nextelem(cbuffer, runner);
		++out;
	}
	
	if (cbuffer -> write == NULL) /*if array was full earlier, update the write pointer to the previous location of read*/
	{
		cbuffer -> write = cbuffer -> read;
	}
	
	cbuffer -> read = runner;
	
	return count;
	
}

ssize_t CBufWrite(cbuffer_ty *cbuffer, const void *input_buf, size_t count)
{
	size_t counter = 0;
	char *runner = cbuffer -> write, *in = (char*)input_buf;

	assert(cbuffer);
		
	if (cbuffer -> write == NULL) /*array is full*/
	{
		return (ssize_t)(-1);
	}
	
	if (count > CBufFreeSpace(cbuffer))	/*making sure count doesnt try to write more than the free space*/
	{
		count = CBufFreeSpace(cbuffer);
	}
	
	for(; counter < count; ++counter)
	{
		*runner = *in;
		runner = nextelem(cbuffer, runner);
		++in;
	}
	cbuffer -> write = runner;
	
	if (cbuffer -> write == cbuffer -> read)	/*if array is now full, update write to be null*/
	{
		cbuffer -> write = NULL;
	}
		
	return count;
	
}

int CBufIsEmpty(const cbuffer_ty *cbuffer)
{
	assert(cbuffer);
	
	return (!CBufSize(cbuffer));
}

char *nextelem(cbuffer_ty* cbuff, char* elem)   /*will assure cyclic moving over the array*/
{
	assert(cbuff);
	assert(elem);
	
	if (elem == (cbuff -> arr) + (cbuff -> capacity)-1) /*elem is the last byte in the array*/
	{
		return (cbuff -> arr);
	}
	return (elem + 1);
}
#include <string.h>
int CBStrNCmp(cbuffer_ty *cbuffer, char *str, size_t n)
{
    return strncmp(cbuffer->arr, str, n);
}