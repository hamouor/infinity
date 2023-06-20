#ifndef __WS10_H__
#define __WS10_H__

/*converts num into string. returns pointer to string containing num str must have enough room for num. base 2-36.*/
char *IntToStr(int num, char* str, int base);

/*converts string to int.*/
int StrToInt(const char *str, int base);

/*prints chars that are present only in arr1 and arr2 but not in arr3. recieves the 3 arrays and their respective lengths base 2-36*/
void OnlyInTwo(char* arr1, char* arr2, char* arr3, int len1, int len2, int len3);

/*priints weather your system is big or little endian*/
void BigLitEndi();

#endif
