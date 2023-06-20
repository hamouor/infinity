#include<stdio.h>

int Flip(int n);

float Powr(int n);

void Swape(int *num1, int *num2);

int main(){
	int num_fl = 12345;
	int num_sw1 = 15;
	int num_sw2 = 16;
	int power = 3;
	
	PrintHex();
	printf("\noriginal num %d\nflipped num %d",num_fl, Flip(num_fl));
	printf("\n ten to the power of %d is %f\n", power, Powr(power));
	printf("\n before swap %d, %d\n", num_sw1, num_sw2);
	Swape(&num_sw1, &num_sw2);
	printf("\n  after swap %d, %d\n", num_sw1, num_sw2);
	return 0;
}
	
	
int PrintHex()
{
	printf("\x22\x48\x45\x4C\x4C\x4F\x20\x57\x4F\x52\x4C\x44\x22");
	return 0;
}

int Flip(int n){
	int dig;
	int res=0;
	while (n > 0){
		dig = n % 10; /*get last digit of n*/
		res = res * 10 + dig; /*add dig as new digit in res*/
		n = n / 10; /*get rid of last digit of n*/
		}
	return res;
	}

void Swape(int *num1, int *num2){
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	}

float Powr(int n){
	int i;
	float res;
	float oper;
	oper = 10.0;
	res = 1.0; /*result initialized to 1*/
	
/*check for negative power*/
	if (n<0){
		n=-n;
		oper = 0.1;
		}

	for (i=0; i<n; i++){
		res=res*oper;
	}	
	return res;
}

