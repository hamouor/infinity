int BitCouples(unsigned int n)
{
	int flag = 0;
	int counter = 0;
	while (n > 0)
	{
		if(flag > 0)
		{
			if( n & 1 == 1)
			{
				counter+=1
				n >>= n;
			}
			else
			{
				flag = 0;
				n >>= n;
			}
		}
		else if  (n & 1 == 1)
		{
			flag = 1;
			n >>= n;
		}
		
	}
	return counter;
}

void SwapI(int* num1, int* num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}

void SwapII(int* num1, int* num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num2 ^ *num1;
	*num1 = *num1 ^ *num2;
}

void SwapIII(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

int SetBitsCount(long int n)
{
	int counter = 0;
	while( n > 0 )
	{
		n = (n - 1) & n;
		counter += 1;
	}
}

/*  add 1 to the left*/
/*arithmetic, since a signed value will retain its sign through the operation the shifting takes into consideration weather to pad with ones or zeros*/
