/* look for subsequent indices that produce a positive sum and set them as initial result. add foloowing indices values as long as overall result remains positive and compare to initial result for indices result value*/
typedef struct result
{
	int st;
	int en;
	int sum;
}result

void SubArr(int *arra, int len);

void SubArr(int *arra, int len)
{
	int i = 0, j = 0;
	result resulto = {0,0,0};
	int arr[len][len] = {0};
	for(i = 0; i<len; i++)
	{
		for(j=0; j<=i; j++)
		{
			if(i > 0)
			{
				arr[i][j] = arr[i-1][j] + *(arra+i);
				if (arr[i][j] > max)
				{
					resulto = {i,j,arr[i][j]};
					max = arr[i][j];
				}
			}
			else
			{
				arr[i][j] = *(arra + i);
			}
		}
	}
}

void SubArrII(int *arra, int len)
{
    int max_so_far = INT_MIN, max_ending_here = 0;
 
    for (int i = 0; i < size; i++)
    {
        max_ending_here = max_ending_here + a[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
 
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}
