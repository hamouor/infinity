/******************************************************************************/
/*									Vector									  */ 
/******************************************************************************/
/*******************************************************************************
* DESCRIPTION: A Vector data type which supports a user-defined element size, 
* 	pushing and popping elements, accessing elements directly, and resizes 
*	itself on demand. The user can also reserve extra memory for the vector and
*	shrink it to fit the current amount of elements.
* AUTHOR: HRD24
* REVIEWER:
* DATE: 07/04/2022
* VERSION: 0.1
*******************************************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>

typedef struct vector vector_ty;

/*******************************************************************************
* Function: Allocate memory for a dynamic vector. Size and capacity are 
	user-defined.
* Arguments: element_size is the size required in bytes. capacity is the maximum
	 elements the vector contain for now (capacity can be change later through
	 DynVectorReserve).          
* Return value: A pointer to vector of type vector_ty.
* Notes: A created vector MUST be destroyed after use!
* Complexity: O(1)
*******************************************************************************/
vector_ty *VectorCreate(size_t element_size, size_t capacity);


/*******************************************************************************
* Function: Frees the memory allocated to a vector.
* Arguments: A pointer to the vector.
* Complexity: O(1)
*******************************************************************************/
void VectorDestroy(vector_ty *vector);


/*******************************************************************************
* Function: Add a new element to the end of the vector. 
* Arguments: A pointer to the vector, the element to be added.
* Return value: 0 for success, 1 if pushback failed
* Notes: If the vector is full, it will attempt to increase its capacity.
* Complexity: average case O(1), worst case O(n) 
*******************************************************************************/
int VectorPushBack(vector_ty *vector, const void *element);


/*******************************************************************************
* Function: Remove the last added element from the end of the vector.
* Arguments: A pointer to the vector.
* Notes: If there is significantly less elements in the vector than the vector's
* 	capacity, the vector will shrink but not less than user capacity requests.
* Complexity: average case O(1), worst case O(n) 
*******************************************************************************/
void VectorPopBack(vector_ty *vector);


/*******************************************************************************
* Function: Returns a pointer to the element and lets so user could read or 
*	write to it.
* Arguments: A pointer to the vector, the desired index.
* Return value: A pointer to the element from the vector.
* Notes: Undefined behavior - If index is larger than size.
* Complexity: O(1)
*******************************************************************************/
void *VectorGetAccessToElement(const vector_ty *vector, size_t index);


/* ANOTHER FUNCTION TO SET? */
void VectorSetElement(const vector_ty *vector, size_t index, void *data);

/*******************************************************************************
* Function: Returns the current vector size in the memory.
* Arguments: A pointer to the vector.
* Return value: An unsigned integer describing the size of the vector in elements.
* Complexity: O(1)
*******************************************************************************/
size_t VectorSize(const vector_ty *vector);


/*******************************************************************************
* Function: Returns the current number of elements in the vector.
* Arguments: A pointer to the vector.
* Return value: An unsigned integer describing the number of elements in the 
* 	vector.
* Complexity: O(1)
*******************************************************************************/
size_t VectorCapacity(const vector_ty *vector);


/*******************************************************************************
* Function: Attempts to increase vector to a new capacity.
* Arguments: A pointer to the vector
* Notes: Undefined behavior - If new_capacity is smaller than current capacity.
* Complexity: average case O(1), worst case O(n) 
*******************************************************************************/
void VectorReserve(vector_ty *vector, size_t new_capacity);


/*******************************************************************************
* Function: Shrinks the vector's allocated memory to fit the amount of occupied
* 	elements in the vector.
* Arguments: A pointer to the vector.
* Complexity: average case O(1), worst case O(n) 
*******************************************************************************/
void VectorShrinkToFitSize(vector_ty *vector);

#endif /* __VECTOR_H__ */
