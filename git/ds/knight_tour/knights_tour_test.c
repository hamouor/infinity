#include <stdio.h> /* printf */

#include "knight_tour.h" /* ADD ANY ADDITIONAL REQUIRED APIS */
#include "bit_array.h"

#define UNUSED(x) (void)(x)
#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define ABS(x) (((x) < 0) ? -(x) : (x))
typedef enum{
	SUCCESS,
	FAILURE,
	TIMEOUT
}result_ty;
/* FOR FUNCTIONS THAT CHECK TRUE/FALSE */
typedef enum bool { FALSE, TRUE } bool_ty; 

/* THE POSSIBLE RETURN STATUSES OF A TEST FUNCTION. AN UNIMPLEMENTED TEST SHOULD RETURN ERROR BY DEFAULT. */
typedef enum status { ERROR, GOOD, BAD } status_ty; 

/* ADD ANY DATA STRUCTURE THAT'S COMMON TO ALL TESTS AS A PARAMETER */
typedef status_ty (*test_func)(int *, int); 

typedef struct 
{
    test_func func;
    char *name;
} test_ty;

/* THE GENERIC TEST FUNCTION THAT CREATES RELEVANT DATA STRUCTURES AND RUNS TEST CASES */
status_ty Test(int index);

/* ADD TEST CASES HERE */
status_ty TestPath(int path[BOARD_SIZE], int index);
status_ty DUMMY(int path[BOARD_SIZE], int index);

int main(void)
{
	int num_tests = BOARD_SIZE;
	int i = 0;
	status_ty test_result = GOOD;
	status_ty unit_result = ERROR;
	
	for (i = 0; i < num_tests; ++i)
	{
		unit_result = Test(i);

		switch (unit_result)
		{
			case ERROR:
				printf("ERROR in running test %d.\n", i + 1);
				test_result = ERROR;
				break;
			case GOOD:
				break;
			case BAD:
				printf("Test %d failed! See details above!.\n", i);
				test_result = BAD;
				break;
			default:
				break;
		}
	}
	
	switch (test_result)
	{
		case ERROR:
			printf("Error in running some tests! See details above!\n");
			test_result = ERROR;
			break;
		case GOOD:
			printf("All tests successful!\n");
			break;
		case BAD:
			printf("Some tests failed! See details above!.\n");
			test_result = BAD;
			break;
		default:
			break;
	}
	
	return 0;
}

/* 
* CREATE AND DESTROY ANY COMMON DATA STRUCTURE, 
* OR DO ANY OTHER NECESSARY PREP WORK THAT'S COMMON FOR ALL TESTS 
*/
status_ty Test(int index) 
{
    status_ty result = ERROR;
	int path[BOARD_SIZE] = {-1};

	printf("Testing starting index %d...\n", index);

    result = TestPath(path, index);

	if (GOOD == result)
	{
		printf("Index %d is successful! Rejoice!\n", index);
	}

    return result;
}

/* IMPLEMENT TEST CASES */
status_ty TestPath(int path[BOARD_SIZE], int index)
{
	result_ty result = SUCCESS;
	status_ty test_result = GOOD;
	bit_arr_ty visited = 0;
	int i = 0;
	int row1 = 0, row2 = 0, col1 = 0, col2 = 0;


	result = KnightTour(path, index);

	if (result == FAILURE)
	{
		printf("Failed to find path when starting from index %d.\n", index);
		return BAD;
	}

	if (result == TIMEOUT)
	{
		printf("Path search timed out when starting from index %d.\n", index);
		return BAD;
	}

	visited = BitArrayResetAll(visited);

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		visited = BitArraySetOn(visited, path[i]);
	}

	if (BitArrayCountOn(visited) != BOARD_SIZE)
	{
		printf("Didn't visit all squares when started from index %d.\n", index);
		return BAD;
	}

	for (i = 0; i < BOARD_SIZE - 1; ++i)
	{
		if (path[i] < 0 || path[i] >= BOARD_SIZE)
		{
			printf("Hit index %d, which is out of the board range.\n", path[i]);
		}

		row1 = path[i] / BOARD_SIZE;
		row2 = path[i + 1] / BOARD_SIZE;
		col1 = path[i] % BOARD_SIZE;
		col2 = path[i + 1] % BOARD_SIZE;


		if (((ABS(row2 - row1) == 2) && (ABS(col2 - col1) != 1)) ||
			((ABS(row2 - row1) == 1) && (ABS(col2 - col1) != 2)))
		{
			printf("Two subsequent indices are not a valid knight move.\n");
			printf("The move is %d to %d, when starting from index %d.\n", path[i], path[i + 1], index);
			printf("Index 1: row %d, col %d\n", row1, col1);
			printf("Index 2: row %d, col %d\n", row2, col2);
			test_result = BAD;
		}
	}

	return test_result;
}

status_ty DUMMY(int path[BOARD_SIZE], int index)
{
	UNUSED(path);
	UNUSED(index);

	return GOOD;
}