#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h> /* size_t*/


enum sort_flag {UNSORTED = 1, SORTED = 0}; 
enum nums {ERROR = -999, ARR_SIZE = 5000}; 

static void TestBubbleSort(void);
static void TestInsertionSort(void);
static void TestSelectionSort(void);
static void TestCountingSort(void);
static int TestSortedArray(int arr[], int arr_size);
static int ComparFunc(const void *num1, const void *num2);
static void PrintArray(int arr[], size_t arr_size);


static void Swap(int* arr, size_t index1, size_t index2);

static int FindIndexMax(int* arr, size_t N);

static int FindIndexMin(int* arr, size_t N);

static void PrintArr(int* arr, size_t N);

void BubbleSort(int* arr, size_t N)
{
    int swaps = 1, i = 0;

    while(swaps)
    {
        swaps = 0;
        for(i = 0; i < N - 1; ++i)
        {
            if(*(arr + i) > *(arr + i + 1))
            {
                swaps = 1;
                Swap(arr, i, i+1);
            }
        }
    }
}

void SelectionSort(int* arr, size_t N)
{
    size_t i = 0, j = 0;

    for(; i < (N - 1); ++i)
    {
        j = FindIndexMin(arr + i, N - i);
        Swap(arr, i, i + j);
    }
}

void InsertionSort(int* arr, size_t N)
{
    int i, key, j;/*TOM: initialize*/
    for (i = 1; i < N; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int CountingSort(int* arr, size_t N)
{
    int min = 0, max = 0, *support = NULL, counter = 0, i = 0;

    min = *(arr + FindIndexMin(arr, N));
    max = *(arr + FindIndexMax(arr, N));

    support = (int*)calloc(max - min + 1, sizeof(int));
    
    if(!support)
    {
        return 1;
    }

    for(; i < N; ++i)
    {
        ++*(support + *(arr + i) - min);
    }

    for(i = 0; i < (max - min + 1); ++i)
    {
        while(*(support + i) > 0)
        {
            --*(support + i);
            *(arr + counter) = i + min;
            ++counter;
        }
    }

    free(support);/*LITAL:support=NULL*/
    return 0;
}

void RadixSort(int* arr, size_t N)
{
    int max = 0, digs = 0;

    /*find max*/
    max = *(arr + FindIndexMax(arr, N));
    
    /*calculate number of digits in max*/
    while(max > 0)
    {
        max /= 10;
        digs +=1;
    }



}

static int FindIndexMin(int* arr, size_t N)
{
    size_t i = 1, temp = 0;

    for(; i < N; ++i)
    {
        if (*(arr + i) < *(arr + temp))
        {
            temp = i;
        }
    }
    return temp;
}

static int FindIndexMax(int* arr, size_t N)
{
    size_t i = 1, temp = 0;

    for(; i < N; ++i)
    {
        if (*(arr + i) > *(arr + temp))
        {
            temp = i;
        }
    }
    return temp;
}

static void Swap(int* arr, size_t index1, size_t index2)
{
    if(index1 != index2)
    {
        *(arr + index1) += *(arr + index2);
        *(arr + index2) = *(arr + index1) - *(arr + index2);
        *(arr + index1) -= *(arr + index2);
    }
}

static void RandomizeArray(int arr[], int size)
{
    size_t i = 0;
    srand(time(NULL));
    for(i = 0; i < size; ++i)
    {
        arr[i] = rand() % 5000;
    }
}

static int IsInOrder(int* arr, size_t N)
{
    int i = 0;

    for(; i < (N - 1); ++i)
    {
        if(*(arr + i) > *(arr + i + 1))
        {
            printf("%d", i);
            return 0;
        }
    }
    return 1;
}

/*int main()
{
    int* arr = NULL;

    arr = (int*)malloc(5000 * sizeof(int));

    RandomizeArray(arr, 5000);

    SelectionSort(arr, 5000);

    if (!IsInOrder(arr, 5000))
    {
        printf("selection failed\n");
    }

    RandomizeArray(arr, 5000);
    
    BubbleSort(arr, 5000);

    if (!IsInOrder(arr, 5000))
    {
        printf("bubble failed\n");
    }

    RandomizeArray(arr, 5000);

    InsertionSort(arr, 5000);
    
    if (!IsInOrder(arr, 5000))
    {
        printf("insertion failed\n");
    }

    RandomizeArray(arr, 5000);

    CountingSort(arr, 5000);
    
    if (!IsInOrder(arr, 5000))
    {
        printf("counting failed\n");
    }
    free(arr);

    return 0;

}*/

void PrintArr(int* arr, size_t N)
{
    size_t i = 0;
    
    for (; i < N; ++i)
    {
        printf("%d", *(arr + i));
    }
}

int main(void)
{

	TestBubbleSort();
	TestInsertionSort();
	TestSelectionSort();
	TestCountingSort();
	
	return 0;
}



static void TestBubbleSort(void)
{
	int array[ARR_SIZE];
	int test_array[ARR_SIZE];
	size_t arr_size = ARR_SIZE;
	size_t i = 0;
	int sort_check = ERROR;
	
	clock_t start_bubble_t = 0, end_bubble_t = 0, start_qsort_t = 0, end_qsort_t = 0;
	double total_bubble_t = 0, total_qsort_t = 0;
	
	srand(time(0));

	for(i = 0; arr_size > i; ++i)
	{
		array[i] = rand() % arr_size;
		test_array[i] = rand() % arr_size;
	}
	
	start_bubble_t = clock();
	
	BubbleSort(array, arr_size);

	end_bubble_t = clock();
	
	total_bubble_t = (double)(end_bubble_t - start_bubble_t) / CLOCKS_PER_SEC;
	
	sort_check = TestSortedArray(array, arr_size);
	
	if(sort_check != SORTED)
	{
		printf("Problem with BubbleSort\n");
	}
	
	/* test with qsort */
	start_qsort_t = clock();
	
	qsort((void *)&test_array[0], arr_size, sizeof(int), &ComparFunc);

	end_qsort_t = clock();
	
	total_qsort_t = (double)(end_qsort_t - start_qsort_t) / CLOCKS_PER_SEC;
	
	
	/*printf("Bubble sort is shorter than qsort\n");*/
	printf("total time for bubble sort is %f and for qsort is %f\n", total_bubble_t, total_qsort_t);
}


static void TestInsertionSort(void)
{
	int array[ARR_SIZE];
	int test_array[ARR_SIZE];
	size_t arr_size = ARR_SIZE;
	size_t i = 0;
	int sort_check = ERROR;
	
	clock_t start_inser_t = 0, end_inser_t = 0, start_qsort_t = 0, end_qsort_t = 0;
	double total_inser_t = 0, total_qsort_t = 0;
	
	srand(time(0));

	for(i = 0; arr_size > i; ++i)
	{
		array[i] = rand() % arr_size;
		test_array[i] = rand() % arr_size;
	}
	
	/*PrintArray(array, arr_size);*/
		
	start_inser_t = clock();
	
	InsertionSort(array, arr_size);

	end_inser_t = clock();
	
	total_inser_t = (double)(end_inser_t - start_inser_t) / CLOCKS_PER_SEC;
	
	sort_check = TestSortedArray(array, arr_size);
	
	if(sort_check != SORTED)
	{
		printf("Problem with InsertionSort\n");
	}
	
	/* test with qsort */
	start_qsort_t = clock();
	
	qsort((void *)&test_array[0], arr_size, sizeof(int), &ComparFunc);

	end_qsort_t = clock();
	
	total_qsort_t = (double)(end_qsort_t - start_qsort_t) / CLOCKS_PER_SEC;
	
	/*PrintArray(array, arr_size);*/
	/*printf("Bubble sort is shorter than qsort\n");*/
	printf("total time for Insertion sort is %f and for qsort is %f\n", total_inser_t, total_qsort_t);
}



static void TestSelectionSort(void)
{
	int array[ARR_SIZE];
	int test_array[ARR_SIZE];
	size_t arr_size = ARR_SIZE;
	size_t i = 0;
	int sort_check = ERROR;
	
	clock_t start_selec_t = 0, end_selec_t = 0, start_qsort_t = 0, end_qsort_t = 0;
	double total_selec_t = 0, total_qsort_t = 0;
	
	srand(time(0));

	for(i = 0; arr_size > i; ++i)
	{
		array[i] = rand() % arr_size;
		test_array[i] = rand() % arr_size;
	}
	
	/*PrintArray(array, arr_size);*/
		
	start_selec_t = clock();
	
	SelectionSort(array, arr_size);

	end_selec_t = clock();
	
	total_selec_t = (double)(end_selec_t - start_selec_t) / CLOCKS_PER_SEC;
	
	sort_check = TestSortedArray(array, arr_size);
	
	if(sort_check != SORTED)
	{
		printf("Problem with SelectionSort\n");
	}
	
	/* test with qsort */
	start_qsort_t = clock();
	
	qsort((void *)&test_array[0], arr_size, sizeof(int), &ComparFunc);

	end_qsort_t = clock();
	
	total_qsort_t = (double)(end_qsort_t - start_qsort_t) / CLOCKS_PER_SEC;
	
	/*PrintArray(array, arr_size);*/
	/*printf("Bubble sort is shorter than qsort\n");*/
	printf("total time for Selection sort is %f and for qsort is %f\n", total_selec_t, total_qsort_t);
}



static void TestCountingSort(void)
{
	int array[ARR_SIZE];
	int test_array[ARR_SIZE];
	int arr_size = ARR_SIZE;
	int i = 0;
	int sort_check = ERROR;
	
	clock_t start_count_t = 0, end_count_t = 0, start_qsort_t = 0, end_qsort_t = 0;
	double total_count_t = 0, total_qsort_t = 0;
	
	srand(time(0));

	for(i = 0; arr_size > i; ++i)
	{
		array[i] = rand() % arr_size;
		test_array[i] = rand() % 100;
	}
	
	/*PrintArray(array, arr_size);*/
		
	start_count_t = clock();
	
	CountingSort(array, arr_size);

	end_count_t = clock();
	
	total_count_t = (double)(end_count_t - start_count_t) / CLOCKS_PER_SEC;
	
	sort_check = TestSortedArray(array, arr_size);
	
	if(sort_check != SORTED)
	{
		printf("Problem with InsertionSort\n");
	}
	
	/* test with qsort */
	start_qsort_t = clock();
	
	qsort((void *)&test_array[0], (size_t)arr_size, sizeof(int), &ComparFunc);

	end_qsort_t = clock();
	
	total_qsort_t = (double)(end_qsort_t - start_qsort_t) / CLOCKS_PER_SEC;
	
	/*PrintArray(array, arr_size);*/
	/*printf("Bubble sort is shorter than qsort\n");*/
	printf("total time for counting sort is %f and for qsort is %f\n", total_count_t, total_qsort_t);
}

static int ComparFunc(const void *num1, const void *num2)
{	
	return (*(int *)num1 - *(int *)num2);
}

static int TestSortedArray(int arr[], int arr_size)
{
	int i = 0;
	int unsorted = 0;
	for(i = 0; arr_size - 1 > i; ++i)
	{
		if(arr[i] > arr[i + 1])
		{
			++unsorted;
		}
	}
	
	if(0 < unsorted)
	{
		printf("array is not sorted, found %d mixed numbers\n", unsorted);
		return UNSORTED;
	} 
	
	return SORTED;
}


static void PrintArray(int arr[], size_t arr_size)
{
	size_t i = 0;
	
	for(i = 0; arr_size > i; ++i)
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}




