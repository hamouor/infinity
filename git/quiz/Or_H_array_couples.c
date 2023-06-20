void ArrayCouples(int *arr, size_t size)
{
    int i = 0, b = 0;

    for(; i < size; ++i)
    {
        b=b^*(arr+i);
    }

    if (b != 0)
    {
        printf("%d\n", b);
    }
}