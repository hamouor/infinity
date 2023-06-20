#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
#include <ctype.h> /*tolower*/

#include "ws3.h"

void rowSum(int arr[3][3], int m, int n, int *res)      
/*here will come pseudo code*/
{
	int i = 0, j = 0;
	int rsum = 0;	
 	for ( ; i < m; i++)
  	{
  	        rsum = 0;
  		for (j = 0; j < n; j++)
  		{
  			rsum = rsum + arr[i][j];  			
		}
		*(res + i) = rsum;
    	}
}

int Josh(int num)
/*here will come pseudo code*/
{
	int *z = calloc(sizeof(num), num);
	int dead = 0;
	int i = 1;
	int killed = 0;
	int skipped = 0;
	
	while (dead < (num - 1))
	{
		skipped = 0;
		killed = 0;
		
		while (killed == 0)
		{
			if (*(z+i) == 0)
			{
				dead += 1;
				*(z + i) = 1;
				killed = 1;
				i += 1;
			}
			
			else
			{
				i += 1;
			}
			
			if(i == num)
			{
				i = 0;
			}
		}
		
		while (skipped == 0)
		{
			if (*(z + i) == 0)
			{
				skipped = 1;
				i += 1;
			
			}
			else
			{
				i += 1;
			}
			if(i == num)
			{
				i = 0;
			}
		}
	}
	free(z);
	return (i);			
}

int josephus(int n, int k)
/*here will come pseudo code*/
{
    if (n == 1)
        return 1;
    else
        /* The position returned by josephus(n - 1, k)
        is adjusted because the recursive call
        josephus(n - 1, k) considers the
        original position k % n + 1 as position 1 */
        return (josephus(n - 1, k) + k - 1) % n + 1;
}

void DataType()
/*here will come pseudo code*/
{
    char c = 0;
    signed char sc = 0;
    unsigned char uc = 0;
    /*short short int ssi1 = 0;*/
    signed short ss = 0;
    signed short int ssi = 0;
    unsigned short us = 0;
    unsigned short int usi = 0;
    int i = 0;
    signed int si = 0;
    unsigned u = 0;
    unsigned int ui = 0;
    long l = 0;
    long int li = 0;
    signed long sl = 0;
    signed long int sli = 0;
    unsigned long ul = 0;
    unsigned long int uli = 0;
    /*long long ll = 0;*/
    /*long long int lli = 0;*/             /*hides all long long - not supported by c90*/
    /*signed long long sll = 0;
    signed long long int slli = 0;
    unsigned long long ull = 0;
    unsigned long long int ulli = 0;*/
    float f = 0;
    double d = 0;
    long double ld = 0;
    printf("\n char= %ld", sizeof(c));
    printf("\n signed char= %ld",  sizeof(sc));
    printf("\n unsigned char= %ld",  sizeof(uc));
    /*printf("\n short short int= %ld",  sizeof(ssi1));*/ 
    printf("\n signed short= %ld",  sizeof(ss));
    printf("\n signed short int= %ld",  sizeof(ssi));
    printf("\n unsigned short= %ld",  sizeof(us));
    printf("\n unsigned short int= %ld",  sizeof(usi));
    printf("\n int= %ld",  sizeof(i));
    printf("\n signed int= %ld",  sizeof(si));
    printf("\n unsigned= %ld",  sizeof(u));
    printf("\n unsigned int= %ld",  sizeof(ui));
    printf("\n long= %ld",  sizeof(l));
    printf("\n long int= %ld",  sizeof(li));
    printf("\n signed long= %ld", sizeof(sl));
    printf("\n signed long int= %ld",  sizeof(sli));
    printf("\n unsigned long= %ld",  sizeof(ul));
    printf("\n unsigned long int= %ld",  sizeof(uli));
    /*printf("\n long long= %ld",  sizeof(ll));
    printf("\n long long int= %ld",  sizeof(lli));
    printf("\n signed long long= %ld",  sizeof(sll));
    printf("\n signed long long int= %ld",  sizeof(slli));*/
    printf("\n float= %ld",  sizeof(f));
    printf("\n double= %ld",  sizeof(d));
    printf("\n long double= %ld",  sizeof(ld));
}

void PrintEnvp(int argc, char **argv, char **envp)
/*here will come pseudo code*/
{
    char **env = envp;
    char *myEnv = *env;
    int i = 0;

    for (env; *env != 0; ++env)
    {
        myEnv = *env;

        for(i = 0; *(myEnv + i) != '\0' ; ++i)
        {
            *(myEnv + i) = tolower(*(myEnv + i));
        }

        printf("%s\n", myEnv);
    }

}


