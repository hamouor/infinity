#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h> 
#include <string.h>

#include"vector.h"

#define NUM_OF_THREADS 1

#define SIZOF_WORD 30

enum{
    SUCCESS,
    FAILURE
};

typedef struct arr
{
    int* original;
    size_t size;
    int* hash;
}arrs;

typedef struct arr1
{
    vector_ty *dict;
    int start;
    size_t size;
    int* hash;
}arrsII;

int mtcs(int* arr, size_t size);
void* CountThread(void* args);
void* CountThreadII(void* args);
int mtcsII(vector_ty* dict, size_t size);
int VtoI(void* val);

int main()
{
    /*int arr[12] = {5, 7, 4, 2, 4, 6, 8, 7, 5, 4, 1, 2};
    int sor[12] = {1, 2, 2, 4, 4, 4, 5, 5, 6, 7, 7, 8};*/
    /*int i = 0;*/
    FILE *dictionary = NULL;
    char line[SIZOF_WORD];
    vector_ty* dict = NULL;

    dict = VectorCreate(SIZOF_WORD, SIZOF_WORD);

    if(!dict)
    {
        return FAILURE;
    }

    dictionary = fopen("/home/or/git/system_programming/multi_thread_CS/messy", "r");

    if(!dictionary)
    {
        VectorDestroy(dict);
        return FAILURE;
    }
    while (EOF != fscanf(dictionary, "%s" ,line ))
    {
        VectorPushBack(dict, (void*)&line);
    }

    VectorShrinkToFitSize(dict);

    if(mtcsII(dict, VectorSize(dict)))
    {
        return FAILURE;
    }

    /*for(i = 0; i < VectorSize(dict); ++i)
    {
        printf("%s\n", (char*)VectorGetAccessToElement(dict, i));
    }*/

    /*mtcs(arr, 12);

    for(i = 0; i < 12; ++i)
    {
        if(arr[i] != sor[i])
        {
            printf("no good\n");
        }
    }*/
    fclose(dictionary);
    VectorDestroy(dict);


    return SUCCESS;
}


int mtcs(int* arr, size_t size) /*positive ints only*/
{
    int max_val = 0;
    size_t i = 0;
    int* hash = NULL;
    int* out = NULL;
    pthread_t id[NUM_OF_THREADS];
    arrs sub_arrs[NUM_OF_THREADS];
    size_t subarray_size = 0;

    for(; i < size; ++i)
    {
        if(arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    hash = (int*)calloc(max_val + 1, sizeof(int));
    if(!hash)
    {
        return FAILURE;
    }
    
    out = (int*)malloc(size * sizeof(int));
    if(!out)
    {
        free(hash);
        return FAILURE;
    }

    
    subarray_size = size / NUM_OF_THREADS;

    for(i = 0; i < NUM_OF_THREADS - 1; ++i)
    {
        sub_arrs[i].original = arr + (i * subarray_size);
        sub_arrs[i].size = subarray_size;
        sub_arrs[i].hash = hash;
        if(!!pthread_create(&id[i], NULL, CountThread, (void*)&sub_arrs[i]))
        {
            free(hash);
            free(out);
            return FAILURE;
        }
    }
    
    sub_arrs[i].original = arr + (i * subarray_size);
    sub_arrs[i].size = size - (i * subarray_size);
    sub_arrs[i].hash = hash;
    if(!!pthread_create(&id[i], NULL, CountThread, (void*)&sub_arrs[i]))
    {
        free(hash);
        free(out);
        return FAILURE;
    }
    
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(id[i], NULL);
    }
        
    for(i = 0; i < max_val; ++i)
    {
        hash[i + 1] += hash[i];
    }

    for(i = size - 1; i >= 0; --i)
    {
        out[hash[arr[i]] - 1]= arr[i];
        --hash[arr[i]];
    }
    
    for(i = 0; i < size; ++i)
    {
        arr[i] = out[i];
    }

    free(out);
    free(hash);
}

void* CountThread(void* args)
{
    arrs* data = NULL;
    int i = 0;
    int* hash, *arr;
    size_t size;

    data = (arrs*)args;

    hash = data->hash;
    arr = data->original;
    size = data->size;

    for(; i < size; ++i)
    {
        __sync_fetch_and_add(&hash[arr[i]], 1);
    }

    return NULL;
}



int mtcsII(vector_ty* dict, size_t size)/*vector containing strings*/
{
    size_t max_val = 0;
    int i = 0, j = 0;
    int* hash[NUM_OF_THREADS];
    vector_ty* out = NULL;
    pthread_t id[NUM_OF_THREADS];
    arrsII sub_arrs[NUM_OF_THREADS];
    size_t subarray_size = 0;

    for(; i < size; ++i)
    {
        if(VtoI(VectorGetAccessToElement(dict, i)) > max_val)
        {
            max_val = VtoI(VectorGetAccessToElement(dict, i));
        }
    }
    
    out = VectorCreate(SIZOF_WORD, size);
    {
        return FAILURE;
    }

    for(i = 0; i < NUM_OF_THREADS; ++i)/*creating hash or count per each thread*/
    {
        hash[i]= (int*)calloc(max_val + 1, sizeof(int));
        if(!hash[i])
        {
            for(++i; i >= 0; --i)
            {
                free(hash[i]);
            }
            VectorDestroy(out);
            return FAILURE;
        }
    }
    
    
    
    subarray_size = size / NUM_OF_THREADS;

    for(i = 0; i < NUM_OF_THREADS - 1; ++i)
    {
        sub_arrs[i].dict = dict;
        sub_arrs[i].start = i * subarray_size;
        sub_arrs[i].size = subarray_size;
        sub_arrs[i].hash = hash[i];
        if(!!pthread_create(&id[i], NULL, CountThreadII, (void*)&sub_arrs[i]))
        {
            for(i = 0; i < NUM_OF_THREADS; ++i)
            {
                free(hash[i]);
            }
            free(out);
            return FAILURE;
        }

    }

    sub_arrs[i].dict = dict;
    sub_arrs[i].start = i * subarray_size;
    sub_arrs[i].size = size - (i * subarray_size);
    sub_arrs[i].hash = hash[i];
    pthread_create(&id[i], NULL, CountThreadII, (void*)&sub_arrs[i]);
    {
        for(i = 0; i < NUM_OF_THREADS; ++i)
        {
           free(hash[i]);
        }
        free(out);
        return FAILURE;
    }
    
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(id[i], NULL);
    }
    
    for(i = 1; i < NUM_OF_THREADS; ++i)
    {
        for(j = 0; j < max_val + 1; ++j)
        {
            hash[0][j] += hash[i][j];
        }
        free(hash[i]);
    }

    for(i = 0; i < max_val + 1; ++i)
    {
        hash[0][i + 1] += hash[0][i];
    }

    for(i = size - 1; i >= 0; --i)
    {
        memcpy(VectorGetAccessToElement(out, hash[0][VtoI(VectorGetAccessToElement(dict, i))] - 1), VectorGetAccessToElement(dict, i), SIZOF_WORD);
        --(hash[0][VtoI(VectorGetAccessToElement(dict, i))]);
    }
    
    for(i = 0; i < size; ++i)
    {
        memcpy(VectorGetAccessToElement(dict, i), VectorGetAccessToElement(out, i), SIZOF_WORD);
    }

    free(hash[0]);

    VectorDestroy(out);
    
}


void* CountThreadII(void* args)
{
    arrsII* data = NULL;
    int i = 0, start;
    int* hash;
    size_t size;
    vector_ty *dict = NULL;


    data = (arrsII*)args;

    dict = data->dict;
    hash = data->hash;
    start = data->start;
    size = data->size;
    for(i = start; i < start + size; ++i)
    {  
        __sync_fetch_and_add(&hash[VtoI(VectorGetAccessToElement(dict, i))], 1);
    }


    return NULL;
}

int VtoI(void* val)
{
    int ret_val = 0;

    ret_val = *(char*)val - 'A';

    if(ret_val < 0)
    {
        ret_val = 58;
    }
    return ret_val;
}
