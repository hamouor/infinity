#include <stdlib.h> /* malloc(), realloc() */
#include <stdio.h> /* printf() */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy() */

#include "vector.h"

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 0.5
#define SHRINK_RATIO 0.25

#define SUCCESS 0
#define FAILURE 1

#define V_SIZE vector->size
#define V_CAPACITY vector->capacity
#define V_MIN_CAPACITY vector->min_capacity
#define V_ELEMENT_SIZE vector->element_size
#define V_ARRAY vector->array

#define IS_EMPTY(vector) V_SIZE == 0
#define IS_FULL(vector) V_SIZE == V_CAPACITY

#define MAX(a, b) ((a > b) ? a : b)

struct vector
{
	size_t size; /* total number of currently occupied elements */
	size_t capacity; /* current maximum of available elements */
	size_t min_capacity; /* updated according to direct user requests */
	size_t element_size; /* size of element in bytes */
	char *array; /* the start of the array */ 
};

static int ResizeVector(vector_ty *vector, size_t new_capacity);

vector_ty *VectorCreate(size_t element_size, size_t capacity)
{
	vector_ty *vector = (vector_ty *)malloc(sizeof(vector_ty));
	
	if (NULL == vector)
	{
		return NULL;
	}
	
	V_ARRAY = (char *)malloc(sizeof(char) * element_size * capacity);
	
	if (NULL == V_ARRAY)
	{
		free(vector), vector = NULL;
		return NULL;
	}
	
	V_SIZE = 0;
	V_CAPACITY = capacity;
	V_MIN_CAPACITY = capacity;
	V_ELEMENT_SIZE = element_size;
	
	return vector;
}

void VectorDestroy(vector_ty *vector)
{
	free(V_ARRAY);
	V_ARRAY = NULL;
	
	V_SIZE = 0;
	V_CAPACITY = 0;
	V_MIN_CAPACITY = 0;
	V_ELEMENT_SIZE = 0;
	
	free(vector), vector = NULL;
}

int VectorPushBack(vector_ty *vector, const void *element)
{
	if (IS_FULL(vector))
	{
		if (FAILURE == ResizeVector(vector, V_CAPACITY * GROWTH_FACTOR))
		{
			return FAILURE;
		}
	}
	
	memcpy(V_ARRAY + V_SIZE * V_ELEMENT_SIZE, element, V_ELEMENT_SIZE);
	
	++V_SIZE;
	
	return SUCCESS;
}

void VectorPopBack(vector_ty *vector)
{
	assert(!IS_EMPTY(vector));
	
	--(V_SIZE);
	
	if (V_SIZE < V_CAPACITY * SHRINK_RATIO)
	{
		ResizeVector(vector, MAX(V_CAPACITY * SHRINK_FACTOR, V_MIN_CAPACITY));
	}
}

void *VectorGetAccessToElement(const vector_ty *vector, size_t index)
{
	assert(!IS_EMPTY(vector));
	
	return (void *)(V_ARRAY + index * V_ELEMENT_SIZE);
}

void VectorSetElement(const vector_ty *vector, size_t index, void *data)
{
    char *start = NULL; 

    assert(vector);
    assert(data);

    start = vector->array;
    start += index * vector->element_size;

    memcpy(start, data, vector->element_size);
}

size_t VectorSize(const vector_ty *vector)
{
	return V_SIZE;
}

size_t VectorCapacity(const vector_ty *vector)
{
	return V_CAPACITY;
}

void VectorReserve(vector_ty *vector, size_t new_capacity)
{
	if (FAILURE == ResizeVector(vector, new_capacity))
	{
		return;
	}
	
	V_MIN_CAPACITY = new_capacity;
}

void VectorShrinkToFitSize(vector_ty *vector)
{
	V_MIN_CAPACITY = (V_SIZE > 0) ? V_SIZE : 1;
	
	ResizeVector(vector, V_SIZE);
}

static int ResizeVector(vector_ty *vector, size_t new_capacity)
{
	void *new_array = realloc((void *)V_ARRAY, new_capacity * V_ELEMENT_SIZE);
	
	if (NULL == new_array)
	{
		return FAILURE;
	}
	
	V_ARRAY = (char *)new_array;
	V_CAPACITY = new_capacity;
	return SUCCESS;
}
