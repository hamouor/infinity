#include <stdio.h> /*printf*/

#include "ws3.h"

void TestPrintEnvp(int argc, char **argv, char **envp);

int main(int argc, char **argv, char **envp)
{
	int arr[3][3] = {{1,2,3},{2,3,4},{3,4,5}};
	int m=3,n=3;
	int res[3]= {0,0,0};
	int i = 0;
	int num = 19;
	int k = 2;
	rowSum(arr,m,n,res);
	for(; i < m; ++i)
	{
		printf("\n%d\n", *(res+i));
	}
	
	i = Josh(num);
	m = josephus(num,k);
	printf("\n%d,%d\n",i,m);
	DataType();
	PrintEnvp(argc, argv, envp);
	return 0;
	
} 

void TestPrintEnvp(int argc, char **argv, char **envp)
{
    PrintEnvp(argc, argv, envp);

}
