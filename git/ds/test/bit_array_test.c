#include "bit_array.h"
#include<stdio.h>
#include <stdlib.h>

int main()
{
	bit_arr_ty test = 1, empty = 0, full = 0;
	size_t index = 5;
	char *tostrres = (char*)malloc(8);
	int i = 0;
	
	full = BitArraySetAll();
	printf("%zu\n", full);
	/*printed size_t with all bits on*/
	
	test = BitArrayResetAll();
	printf("%zu\n", test);
	/*printed 0*/
	
	empty = BitArraySetOn(empty, index);
	printf("%zu\n", empty);
	/*printed size_t with bit num test set on*/
	
	test = BitArraySetOff(empty, index);
	printf("%zu\n", test);
	/*should print 0*/
	
	test = full - empty;
	full = BitArraySetBit(full, index, 0);
	printf("%zu\n", full - test);
	/*should pprint 0*/	 	
	tostrres = BitArrayToString(full, tostrres);
	printf("%s\n", tostrres);

	
	printf("%s\n", BitArrayToString(BitArrayRotR(full, index), tostrres));
	printf("%s\n", BitArrayToString(BitArrayRotL(full, index), tostrres));
	printf("%zu\n", BitArrayCountOn(full));
	printf("%zu\n", BitArrayCountOff(full));
	printf("%s\n", BitArrayToString(BitArrayMirror(full), tostrres));
	printf("%s\n", BitArrayToString(BitArrayFlipBit(full, index), tostrres));
	InitLutMirr();
	for(i=0;i<256;++i)
	{
		printf("%c\n",lut[i]);
	}
	printf("%s\n", BitArrayToString(BitArrayMirrorII(full), tostrres));

	InitLutCount(lutII);
	for(i=0;i<256;++i)
	{
		printf("%d\n",lutII[i]);
	}
	printf("%d\n", BitArrayCountOnII(full));

	free(tostrres);	
	return 0;
}
