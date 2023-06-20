#include <stdlib.h>         /* size_t, malloc, srand, rand */
#include <assert.h>         /* assert */
#include <stdio.h>          /* printf */
#include <time.h>           /* time */ 

#include "vsa.h"

enum {FALSE, TRUE};

int TestVSA(void); 
long int TestInBoundCheck(void *lower_bound, void *upper_bound, void *address);
void TestGetRandomDiss(void);

int TestVSAAlloc(void);
int TestVSAFree(void);

int main()
{
    int is_success = TRUE;

    is_success &= TestVSA();

    if(!is_success)
    {
        TestGetRandomDiss();
    }
    return 0;
}

int TestVSA(void)
{
    size_t mem_size = 32768, largest_available = 0;
    void *mem = malloc(mem_size);
    vsa_ty *vsa = NULL;
    int is_success = FALSE;

    printf("in TestVSA(): \n");

    if(!mem)
    {
        printf("failed to allocate memory for VSA, testing stopped.\n");
        return is_success;
    }

    vsa = VSAInit(mem, mem_size);
    if(!vsa)
    {
        printf("failed to init with %lu bytes?? are you high? \n", mem_size);   
        return is_success;
    }

    largest_available = VSALargestAvailable(vsa);
    printf("in an empty vsa largest availbale size out of %lu allocated is: %lu \n", mem_size, largest_available);
    free(mem);
    mem = NULL;

    if(!TestVSAAlloc())
    {
        return is_success;
    }
    if(!TestVSAFree())
    {
        return is_success; 
    }
    is_success = TRUE;
    return is_success;
}

int TestVSAAlloc(void)
{
    int is_success = FALSE;
    size_t mem_size = 510, largest_available = 0, num_of_elements = 0, i = 0, *chunk = NULL;
    size_t *ptr_arr[510] = {0}; 
    void *mem = malloc(mem_size), *vsa = NULL;
    long int out_of_bound_offset = 0;

    printf("in TestVSAAlloc(): \n");

    assert(mem);

    vsa = VSAInit(mem, mem_size);

    assert(vsa);

    largest_available = VSALargestAvailable(vsa);
    chunk = VSAAlloc(vsa, largest_available);
    if(!chunk)
    {
        printf("VSAAlloc failed to allocate the largest size.\n");
        return is_success;
    }

    chunk = VSAAlloc(vsa, 1);
    if(chunk)
    {
        printf("alloc returned an address went out of bound after reaching max capacity, and ");

        out_of_bound_offset = TestInBoundCheck(mem, (char *)mem + mem_size, chunk);
        if(out_of_bound_offset)
        {
            printf("it's running over vsa data.");
        }
        else
        {
            printf("it's out of bounds with an offset of %ld from mem", out_of_bound_offset);
        }
        return is_success;
    }

    vsa = VSAInit(mem, mem_size);

    assert(vsa);
    assert(largest_available == VSALargestAvailable(vsa));   

    chunk = VSAAlloc(vsa, sizeof(int));

    assert(chunk);

    while(chunk)
    {
        *chunk = num_of_elements; 
        ptr_arr[num_of_elements] = chunk;
        ++num_of_elements;
        chunk = VSAAlloc(vsa, sizeof(int));
    }

    for(i = 0; i < num_of_elements; ++i)
    {
        if((*ptr_arr[i]) != i)
        {
            printf("alloc is running over memory.\n");
            return is_success;
        }
    }

    free(mem);
    mem = NULL;
    is_success = TRUE;
    return is_success;
}

int TestVSAFree(void)
{
    int is_success = FALSE;
    size_t mem_size = 510, num_of_elements = 0, i = 0, *chunk = NULL;
    size_t *ptr_arr[510] = {0}; 
    void *mem = malloc(mem_size), *vsa = NULL;

    printf("in TestVSAFree(): \n");

    assert(mem);

    vsa = VSAInit(mem, mem_size);

    assert(vsa);

    chunk = VSAAlloc(vsa, sizeof(int));

    assert(chunk);

    while(chunk)
    {
        *chunk = num_of_elements; 
        ptr_arr[num_of_elements] = chunk;
        ++num_of_elements;
        chunk = VSAAlloc(vsa, sizeof(int));
    }

    for(i = 0; i < num_of_elements; ++i)
    {
        VSAFree(ptr_arr[i]);
    }

    i = 0;
    chunk = VSAAlloc(vsa, sizeof(int));

    assert(chunk);

    while(chunk)
    {
        chunk = VSAAlloc(vsa, sizeof(int));
        ++i;
    }

    if(i != num_of_elements)
    {
        printf("vsa failed to refill an empty list with the exact same elements...\n failed after %lu allocs", num_of_elements - i );
    }

    free(mem);
    mem = NULL;
    is_success = TRUE;
    return is_success;

}

long int TestInBoundCheck(void *lower_bound, void *upper_bound, void *address)
{
    long int in_bound_cmp = (size_t)lower_bound - (size_t)address;
    long int range = (size_t)lower_bound - (size_t)upper_bound;

    if(in_bound_cmp < range && 0 <= in_bound_cmp)
    {
        return 0;
    }
    return (long int)((size_t)address - (size_t)lower_bound);
}

void TestGetRandomDiss(void)
{
    char *diss_array[50] = {
    "here: https://www.mcdonalds.co.il/%%D7%%93%%D7%%A8%%D7%%95%%D7%%A9%%D7%%99%%D7%%9D/%%D7%%9B%%D7%%9C%%D7%%9C%%D7%%99. \n you are welcome. :)\n"
    , "if you need motivation... here listen to this! https://www.youtube.com/watch?v=E9B8D5Tztbs \n"
    , "here you go, you'll need this buddy... https://www.learnpython.org/\n"
    , "still pooping I see... you gotta let it go bruv. -evald, probably.\n"
    , "https://gethelpisrael.com/hotlines/\n"
    , "dont worry... its not a bug, it a feature!\n"
    , "To live is to suffer. To survive is to find meaning in the suffering. -Friedrich Nietzsche"
    , "This thing that we call failure is not the falling down, but the staying down. -Mary Pickford"
    };
    size_t num_of_disses = 6;
    char *rand_str = NULL;

    srand(time(0));

    rand_str = diss_array[rand()%num_of_disses];
    printf("%s", rand_str);
}