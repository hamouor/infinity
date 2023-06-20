#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> 		 /* size_t */

/*----------------------------------------------------------------------------*/
/*				Bit Array                                      */ 
/*----------------------------------------------------------------------------*/
/*
/* DESCRIPTION: Bit array of a 64 bit size, containing values of 0 or 1 can be handled with this API . Fit for LSB system (little endian)	.	
/* AUTHOR:	Or Hamou		
/* REVIEWER:	Tom Lyden	
/* DATE:	04/04/2022			
/* VERSION:      		
/* 
/*----------------------------------------------------------------------------*/

typedef size_t bit_arr_ty;

char lut[256];
short lutII[256];

/*******************************************************************************
* Function:  set all bits in the bit array to 1            
* Arguments:      bit_arr_ty*  to requested array       
* Return value:     bit_arr_ty*  
* Notes: 	        
*******************************************************************************/
bit_arr_ty BitArraySetAll(void); 


/*******************************************************************************
* Function:  set all bits in the bit array to 0       
* Arguments:    bit_arr_ty*  to requested array       
* Return value:     bit_arr_ty*  
* Notes: 	        
*******************************************************************************/
bit_arr_ty BitArrayResetAll(void); 


/*******************************************************************************
* Function:  set the 'n' bit on  . starting index = 0     
* Arguments:   bit_arr_ty*  to requested array, index is the requested bit spot in the array,        
* Return value:    bit_arr_ty*   
* Notes: undefined behaviour if index is smaller than 0 or larger than bit count in the array 	        
*******************************************************************************/
bit_arr_ty BitArraySetOn(bit_arr_ty bit_array, size_t index); 


/*******************************************************************************
* Function:  set the 'n' bit off. starting index = 0       
* Arguments:   bit_arr_ty*  to requested array, index is the requested bit spot in the array,
* Return value:     bit_arr_ty*  
* Notes: 	undefined behaviour if index is smaller than 0 or larger than bit count in the array     
*******************************************************************************/
bit_arr_ty BitArraySetOff(bit_arr_ty bit_array, size_t index); 


/*******************************************************************************
* Function:  change bit 'n' to requested value  set - either 0 or 1     
* Arguments:   bit_arr_ty*  to requested array, index is the requested bit spot in the array, set is either 0 or 1 values.  
* Return value:    bit_arr_ty*   
* Notes: undefined behaviour if index is smaller than 0 or larger than bit count in the array  , set - 0 == false, else == true        
*******************************************************************************/
bit_arr_ty BitArraySetBit(bit_arr_ty bit_array, size_t index, char set); 


/*******************************************************************************
* Function:  change the string representing the bolean values in the bit array       
* Arguments: bit_arr_ty*  to requested array, char* to intented string         
* Return value:     char*  
* Notes: 	dest must be big enough to contain all bits      
*******************************************************************************/
char *BitArrayToString(bit_arr_ty bit_array, char *dest); 


/*******************************************************************************
* Function: rotate the bit array n times to the right         
* Arguments:         bit_arr_ty*  to requested array, n is the number of rotations   
* Return value:    bit_arr_ty*   
* Notes: 	       
*******************************************************************************/
bit_arr_ty BitArrayRotR(bit_arr_ty bit_array, size_t n); 


/*******************************************************************************
* Function:  rotate the bit array n times to the left        
* Arguments:       bit_arr_ty*  to requested array, n is the number of rotations     
* Return value:    bit_arr_ty*   
* Notes: 	        
*******************************************************************************/
bit_arr_ty BitArrayRotL(bit_arr_ty bit_array, size_t n); 


/*******************************************************************************
* Function:         counts all on bits (valued 1)     
* Arguments:  bit_arr_ty*  to requested array,         
* Return value: unsigned char representing number of set bits on    
* Notes: 	        
*******************************************************************************/
size_t BitArrayCountOn(bit_arr_ty bit_array); 


/*******************************************************************************
* Function:    counts all off bits (valued 0)      
* Arguments: bit_arr_ty*  to requested array,          
* Return value: unsigned char representing number of set bits off    
* Notes: 	        
*******************************************************************************/
size_t  BitArrayCountOff(bit_arr_ty bit_array); 


/*******************************************************************************
* Function: returns the bit array in a reverse order (the far ri 0100 mirrored == 0010  .       
* Arguments:  bit_arr_ty*  to requested array,         
* Return value:  bit_arr_ty*     
* Notes: 	        
*******************************************************************************/
bit_arr_ty BitArrayMirror(bit_arr_ty bit_array); 


/*******************************************************************************
* Function: changes the bit in the requested index to it's opposite value.
* Arguments:  bit_arr_ty*  to requested array,   index is the requested bit spot in the array,      
* Return value: bit_arr_ty*    
* Notes: undefined behaviour if index is smaller than 0 or larger than bit count in the array      	        
*******************************************************************************/
bit_arr_ty BitArrayFlipBit(bit_arr_ty bit_array, size_t index); 



/*******************************************************************************
* Function:  returns value in the requested index
* Arguments:  bit_arr_ty*  to requested array,   index is the requested bit spot in the array       
* Return value: 0 or 1    
* Notes: 	undefined behaviour if index is smaller than 0 or larger than bit count in the array     
*******************************************************************************/
size_t BitArrayGetVal(bit_arr_ty bit_array, size_t index); 


/*******************************************************************************
* Function:  initiates the LUT for mirror
* Arguments:  bit_arr_ty*  to requested array,     
* Return value:    
* Notes: 
*******************************************************************************/
void InitLutMirr();


/*******************************************************************************
* Function:  initiates the LUT for mirror
* Arguments:  bit_arr_ty*  to requested array,     
* Return value:    
* Notes: 
*******************************************************************************/
bit_arr_ty BitArrayMirrorII(bit_arr_ty bit_array);


void InitLutCount(short* lutII);

short BitArrayCountOnII(bit_arr_ty bit_array);

#endif /* __BIT_ARRAY_H__ */
