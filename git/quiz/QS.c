#include<stdio.h>

int Pivot(int *arr, size_t len);
void QS(int*arr, size_t len);
void Swap(int* a, int* b);

int main()
{
    int arr[10] = {9,8,7,6,5,4,3,2,1,0};
    int i = 0;

    QS(arr, 10);

    for(; i < 10; ++i)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}




void QS(int*arr, size_t len)
{
    int piv = 0;

    piv = Pivot(arr, len);

    if(piv > 0)
    {
        QS(arr, piv);
    }
    if(piv < len - 1)
    {
        QS(arr + piv + 1, len - (piv + 1));
    }
}

int Pivot(int *arr, size_t len)
{
    int i = 0, j = len - 2, piv = 0;

    if(len < 2)
    {
        return 0;
    }

    piv = arr[len - 1];
    
    while(j >= i)
    {
        if(arr[i] > piv)
        {
            Swap(arr + i, arr + j);
            --j;
        }
        else
        {
            ++i;
        }
    }

    Swap(arr + j + 1, arr + len - 1);
    return(j+1);
}

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}