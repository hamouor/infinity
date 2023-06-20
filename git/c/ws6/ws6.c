#include "ws6.h"
#include<stdio.h> /*printf*/

long Pow2(unsigned int x, unsigned int y)
{
	x = x << y; /*equals x*(2^y)*/
	return x;
}

int IsPow2loop(unsigned int n)
{
	int num_of_ones = 0; /*will indicate an occurance of one in the binary representation of n*/
	while (0 == num_of_ones) /*extracts the last digit of n and checks if its 1*/
	{
		num_of_ones = num_of_ones + (n & 1); 
		n = n >> 1;
	}
	if (n > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int IsPow2(unsigned int n)
{
	if(0 == (n & (n - 1)))/*make the first occurance of 1 to 0 and all the zeroz that came before are now one. if the original number and this changed one have no common digits - true*/
	{
		return 0;
	}
	return 1;
}

unsigned int AddOnez(unsigned int n)
{
	int ones_counter = 0;/*will count how many ones in a row are from the right*/
	while (1)/*will find the first occurance of zero, change it to one and all ones that came before are now zero*/
	{
		if (1 == (n & 1))
		{
			++ones_counter;
			n = n >> 1;
		}
		else
		{
			n = n | 1;
			n = n << ones_counter;
			break;
		}
	}
	return n;
}

void OnlyThree(unsigned int* n, int len)
{
	int ones_counter = 0; /*will count how many ones in the number*/
	unsigned int holder = 0;
	for (; len > 0; --len)
	{
		holder = *(n + len);
		while (0 < holder)
		{
			if((holder & 1) == 1)
			{
				++ones_counter;
				holder = holder >> 1;
			}
			else
			{
				holder = holder >> 1;
			}
		}
		if (ones_counter == 3)
		{
			printf("%d\n", *(n + len));
		}
	}
}

unsigned int ByteMirrorloop(unsigned int n)
{
	int i = 0;
	unsigned int mirrored = 0;
	for(; i < 8; i++)
	{
		if((n & 1) == 1)
		{
			mirrored+=1;

		}
		if (i==7)
		{
			return mirrored;
		}
		n = n >> 1;
		mirrored = mirrored << 1;
	}
	return 1;
}

unsigned int ByteMirror(unsigned int n)
{
	n = ((n & 240) >> 4) | ((n & 15) << 4);/*240 is 11110000. 15 is 00001111 ---- swaping between the 4 leftmost to the 4 rightmost bits*/
	n = ((n & 204) >> 2) | ((n & 51) << 2);/*11001100. 00110011---- swapping between each pair of bits to its neigbor*/
	n = ((n & 170) >> 1) | ((n & 85) << 1);/*10101010. 01010101 ---- swapping each bit and its neighbo*/ /*these magic binarys allow us to pick out a specific bit or bits and work on them indvidually*/
	return n; 
}

int SecSixOn(unsigned char n)
{
	return (((n & 34) / 34)) ; /*00100010*/
}

int SecOrSixOn(unsigned char n)
{
	return (((n & 34) / 34) | ((n & 32) / 32) | ((n & 2) / 2));
	
}

int SwapThirdFifth(unsigned char n)
{
	return (((n & 16) >> 2 | (n & 253)) | ((n & 4) << 2 | (n & 239)));
}

int ClosestSixteen(unsigned int n)
{
	return (n & 240);
}

int SetBitsloop(unsigned int n)
{
	int counter = 0;
	while (n > 0)
	{
		counter = (n & 1);
		n = n >> 1;
	}
	return counter;
}

int SetBits(unsigned int n)
{
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F);
	n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF);
	n = (n & 0x0000FFFF) + ((n >> 16)& 0x0000FFFF);
	return n;
}

void PrintFloatBits(float n)
{
	unsigned int casted;
	casted = *(unsigned int*)&n;
	while(casted != 0)
	{
		printf("%d", (casted & 1));
		casted = casted >> 1;
	}
	printf("\n");
}	

void SwapVars(unsigned int* x, unsigned int* y)
{
	*x = *x ^ *y;
	*y = *y ^ *x;
	*x = *x ^ *y;
}
void InitLutCount(short* lutII)
{
	static flag = 0;
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

short SetBits(int n, short* dest)
{
	int i = 0;
	short count = 0;
	for(; i < 8; ++i)
	{
		count += (n & 1);
		n >>= 1;
	}
	*dest count;
}

size_t BitArrayCountOnII(bit_arr_ty bit_array)
{
	size_t numofon = 0;
	int i = 0;
	char* byte = (char*)&bit_array;
	for(; i < 8; ++i)
	{
		numofon += lutII[(int)*(byte+i)];
	}
	return numofon;
}
