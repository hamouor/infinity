#include"vector.h"
#include<stdlib.h> /*size_t, malloc*/
#include<assert.h> /*assert*/
#include<string.h> /*memcpy*/
struct vector
	{
		size_t size; /* total number of currently occupied elements */
		size_t capacity; /* current maximum of available elements */
		size_t min_capacity; /* updated according to requests of user */
		size_t element_size; /* size of element in bytes */
		void *array; /* the start of the array */
	};

vector_ty *VectorCreate(size_t element_size, size_t capacity)
{
	vector_ty* new_vect = NULL;
	void* data = NULL;
	
	new_vect = (vector_ty*)malloc(sizeof(vector_ty));
	data = malloc(element_size * capacity);
	
	new_vect -> size = 0;
	new_vect -> capacity = capacity;
	new_vect -> min_capacity = capacity;
	new_vect -> element_size = element_size;
	new_vect -> array = data;
	
	return new_vect;
}

void VectorDestroy(vector_ty *vector)
{
	assert(vector);
	assert(vector -> array);
	
	free(vector -> array);
	vector -> array = NULL;
	free(vector);
	vector = NULL;	
}

int VectorPushBack(vector_ty *vector, const void *element)
{
	assert(vector);
	assert(vector -> array);
	
	if (vector -> capacity == vector -> size)
	{
		vector -> array = realloc(vector -> array, vector -> capacity * 2 * vector -> element_size);
		if (vector -> array != NULL)
		{
			memcpy((void*)((char*)(vector -> array) + (vector -> size * vector -> element_size)), element, vector -> element_size);
			vector -> capacity *= 2;
			vector -> size += 1;
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		memcpy((void*)((char*)(vector -> array) + (vector -> size * vector -> element_size)), element, vector -> element_size);
		vector -> size += 1;
		return 0;
	}
}

void VectorPopBack(vector_ty *vector)
{
	assert(vector);
	assert(vector -> array);
	
	vector -> size -= 1;
	if ((vector -> size <= vector -> capacity / 4) && (vector -> capacity / 2 >= vector -> min_capacity))
	{
		vector -> array = realloc(vector -> array, vector -> element_size * vector -> capacity / 2);
		vector -> capacity /= 2;	
	}
}

void *VectorGetAccessToElement(const vector_ty *vector, size_t index)
{
	assert(vector);
	assert(vector -> array);
	
	return (void*)((char*)vector -> array + (vector -> element_size * index));
}

size_t VectorSize(const vector_ty *vector)
{
	assert(vector);
	assert(vector -> array);
	
	return vector -> size;	
}

size_t VectorCapacity(const vector_ty *vector)
{
	assert(vector);
	assert(vector -> array);
	
	return vector -> capacity;
}

int VectorReserve(vector_ty *vector, size_t new_capacity)
{
	assert(vector);
	assert(vector -> array);
	
	vector -> array = realloc(vector -> array, vector -> element_size * new_capacity);
	if (vector -> array == NULL)
	{
		return 1;
	}
	else
	{
		vector -> capacity = new_capacity;
		vector -> min_capacity = new_capacity;
		return 0;
	}
}

void VectorShrinkToFitSize(vector_ty *vector)
{
	assert(vector);
	assert(vector -> array);
	
	vector -> array = realloc(vector -> array, vector -> size * vector -> element_size);
	vector -> min_capacity = vector -> size;
	vector -> capacity = vector -> size;
}


