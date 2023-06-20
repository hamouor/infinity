#include<stddef.h>

int Missing(int* a, size_t N)
{
    int sum = 0, sum_arr = 0, fact_actual = 1, fact_arr = 1, i = 1;

    sum = N * (1 + N) / 2;
    
    for(; i <= N; ++i)
    {
        fact_actual *= i;
        fact_arr *= *(a + i - 1);
        sum_arr += *(a + i - 1);
    }

    return (sum_arr - sum)/((fact_arr / fact_actual) - 1);
}

/*two equations with two variables. one is the sum of the array, the other is the factorial
manipulate the equations to recieve the vars*/