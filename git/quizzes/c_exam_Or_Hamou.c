/*Q1*/

int FlipDigitsInNum(int num)
{
	int result = 0;
	while (0 != num)
	{
		result *= 10;
		result += (num%10);
		num /= 10;
	}
	return result;
}

/*Q2*/

/*take 4 bits at a time (devision by 16 of a binary) and translate to hexa.
CE99D8F7*/

/*Q3*/

Garbage

/*Q4*/

unsigned char ByteMirror(unsigned char n)
{
	n = ((n & 240) >> 4) | ((n & 15) << 4);/*240 is 11110000. 15 is 00001111 ---- swaping between the 4 leftmost to the 4 rightmost bits*/
	n = ((n & 204) >> 2) | ((n & 51) << 2);/*11001100. 00110011---- swapping between each pair of bits to its neigbor*/
	n = ((n & 170) >> 1) | ((n & 85) << 1);/*10101010. 01010101 ---- swapping each bit and its neighbo*/ /*these magic binarys allow us to pick out a specific bit or bits and work on them indvidually*/
	return n; 
}

/*by using bitwise operations*/

/*Q5*/

int FlipBit(int val unsigned int n)
{
	n = 1 << n;
	val = val ^ n;
	return val;
}

/*Q6*/

int SetBits(unsigned int n)
{
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F);
	n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF);
	return n;
}

/* summing the on bits in pairs and summing the results in pairs of pairs*/
/*doing the same in shorter sequences*/
/*doing the same in longer sequences*/

/*Q7*/

/*size_t is used for holding indexes and sizes values. */
/*int may contain negative values*/

/*Q8*/

char RotateLeft(char byte, unsigned int nbits)
{
	byte = (byte << nbits) || (byte >> (8 - nbits));
	return byte;
}

/*Q9*/

/* either little vs big endian.*/

/*Q10*/

void SwapPtrs(int **ptr1, int **ptr2)
{
	int *temp = NULL;
	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

/*Q11*/

size_t Strlen(char *str)
{
	size_t res = 0;
	while ('\0' != *str)
	{
		res += 1;
		++str;
	}
	return res;
}


int Strncmp(const char* string1, const char* string2, size_t n)
{
	size_t i = 0;
	
	while(*(string1+i) == *(string2+i) && *(string2+i) != '\0')
	{
		i++;
		if(i == n)
		{
			break;
		}
	}
	return (int)(*(string1+i)-*(string2+i));
}

Char *Strcpy(char *dest, const char *src)
{
	size_t i = 0;
	
	for( ; *(src+i) != '\0'; i++)
	{
		*(dest+i) = *(src+i);
	}
	*(dest+i) = '\0';
	return dest;
}


/*copies a src string to dest string up to n characters*/	
char *Strncpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;
	
	for( ; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return dest;
}

char *Strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';
	return dest;
}

/*Q12*/

unsigned long GetNFibonacciElement(unsigned int n)
{
	if(1 == n)
	{
		return 1;
	}
	else if (0 == n)
	{
		return 0;
	}
	else
	{
		return GetNFibonacciElement(n-1) + GetNFibonacciElement(n-2);
	}
}

/*Q13*/

char *IntToStr(int num, char* str, int base)
{
	int digit = 0, counter = 0;
	char gap = '0';
	while (num > 0)
	{
		digit = num % base;
		num = num / base;
		if (digit > 9)
		{
			digit += 7; /*shift towards alphabetical rep*/
		}
		*(str + counter) = gap + (char)digit;
		counter += 1;
	}
	*(str + counter) = '\0';
	reverse(str);
	return str;
}

void reverse(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = strlen(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}

/*Q14*/

void MultiEight(int* num)
{
	int sign = 1;
	if(*num < 0)
	{
		*num *= -1;
		sign = -11;
	}
	*num = (*num << 3)*sign;
}

/*Q15*/

void SwapI(int* a, int* b)
{
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}

void SwapII(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void SwapIII(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}

/*the first one. it is least vulnerable to input variations*/

/*Q16*/

/* 8, 6, 5, 5, segmentation failt read only*/

/*Q17*/

/*3*/

/*Q18*/

/*
a global variable only accessable within the file where it defined

var whose lifetime does not stop with the the function call

function that has a scope that is limited to its object file

In the C programming language, a static library is a compiled object file containing all symbols required by the main program to operate (functions, variables etc.) as opposed to having to pull in separate entities. Static libraries aren't loaded by the compiler at run-time; only the executable file need be loaded.

A static link is a hard-coded link containing a Web page uniform resource locator (URL) that is permanent or unchangeable. It is the opposite of dynamic link. As a static link is permanent in nature, search engines find such links to be easier to crawl and index, which greatly helps in search engine optimization (SEO).
*/

/*Q19*/
/*in variable declarations 
auto - declaring a local var
register - hints to compiler that a given variable can be put in a register. It's compiler's choice to put it in a register or not
volatile -  It tells the compiler that the value of the variable may change at any time--without any action being taken by the code the compiler finds nearby.
default-The default statement is executed if no case constant-expression value is equal to the value of expression .
extern - used to declare a global variable that is a variable without any memory assigned to it. */

/*Q20*/

/*32*/

/*Q21*/

/* 96
192
*/

/*Q22*/

/*160
192*/

/*Q23*/

/*var
7*/

	
