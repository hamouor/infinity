int Find(char* arr, size_t len, char findme)
{
	size_t bita[4] = {0};
	for (; len > 0; --len)
	{
		index = ((int)*(arr + len)) % 64;
		pos = ((int)*(arr + len)) / 64;
		BitArraySetOn(bita[pos], index);
	}
	return (int)BitArrayGetVal(bita[(int)(findme / 64)], (int)(findme % 64); 
}
		
/*algorithm 2: memcopy of N values from the end of the arry to temp. memove...*/		


