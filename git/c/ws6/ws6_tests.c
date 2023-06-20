#include "ws6.h"
#include "ws6.c"
#include<stdio.h> /*printf*/
#include<math.h>

int main()
{
	unsigned int x = 15;
	unsigned int y = 3;
	unsigned int z = 0;
	float k = 0.5550221;
	z = Pow2(x,y);
	printf("pow2%d\n",z);
	z = IsPow2loop(x);
	printf("ispow%d\n",z);
	z = IsPow2(x);
	printf("ispow%d\n",z);
	z = AddOnez(x);
	printf("addones%d\n",z);
	z = ByteMirrorloop(x);
	printf("mirror%d\n",z);
	z =ByteMirror(x);
	printf("mirrornoloop%d\n",z);		
	z = SecSixOn((unsigned char) x);
	printf("secsix%d\n",z);
	z = SecOrSixOn((unsigned char) x);
	printf("secorsix%d\n",z);	
	z = SwapThirdFifth((unsigned char) x);
	printf("swap%d\n",z);
	z = ClosestSixteen(x);
	printf("closest%d\n",z);
	z = SetBitsloop(x);
	printf("set%d\n",z);
	PrintFloatBits(k);
	SwapVars(&x, &y);
	printf("swapped%d%d",x,y);
	return 0;
}

