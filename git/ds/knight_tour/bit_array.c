#include <limits.h> 			/*CHAR_BIT*/
#include <stddef.h> 			/* size_t */
#include <stdint.h>  			/* SIZE_MAX */
#include<stdlib.h>
#include "bit_array.h"

const char bitarraysize = sizeof(bit_arr_ty) * CHAR_BIT; 

void ByteMirr(int i, char* dest);
void SetBits(int n, short* dest);

bit_arr_ty BitArraySetAll(void)
{
	/*bit_arr_ty allon = 0;*/
	return (~(bit_arr_ty)1);
}

bit_arr_ty BitArrayResetAll(void)
{
	bit_arr_ty alloff = 0;
	return alloff;
}


bit_arr_ty BitArraySetOn(bit_arr_ty bit_array, size_t index)
{
	bit_arr_ty mask = 1;
	mask <<= index;
	bit_array |= mask;
	return bit_array;
}


bit_arr_ty BitArraySetOff(bit_arr_ty bit_array, size_t index) 
{
	bit_arr_ty mask = 1;
	mask <<= index;
	bit_array &= (~mask);
	return bit_array;
}


bit_arr_ty BitArraySetBit(bit_arr_ty bit_array, size_t index, char set)
{
	if (0 == set)
	{
		bit_array = BitArraySetOff(bit_array, index);
	}
	else
	{
		bit_array = BitArraySetOn(bit_array, index);
	}
	return bit_array;
}


char *BitArrayToString(bit_arr_ty bit_array, char *dest)
{
	int i = bitarraysize;
	*(dest + i) = '\0';
	for(--i; 0 <= i; --i)
	{
		*(dest+i) = (bit_array & 1) + '0';
		bit_array >>= 1;
	}
	return dest;
}


bit_arr_ty BitArrayRotR(bit_arr_ty bit_array, size_t n)
{
	bit_array = (bit_array >> n) | (bit_array << (bitarraysize - n));
	return bit_array;
}


bit_arr_ty BitArrayRotL(bit_arr_ty bit_array, size_t n)
{
	bit_array = (bit_array << n) | (bit_array >> (bitarraysize - n));
	return bit_array;
}


size_t BitArrayCountOn(bit_arr_ty bit_array)
{
	size_t numofon = 0;
	while(bit_array > 0)
	{
		bit_array = (bit_array - 1) & bit_array;
		numofon += 1;
	}
	return numofon;
}


size_t  BitArrayCountOff(bit_arr_ty bit_array)
{
	size_t numofoff = bitarraysize;
	numofoff -= BitArrayCountOn(bit_array);
	return numofoff;
}


bit_arr_ty BitArrayMirror(bit_arr_ty bit_array)
{
	bit_arr_ty buff = 0;
	int i = bitarraysize;
	for (; i > 0; --i)
	{
		buff <<= 1;
		buff += (bit_array & 1);
		bit_array >>= 1;
	
	}
	return buff;
}


bit_arr_ty BitArrayFlipBit(bit_arr_ty bit_array, size_t index)
{
	bit_array ^= (1 << index);
	return bit_array;
}


size_t BitArrayGetVal(bit_arr_ty bit_array, size_t index)
{
	bit_arr_ty mask = 1 << index;
	mask &= bit_array;
	mask >>= index;
	return mask;
}

void InitLutMirr()
{
	static int flag = 0;
	int max = 255;
	if (0 == flag)
	{
		for (; max >= 0; --max)
		{
			ByteMirr(max, (lut+max));
		}
		flag = 1;
	}
}
void ByteMirr(int i, char* dest)
{
	int j = 0, k = 0;
	for (;j < 8; ++j)
	{
		k <<= 1;
		k += (i & 1);
		i >>= 1;
	}
	*dest = (char)k;
}

bit_arr_ty BitArrayMirrorII(bit_arr_ty bit_array)
{
	bit_arr_ty buff = 0;
	int i = 0;
	char* byte = (char*)&bit_array, *buffby = (char*)&buff;
	for(; i < 8; ++i)
	{
		*(buffby + 7 - i) = lut[(int)*(byte+i)];
	}
	return buff;
}

void InitLutCount(short* lutII)
{
	static int flag = 0;
	int max = 255;
	if (0 == flag)
	{
		for (; max >= 0; --max)
		{
			SetBits(max, (lutII+max));
		}
		flag = 1;
	}
}

void SetBits(int n, short* dest)
{
	int i = 0;
	short count = 0;
	for(; i < 8; ++i)
	{
		count += (n & 1);
		n >>= 1;
	}
	*dest = count;
}

short BitArrayCountOnII(bit_arr_ty bit_array)
{
	short numofon = 0;
	int i = 0;
	char* byte = (char*)&bit_array;
	for(; i < 8; ++i)
	{
		numofon += lutII[*(byte+i)];
	}
	return numofon;
}

