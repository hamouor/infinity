int * Bursa(int* prices, int daytime)
{
	int *best = (int*)malloc(3*sizeof(int));
	int i = 1;
	int *curr_buy = prices;
	int *curr_sell = prices;
	int curr_record = 0;
	int *challanger = prices;
	for(; i < daytime; ++i)
	{
		if(*(prices + i) < *challanger)
		{
			challanger = prices + i;
		}
		if(*(prices + i) - *challanger > curr record)
		{
			curr_buy = challanger;
			curr_sell = prices + i;
			curr_record = *(prices + i) - *challanger;
		}
	}
	*best = curr_buy - prices;
	*(best + 1) = curr_sell - prices;
	*(best + 2) = record;
	return best;
}
