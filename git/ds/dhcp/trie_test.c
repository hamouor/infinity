#include <stdio.h>
#include <limits.h>

#include "trie.h"

#define UNUSED(x)               (void)(x)
#define ARR_SIZE(arr)           (sizeof(arr)/sizeof(arr[0]))
#define HEIGHT                  8

enum bool { FALSE, TRUE };

typedef enum status { ERROR, SUCCESS, FAILURE } status_ty;

typedef struct 
{
    int         *arr;
    int         ind;
    status_ty   result;
} arr_and_ind;

typedef status_ty (*test_func)(trie_ty *);

status_ty Test(test_func);

status_ty TestCreate(trie_ty *);
status_ty TestDestroyEmpty(trie_ty *);
status_ty TestDestroyNonEmpty(trie_ty *);
status_ty TestSizeEmpty(trie_ty *);
status_ty TestRemoveEmpty(trie_ty *);
status_ty TestRemoveSIngle(trie_ty *);
status_ty TestRemove(trie_ty *);
status_ty TestInsertSIngle(trie_ty *);
status_ty TestInsert(trie_ty *);

void PathPrint(char *);
void PathCompare(char *req_path, char *rec_path);

int main(void)
{
	test_func tests[] = {
        TestCreate,
        TestDestroyEmpty,
        TestDestroyNonEmpty,
        TestSizeEmpty,
        TestRemoveEmpty,
        TestRemoveSIngle,
        TestRemove,
        TestInsertSIngle,
        TestInsert,

	};
	
	char *test_names[] = {
        "TestCreate",
        "TestDestroyEmpty",
        "TestDestroyNonEmpty",
        "TestSizeEmpty", 
        "TestRemoveEmpty", 
        "TestRemoveSIngle",
        "TestRemove",
        "TestInsertSIngle",     
        "TestInsert",

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
			printf("+*+ YOU ARE AWESOME AND ALSO AMAZING! +*+\n");
			break;
		case FAILURE:
			printf("OH SNAP! U FAILED\n check out earlier comments.\n");
			test_result = FAILURE;
			break;
		default:
			break;
	}
	
	return 0;
}

status_ty Test(test_func test)
{
    trie_ty *trie = NULL;
    
    status_ty result = ERROR;

    trie = TrieCreate(HEIGHT);
    result = test(trie);
    TrieDestroy(trie);

    return result;
}

status_ty TestCreate(trie_ty *trie)
{
    return trie ? SUCCESS : FAILURE;
}

status_ty TestDestroyEmpty(trie_ty *trie)
{
    UNUSED(trie);

    printf("Dont forget to check vlg sugar buns\n");
    /* run valgrind and make sure there are no leaks */
    return SUCCESS;
}

status_ty TestDestroyNonEmpty(trie_ty *trie)
{
    int status = SUCCESS;
    char path[1] = {0};
    char requested[1] = {0};

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("1. failed creating a new path\n");
        status = FAILURE;
    }
    else
    {
        PathCompare(requested, path);
        
        if (1 != TrieSize(trie))
        {
            printf("size is %lu instead of 1\n", TrieSize(trie));
            status = FAILURE;
        }
    }
    
    printf("Dont forget to check vlg sugar buns\n");
    /* run valgrind and make sure there are no leaks */
    return status;
}

status_ty TestSizeEmpty(trie_ty *trie)
{
    int status = SUCCESS;

    if (TrieSize(trie))
    {
        printf("size is %lu\n", TrieSize(trie));
        status = FAILURE;
    }

    return status;
}

status_ty TestRemoveEmpty(trie_ty *trie)
{
    int status = SUCCESS;
    char path[4] = {0,0,0,0};

    if (BAD_IP != TrieFreePath(trie, path))
    {
        printf("remove returns success when empty\n");
        status = FAILURE;
    }

    return status;
}

status_ty TestInsertSIngle(trie_ty *trie)
{
    int status = SUCCESS;
    char path[1] = {0};
    char requested[1] = {0};

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("1. failed creating a new path\n");
        status = FAILURE;
    }
    else
    {
        PathCompare(requested, path);
        
        if (1 != TrieSize(trie))
        {
            printf("size is %lu instead of 1\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    return status;
}

status_ty TestInsert(trie_ty *trie)
{
    int status = SUCCESS;
    char path[1] = {2};
    char requested[1] = {2};
    char requested2[1] = {3};
    char requested3[1] = {4};

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("1. failed creating a new path\n");
        status = FAILURE;
    }
    else
    {
        PathCompare(requested, path);
        
        if (1 != TrieSize(trie))
        {
            printf("size is %lu instead of 1\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("2. failed creating a new path\n");
        PathCompare(requested2, path);
        status = FAILURE;
    }
    else
    {
        PathCompare(requested2, path);
        
        if (2 != TrieSize(trie))
        {
            printf("size is %lu instead of 2\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("3. failed creating a new path\n");
        PathCompare(requested2, path);
        status = FAILURE;
    }
    else
    {
        PathCompare(requested3, path);
        
        if (3 != TrieSize(trie))
        {
            printf("size is %lu instead of 3\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    return status;
}

status_ty TestRemoveSIngle(trie_ty *trie)
{
    int status = SUCCESS;
    char path[1] = {3};
    char requested[1] = {3};

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("1. failed creating a new path\n");
        status = FAILURE;
    }
    else
    {
        PathCompare(requested, path);
        
        if (1 != TrieSize(trie))
        {
            printf("size is %lu instead of 1\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    if (-1 == TrieFreePath(trie, path))
    {
        printf("remove failed after a single insertion\n");
        status = FAILURE;
    }
    if (TrieSize(trie))
    {
        printf("size is %lu when should be empty\n", TrieSize(trie));
        status = FAILURE;
    }

    return status;
}

status_ty TestRemove(trie_ty *trie)
{
    int status = SUCCESS;
    char path[1] = {1};
    char requested[1] = {1};
    char requested2[1] = {2};
    char requested3[1] = {3};

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("1. failed creating a new path\n");
        status = FAILURE;
    }
    else
    {
        PathCompare(requested, path);
        
        if (1 != TrieSize(trie))
        {
            printf("size is %lu instead of 1\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    if (FAILURE == TrieCreateNewPath(trie, path))
    {
        printf("2. failed creating a new path\n");
        PathCompare(requested2, path);
        status = FAILURE;
    }
    else
    {
        PathCompare(requested2, path);
        
        if (2 != TrieSize(trie))
        {
            printf("size is %lu instead of 2\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    if (FAILURE == TrieCreateNewPath(trie, requested3))
    {
        printf("3. failed creating a new path\n");
        PathCompare(requested2, path);
        status = FAILURE;
    }
    else
    {
        printf(".");
        PathCompare(requested3, path);
        printf(".");
        if (3 != TrieSize(trie))
        {
            printf("size is %lu instead of 3\n", TrieSize(trie));
            status = FAILURE;
        }
    }

    if (-1 == TrieFreePath(trie, requested2))
    {
        printf("remove requested2 failed\n");
        status = FAILURE;
    }
    if (2 != TrieSize(trie))
    {
        printf("size is %lu when should be 2\n", TrieSize(trie));
        status = FAILURE;
    }

    if (BAD_IP != TrieFreePath(trie, requested2))
    {
        printf("remove same thing twice failed\n");
        status = FAILURE;
    }
    if (2 != TrieSize(trie))
    {
        printf("size is %lu when should be 2\n", TrieSize(trie));
        status = FAILURE;
    }

    if (-1 == TrieFreePath(trie, requested))
    {
        printf("remove requested failed\n");
        status = FAILURE;
    }
    if (1 != TrieSize(trie))
    {
        printf("size is %lu when should be 1\n", TrieSize(trie));
        status = FAILURE;
    }

    if (-1 == TrieFreePath(trie, requested3))
    {
        printf("remove requested3 failed\n");
        status = FAILURE;
    }
    if (TrieSize(trie))
    {
        printf("size is %lu when should be empty\n", TrieSize(trie));
        status = FAILURE;
    }

    return status;    
}







void PathCompare(char *req_path, char *rec_path)
{
    int i = 0;
    
    for (i = 0; 1 > i; ++i)
    {
        if (req_path[i] != rec_path[i])
        {
            printf("requested path:");
            PathPrint(req_path);
            printf("\n");
            printf("recieved path:");
            PathPrint(rec_path);
            printf("\n");
            return;
        }
    }    
}

void PathPrint(char *path)
{
    int i = 0;
    
    for (i = 1; 0 <= i; --i)
    {
        printf("%d", path[i]);
    }
}