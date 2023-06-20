void BinArraySort(int* arr, size_t len)
{
    int *current1 = NULL, *next0 = NULL, len2 = 0;

    current1 = FindNext(arr, len, 1);
    len2 = len - (current1 - arr);
    next0 = FindNext(current1, len2, 0 );
    while (next0 && current1)
    {
        *current1 = 0;
        *next0 = 1;
        current1 = FindNext(current1+1, len2 - 1, 1);
        if (current1)
        {
            len2 = len - (current1 - arr);
            next0 = FindNext(current1, len2, 0 );
        }
    }
}

int* FindNext(int* arr, size_t len, int who)
{
    int* res = arr, i=0;

    while(i < len && res)
    {
        if (*(res + i) == who)
        {
            return res;
        }
        ++i;
    }
    return NULL;
}