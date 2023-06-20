#ifndef __WS6_H__
#define __WS6_H__

/*pushes the binary representation of x, y zeros to the right*/
long Pow2(unsigned int x, unsigned int y);

/*checks n to be a power of 2. return 0 if true, 1 if false using loop*/
int IsPow2loop(unsigned int n);

/*/*checks n to be a power of 2. return 0 if true, 1 if false without loop*/
int IsPow2(unsigned int n);

/*adds 1 to n*/
unsigned int AddOnez(unsigned int n);

/*will peint only the numbers with three ones in their binary representation - requires the len of the arrays*/
void OnlyThree(unsigned int* n, int len);

/*mirroring the binary representation of int by 8 bits using a loop*/
unsigned int ByteMirrorloop(unsigned int n);

/*mirroring the binary representation of int by 8 bits. no loop*/
unsigned int ByteMirror(unsigned int n);

/*checks the second and sixth bit, if both are on, returns 0. else returns number*/
int SecSixOn(unsigned char n);

/*checks the second and sixth bit, if at least one is on, returns 0. else returns number*/
int SecOrSixOn(unsigned char n);

/*takes an unsigned char and returns the int represented by the swapped 2nd and fifth bits*/
int SwapThirdFifth(unsigned char n);

/*takes an unsigned int and returns the the closest number smaller that devidable by 16*/
int ClosestSixteen(unsigned int n);

/*returns the number of set bits in n using loop*/
int SetBitsloop(unsigned int n);

/*returns the number of set bits in n no loop*/
int SetBits(unsigned int n);

/*prints the bits in n*/
void PrintFloatBits(float n);

/*for the milionth time, swaps two variables*/
void SwapVars(unsigned int* x, unsigned int* y);

#endif
