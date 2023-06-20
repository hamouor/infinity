#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h> 
#include <string.h>
#include <time.h>

#include"vector.h"
#include"vector.c"

#define NUM_OF_THREADS 1000
#define SIZOF_WORD 30
#define MAX_CHAR 54
#define NUM_OF_COPIES 4
#define TOO_MUCH 100

#define IGNORE(x) (void)(x)

enum { NS_PER_SECOND = 1000000000 };

enum{
    SUCCESS,
    FAILURE
};

typedef struct arr1
{
    vector_ty *dict;
    int start;
    int end;
}arguments;

static void Swap(vector_ty* arr, size_t index1, size_t index2);
void *BubbleSort(void *args);
int VtoI(void* val);
void* MinVal(vector_ty* *out, int* index);
void Merge(vector_ty** out, vector_ty* vect);
int SplitNSort(vector_ty* vect, size_t size);
int Shuff(const void* elem1, const void* elem2);
int CompVtoI(const void* arg1, const void* arg2);
void* Qsort(void* args);
void* CountingSort(void* args);
void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td);


int main()
{
    FILE *dictionary = NULL;
    char line[SIZOF_WORD];
    vector_ty* dict = NULL;
    vector_ty* ptrs = NULL;
    int i = 0, ret_val = 0;
    struct timespec start, finish, delta;

    dict = VectorCreate(SIZOF_WORD, SIZOF_WORD);

    if(!dict)
    {
        return FAILURE;
    }

    dictionary = fopen("/usr/share/dict/american-english", "r");

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

    ptrs = VectorCreate(SIZOF_WORD, NUM_OF_COPIES * VectorSize(dict));
    if(!ptrs)
    {
        VectorDestroy(dict);
        fclose(dictionary);
        return FAILURE;
    }

    for(i = 0; i < NUM_OF_COPIES; ++i)
    {
        memcpy(VectorGetAccessToElement(ptrs, i * VectorSize(dict)), VectorGetAccessToElement(dict,0), VectorSize(dict) * SIZOF_WORD);
    }

    ptrs->size = NUM_OF_COPIES * VectorSize(dict);
    
    qsort(VectorGetAccessToElement(ptrs,0), VectorSize(ptrs), SIZOF_WORD, Shuff);

    /*for(i = 0; i < VectorSize(ptrs); ++i)
    {
        printf("%s\n", (char*)VectorGetAccessToElement(ptrs, i));
    }*/
    clock_gettime(CLOCK_REALTIME, &start);
    ret_val = SplitNSort(ptrs, VectorSize(ptrs));
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_timespec(start, finish, &delta);
    /*for(i = 0; i < VectorSize(ptrs); ++i)
    {
        printf("%s\n", (char*)VectorGetAccessToElement(ptrs, i));
    }*/

    printf("%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);    
    
    fclose(dictionary);
    VectorDestroy(dict);
    VectorDestroy(ptrs);

    return SUCCESS;
}


int Shuff(const void* elem1, const void* elem2)
{
    int a = 0;

    IGNORE(elem1);
    IGNORE(elem2);

    a = rand();

    if(a % 2)
    {
        return 1;
    }

    return -1;
}


int SplitNSort(vector_ty* vect, size_t size)
{
    pthread_t id[NUM_OF_THREADS];
    int i = 0, j = 0;
    arguments args[NUM_OF_THREADS];
    vector_ty* out[NUM_OF_THREADS];
    int sub_size = 0;
    int fail_flag = 0;

    sub_size = size / NUM_OF_THREADS;

    for(; i < NUM_OF_THREADS - 1; ++i)
    {
        args[i].dict = vect;
        args[i].start = i * sub_size;
        args[i].end = (i + 1) * sub_size;
        if(pthread_create(&id[i], NULL, BubbleSort, (void*)&args[i]))
        {
            return FAILURE;
        }
    }
    args[i].dict = vect;
    args[i].start = i * sub_size;
    args[i].end = size;
    if(pthread_create(&id[i], NULL, BubbleSort, (void*)&args[i]))
    {
        return FAILURE;
    }


    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(id[i], (void*)&out[i]);
    }

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(!out[i])
        {
            fail_flag = 1;
        }
    }

    if(fail_flag)
    {
        for(i = 0; i < NUM_OF_THREADS; ++i)
        {
            if(out[i])
            {
                VectorDestroy(out[i]);
            }
        }
        return FAILURE;
    }

    Merge(out, vect);

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        VectorDestroy(out[i]);
    }

    
    return SUCCESS;
}


void Merge(vector_ty** out, vector_ty* vect)
{
    int i = 0;
    int index[NUM_OF_THREADS] = {0};

    for(; i < VectorSize(vect); ++i)
    {
        memcpy(VectorGetAccessToElement(vect, i), MinVal(out, index), SIZOF_WORD);
    }
}

void* MinVal(vector_ty** out, int* index)
{
    int i = 0, found = 0;
    void* ret_val = NULL;

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if(index[i] < VectorSize(out[i]) && VtoI(ret_val) > VtoI(VectorGetAccessToElement(out[i], index[i])))
        {
            ret_val = VectorGetAccessToElement(out[i], index[i]);
            found = i;
        }
    }

    ++index[found];
    return ret_val;
}


int VtoI(void* val)
{
    int ret_val = 0;

    if(!val)
    {
        return TOO_MUCH;
    }
    ret_val = *(char*)val - 'A';

    if(ret_val < 0)
    {
        ret_val = MAX_CHAR;
    }
    return ret_val;
}


void* Qsort(void* args)
{
    vector_ty* out = NULL;
    arguments* ars = (arguments*)args;


    out = VectorCreate(SIZOF_WORD, ars->end - ars->start);
    if(!out)
    {
        return NULL;
    }

    memcpy(VectorGetAccessToElement(out, 0), VectorGetAccessToElement(ars->dict, ars->start),SIZOF_WORD * (ars->end - ars->start));

    out->size = ars->end - ars->start;

    qsort(VectorGetAccessToElement(out, 0), ars->end - ars->start, SIZOF_WORD ,CompVtoI);

    return (void*)out;
}

int CompVtoI(const void* arg1, const void* arg2)
{
    if(VtoI((void*)arg1) > VtoI((void*)arg2))
    {
        return 1;
    }
    return -1;
}

void *BubbleSort(void *args) 
{
    int swaps = 1, i = 0;
    arguments* ars = (arguments*)args;
    vector_ty* out = NULL;

    out = VectorCreate(SIZOF_WORD, ars->end - ars->start);
    if(!out)
    {
        return NULL;
    }

    memcpy(VectorGetAccessToElement(out, 0), VectorGetAccessToElement(ars->dict, ars->start),SIZOF_WORD * (ars->end - ars->start));

    out->size = ars->end - ars->start;

    while(swaps)
    {
        swaps = 0;
        for(i = 0; i < (int)VectorSize(out) - 1; ++i)
        {
            if(VtoI(VectorGetAccessToElement(out, i)) >  VtoI(VectorGetAccessToElement(out, i + 1)))
            {
                swaps = 1;
                Swap(out, i, i+1);
            }
        }
    }

    return (void*)out;
}

static void Swap(vector_ty* arr, size_t index1, size_t index2)
{
    char temp[SIZOF_WORD];

    if(index1 != index2)
    {
        memcpy((void*)&temp, VectorGetAccessToElement(arr, index1), SIZOF_WORD);
        memcpy(VectorGetAccessToElement(arr, index1), VectorGetAccessToElement(arr, index2), SIZOF_WORD);
        memcpy(VectorGetAccessToElement(arr, index2), (void*)&temp, SIZOF_WORD);
    }
}


void* CountingSort(void* args)
{
    int* hash = NULL, i = 0, max_val = 0;
    vector_ty* out = NULL, *place = NULL;
    arguments* ars = (arguments*)args;

    out = VectorCreate(SIZOF_WORD, ars->end - ars->start);
    if(!out)
    {
        return NULL;
    }

    place = VectorCreate(SIZOF_WORD, ars->end - ars->start);
    if(!place)
    {
        VectorDestroy(out);
        return NULL;
    }

    memcpy(VectorGetAccessToElement(out, 0), VectorGetAccessToElement(ars->dict, ars->start),SIZOF_WORD * (ars->end - ars->start));

    out->size = ars->end - ars->start;
    place->size = ars->end - ars->start;

    for(; i < VectorSize(out); ++i)
    {
        if(VtoI(VectorGetAccessToElement(out, i)) > max_val)
        {
            max_val = VtoI(VectorGetAccessToElement(out, i));
        }
    }
    
    hash = (int*)calloc(max_val + 1, sizeof(int));
    if(!hash)
    {
        VectorDestroy(out);
        VectorDestroy(place);
        return NULL;
    }

    for(i = 0; i < VectorSize(out); ++i)
    {  
        ++hash[VtoI(VectorGetAccessToElement(out, i))];
    }


    for(i = 0; i < max_val; ++i)
    {
        hash[i + 1] += hash[i];
    }

    for(i = VectorSize(out) - 1; i >= 0; --i)
    {
        memcpy(VectorGetAccessToElement(place, hash[VtoI(VectorGetAccessToElement(out, i))] - 1), VectorGetAccessToElement(out, i), SIZOF_WORD);
        --(hash[VtoI(VectorGetAccessToElement(out, i))]);
    }
    
    for(i = 0; i < VectorSize(out); ++i)
    {
        memcpy(VectorGetAccessToElement(out, i), VectorGetAccessToElement(place, i), SIZOF_WORD);
    }

    free(hash);
    VectorDestroy(place);

    return (void*)out;    
}

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

