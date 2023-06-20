#include <stdio.h>
#include <limits.h>
#include <time.h>

#include <string.h>             /* strcmp */

#include "ht.h"

#define UNUSED(x)               (void)(x)
#define ARR_SIZE(arr)           (sizeof(arr)/sizeof(arr[0]))

enum str_name {STRING0, STRING1, STRING2, STRING3, STRING4, STRING5, STRING6};

enum sizes {EMPTY, SINGLE, ARR_SIZE = 10, LETTERS = 26};

enum bool { FALSE, TRUE };

typedef enum status { ERROR, SUCCESS, FAILURE } status_ty;

typedef struct 
{
    int         *arr;
    int         ind;
    status_ty   result;
} arr_and_ind;

typedef status_ty (*test_func)(ht_ty *hash);

status_ty Test(test_func test);

status_ty TestCreate(ht_ty *hash);
status_ty TestDestroyEmpty(ht_ty *hash);
status_ty TestDestroyNonEmpty(ht_ty *hash);

status_ty TestSizeEmpty(ht_ty *hash);
status_ty TestSizeInsertOnly(ht_ty *hash);
status_ty TestSizeInsertNRemove(ht_ty *hash);

status_ty TestIsEmptyEmpty(ht_ty *hash);
status_ty TestIsEmptyNonEmpty(ht_ty *hash);

status_ty TestInsertNonEmpty(ht_ty *hash);

status_ty TestFindPresent(ht_ty *hash);
status_ty TestFindNonPresent(ht_ty *hash);

status_ty TestForEach(ht_ty *hash);

status_ty TestRemoveNotPresent(ht_ty *hash);
status_ty TestRemoveNonEmpty(ht_ty *hash);

int IntCmp(void *val1, void *val2);
int TestOrder(void *data, void *order_str);
int KeyTranslator(const void *);
int CompFunc(void *, void *);
int AddSmiley(void *data, void *param);
int PrintHash(void *data, void *param);

int main(void)
{
	test_func tests[] = {
        TestCreate,
        TestDestroyEmpty,
        TestDestroyNonEmpty,
        TestSizeEmpty,
        TestSizeInsertOnly,
        TestSizeInsertNRemove,
        TestIsEmptyEmpty,
        TestIsEmptyNonEmpty,
        TestFindPresent,
        TestFindNonPresent,
        TestInsertNonEmpty,
        TestForEach,
        TestRemoveNotPresent,
        TestRemoveNonEmpty,
	};
	
	char *test_names[] = {
        "TestCreate",
        "TestDestroyEmpty",
        "TestDestroyNonEmpty",
        "TestSizeEmpty",
        "TestSizeInsertOnly",
        "TestSizeInsertNRemove",
        "TestIsEmptyEmpty",
        "TestIsEmptyNonEmpty",
        "TestFindPresent",
        "TestFindNonPresent",
        "TestInsertNonEmpty",
        "TestForEach",
        "TestRemoveNotPresent",
        "TestRemoveNonEmpty",
	};
	
	int num_tests = sizeof(tests) / sizeof(tests[0]);
	int i = 0;
	status_ty test_result = SUCCESS;
	status_ty unit_result = ERROR;
	
	for (i = 0; i < num_tests; ++i)
	{
		unit_result = Test(tests[i]);
		switch (unit_result)
		{
			case ERROR:
				printf("GEVALD! test %d: %s() is maaadd.\n", i + 1, test_names[i]);
				test_result = ERROR;
				break;
			case SUCCESS:
				break;
			case FAILURE:
				printf("%s() is making BALAGAN! See details above!.\n", test_names[i]);
				test_result = FAILURE;
				break;
			default:
				break;
		}
	}
	
	switch (test_result)
	{
		case ERROR:
			printf("Some of ur tests are .. meh. See details above!\n");
			test_result = ERROR;
			break;
		case SUCCESS:
			printf("YOU ARE AWESOME AND ALSO AMAZING!\n");
			break;
		case FAILURE:
			printf("damn son, u failed. check out earlier comments.\n");
			test_result = FAILURE;
			break;
		default:
			break;
	}
	
	return 0;
}

status_ty Test(test_func test)
{
    ht_ty *hash = NULL;
    size_t hash_len = LETTERS;
    status_ty result = ERROR;

    hash = HTCreate(KeyTranslator, CompFunc, hash_len);
    result = test(hash);
    HTDestroy(hash);

    return result;
}

status_ty TestCreate(ht_ty *hash)
{
    return hash ? SUCCESS : FAILURE;
}

status_ty TestDestroyEmpty(ht_ty *hash)
{
    UNUSED(hash);

    printf("dont forget to check vlg sugar buns\n");
    /* run valgrind and make sure there are no leaks */
    return SUCCESS;
}

status_ty TestDestroyNonEmpty(ht_ty *hash)
{
    char *strings[] = {
        "Hagar",
        "Was",
        "Here"
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;


    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            status = FAILURE;
        }
    }

    printf("dont forget to check vlg sugar buns\n");
    /* run valgrind and make sure there are no leaks */
    return status;    
}

status_ty TestSizeEmpty(ht_ty *hash)
{    
    int status = SUCCESS;

    if (HTSize(hash))
    {
        printf("size isnt 0 when empty\nits : %lu", HTSize(hash));
        status = FAILURE;
    }

    HTIsEmpty(hash) ? SUCCESS : FAILURE;
    
    return status;
}

status_ty TestSizeInsertOnly(ht_ty *hash)
{
    char *strings[] = {
        "Hagar",
        "Was",
        "Here"
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            status = FAILURE;
        }
    }

    if (num_str != (int)HTSize(hash))
    {
        printf("size was supposed to be %d and its %lu\n", num_str, HTSize(hash));
        status = FAILURE;
    }
    
    return status;  
}

status_ty TestSizeInsertNRemove(ht_ty *hash)
{
    char *strings[] = {"Hagar"};
    char *get_it[10];
    char *str = get_it[0];
    int status = SUCCESS;

    UNUSED(get_it);

    if (HTInsert(hash, (void *)strings[0]))
    {
        status = FAILURE;
    }

    if (!HTRemove(hash, (void *)strings[0]))
    {
        printf("remove brought back NULL when it shouldnt\n");
        status = FAILURE;
    }

    if (HTSize(hash))
    {
        printf("size was supposed to bring back 0 and its %lu\n", HTSize(hash));
        status = FAILURE;
    }    

    return status;     
}    

status_ty TestIsEmptyEmpty(ht_ty *hash)
{    
    return HTIsEmpty(hash) ? SUCCESS : FAILURE;
}

status_ty TestIsEmptyNonEmpty(ht_ty *hash)
{
    char *strings[] = {
        "Hagar",
        "Was",
        "Here"
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            return FAILURE;
        }
    }

    return !HTIsEmpty(hash) ? SUCCESS : FAILURE;
}

status_ty TestInsertNonEmpty(ht_ty *hash)
{
    char *strings[] = {
        "Hagar",
        "Was",
        "Here",
        "Hi",
        "How",
        "Are",
        "You",
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            status = FAILURE;
        }
    }

    if (num_str != (int)HTSize(hash))
    {
        printf("size was supposed to be %d and its %lu\n", num_str, HTSize(hash));
        status = FAILURE;
    }
    
    return status;  
}

status_ty TestFindPresent(ht_ty *hash)
{
    char *strings[] = {
        "Hagar",
        "Was",
        "Here",
        "Hi",
        "How",
        "Are",
        "You",
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            status = FAILURE;
        }
    }

    if (!HTFind(hash, (void *)strings[2]))
    {
        printf("Find returns NULL\n");
        status = FAILURE;
    }
    
    return status;
}

status_ty TestFindNonPresent(ht_ty *hash)
{
    char *strings[] = {
        "Hagar",
        "Was",
        "Here",
        "Hi",
        "How",
        "Are",
        "You",
    };
    char *not_there = "Nope";
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            status = FAILURE;
        }
    }

    if (num_str != (int)HTSize(hash))
    {
        printf("size was supposed to be %d and its %lu\n", num_str, HTSize(hash));
        status = FAILURE;
    }

    if (HTFind(hash, (void *)not_there))
    {
        printf("Find returns data, wtf bruh: %s\n", (char *)HTFind(hash, (void *)strings[2]));
        status = FAILURE;
    }
    
    return status;
}    

status_ty TestForEach(ht_ty *hash)
{
    char *strings[] = {
        "A:(",
        "A:)",
        "Alloooooo",
        "Been",
        "Here",
        "For",
        "Some",
        "Time..",
        "Well, now that we've met im gonna go..\n"
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            status = FAILURE;
        }
    }

    if (num_str != (int)HTSize(hash))
    {
        printf("size was supposed to be %d and its %lu\n", num_str, HTSize(hash));
        status = FAILURE;
    }

    printf("\n*+* watch youre strings: *+*\n");
    
    if (HTForEach(hash, PrintHash, NULL))
    {
        printf("ForEach returned FAILURE\n");
        status = FAILURE;        
    }

    return status;
}

status_ty TestRemoveNotPresent(ht_ty *hash)
{
    char *to_remove = "hi";

    if (HTRemove(hash, (void *)to_remove))
    {
        return FAILURE;
    }

    return SUCCESS;
}

status_ty TestRemoveNonEmpty(ht_ty *hash)
{
    char *strings[] = {
        "A:(",
        "A:)",
        "Alloooooo",
        "Been",
        "Here",
        "For",
        "Some",
        "Time..",
        "Well, now that we've met im gonna go..\n"
    };
    int num_str = sizeof(strings) / sizeof(strings[0]);
    int status = SUCCESS;
	int i = 0;

    for (i = 0; num_str > i; ++i)  
    {
        if (HTInsert(hash, (void *)strings[i]))
        {
            printf("failure inserting new data\n");
            status = FAILURE;
        }
    }

    for (i = 0; num_str > i; ++i)
    {
        if ((void *)strings[i] != HTFind(hash, (void *)strings[i]))
        {
            printf("find retunrs wrong data to remove\nyou might want to check past removals\ni = %d\n", i);
            status = FAILURE;
        }

        if (!HTRemove(hash, (void *)strings[i]))
        {
            printf("remove brought back NULL when it shouldnt\n");
            status = FAILURE;
        }

        if ((num_str -1 - i) != (int)HTSize(hash))
        {
            printf("size is wrong after remove, should be %d, but its %lu\n", (num_str -1 - i), HTSize(hash));
            status = FAILURE;
        }

        if (HTFind(hash, (void *)strings[i]))
        {
            printf("find retunrs data that was supposed to be deleted.. OOPS\n");
            status = FAILURE;
        }
    }

    if (!HTIsEmpty(hash))
    {
        printf("remove was supposed to clear the table,\nyet it didnt, good luck fixing that sh*t now.\n");
        status = FAILURE;
    }

    return status;
}

int KeyTranslator(const void *data)
{
    /* make sure to stay consistant with capital letters */
    return *(char *)data - 'A';
}

int CompFunc( void *data1,  void *data2)
{
    return !strcmp((char *)data1, (char *)data2); 
}

int AddSmiley(void *data, void *param)
{
    strcat((char *)data, (char *)param);
    return SUCCESS;
}

int PrintHash(void *data, void *param)
{
    UNUSED(param);

    printf("%s\n", (char *)data);

    return 0;
}
