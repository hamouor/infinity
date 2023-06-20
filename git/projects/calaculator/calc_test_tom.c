#include <stdio.h>
#include <math.h>

#include "calc.h"

typedef enum { SUCCESS, FAILURE } status_ty;

int main(void)
{
	char *tests[] = 
	{
		"2+2",
		"3-5",
		"0+0",
		"0-0",
		"0+10",
		"0-10",
		/*"0",
		"1",*/
		"10-10",
		"0.2+1.4",
		"0.1-0.2",
		"0-1.4",
		"0+1.4",
		/*"+18",
		"-18,*/
		"5+1+9",
		"1-5+8",
		"1+9-3",
		"10-3-5",
		"10++10",
		"10--10",
		"2*2",
		"2/2",
		"2^2",
		"2*2/5",
		"2/2*5",
		"(2+2)",
		"((2)+3)+(5+6)",
		"(2+4)-(2+8)",
		"(2+2*2)",
		"(2*2+(-2))",
		"(2+2/2)",
		"(2/2+2)",
		"(2+2)*5",
		"4*(2+3)",
		"5/(4+3)",
		"(4+3)/5",
		"(3+6)^5",
		"5^(3+6)",
		"(3-6)^5",
		"(3*6)^5",
		"5^(3*2)",
		"(3/6)^5",
		"(2+5)*(4+2)",
		"(2+6)/(4+9)",
		"(4+3)^(2+1)",
		"4^(2^3)",
		"2^3^4",
		"(2+5)*5^(2+1)-(2+3)^(3-1)",
		" 2+2",
		"2 +2",
		"2+ 2",
		"2+2 ",
		" ( 2 + 5 ) * 5 ^ ( 2 + 1 ) - ( 2 + 3 ) ^ (  3 - 1 ) "
	};
	
	double results[] = 
	{
		2+2,
		3-5,
		0+0,
		0-0,
		0+10,
		0-10,
		/*0,
		1,*/
		10-10,
		0.2+1.4,
		0.1-0.2,
		0-1.4,
		0+1.4,
		/*+18,
		-18,*/
		5+1+9,
		1-5+8,
		1+9-3,
		10-3-5,
		10+(+10),
		10-(-10),
		2*2,
		2/2,
		4, 				/*pow(2, 2)*/
		2*2/5.0,
		2.0/2*5,
		(2+2),
		((2)+3)+(5+6),
		(2+4)-(2+8),
		(2+2*2),
		(2*2+(-2)),
		(2+2/2.0),
		(2/2+2),
		(2+2)*5,
		4*(2+3),
		5.0/(4+3),
		(4+3)/5.0,
		59049,		 	/*pow(3+6, 5)*/
		1953125,		/*pow(5, 3+6)*/
		-243, 			/*pow(3-6, 5)*/
		1889568,		/*pow(3*6, 5)*/
		15625,			/*pow(5, 3*2)*/
		0.03125,		/*pow(3/6, 5)*/
		(2+5)*(4+2),
		(2+6)/(4.0+9),
		343,			/*pow((4+3), (2+1)),*/
		65536,			/*pow(4, pow(2, 3))*/
		4096,			/*pow(pow(2, 3), 4)*/
		850,			/*(2+5)*(pow(5, (2+1)))-pow((2+3), (3-1))*/
		 2+2,
		2 +2,
		2+ 2,
		2+2 ,
		850				/*(2+5)*(pow(5, (2+1)))-pow((2+3), (3-1))*/
	};
	
	char *bad_tests[] = 
	{
		"+",
		"-",
		"10+",
		"10-",
		"10+10+",
		"10+10-",
		"10+++10",
		"10---10",
		"((2+3)",
		"2+3)",
		"2*",
		"2/",
		"2^",
		"2)",
		"2)",
		"(",
		"*",
		"/",
		")",
		"^",
		"*5",
		"/5",
		"^5",
		"(5",
		")5",
		"2/0",
		"0^0",
		"(2+3+)",
		"2^(2+",
		"2)^6",
	};
	
	char *tests_adv[] = 
	{
		"2(2+5)",
		"(2+5)2",
		"2 (2+5)",
		"(2+5) 2",
		"2(2(2(2+2)))",
		"((((2+2)2)2)2)",
	};
	
	double results_adv[] = 
	{
		2*(2+5),
		(2+5)*2,
		2 *(2+5),
		(2+5)* 2,
		2*(2*(2*(2+2))),
		((((2+2)*2)*2)*2),
	};
	
	int num_tests = sizeof(tests) / sizeof(tests[0]);
	int num_bad_tests = sizeof(bad_tests) / sizeof(bad_tests[0]);
	int num_adv_tests = sizeof(tests_adv) / sizeof(tests_adv[0]);
	int i = 0;
	double calc_result = 0;
	status_ty test_result = SUCCESS;
	
	for (i = 0; i < num_tests; ++i)
	{
		printf("%d", i);
		if (Calc(tests[i], &calc_result))
		{
			test_result = FAILURE;
			printf("*****Calculator failed at index %d*****\n", i);
		}
		
		if (calc_result != results[i])
		{
			test_result = FAILURE;
			printf("*****Failed test at index %d*****\n"
			"Input: %s\n"
			"Expected: %f\n"
			"Yielded: %f\n\n", i, tests[i], results[i], calc_result);
		}
	}
	
	for (i = 0; i < num_bad_tests; ++i)
	{
		if (!Calc(bad_tests[i], &calc_result))
		{
			test_result = FAILURE;
			printf("*****Failed test at index %d*****\n"
			"Input: %s\n"
			"Expected: Bad syntax failure.\n"
			"Yielded: %f\n\n", i, bad_tests[i], calc_result);
		}
	}
	
	if (FAILURE == test_result)
	{
		printf("Some tests failed! See results above!\n");
	}
	else
	{
		printf("All tests successful!\n");
	}
	
	test_result = SUCCESS;
	printf("*****THESE ARE THE ADVANCED TESTS*****\n");
	for (i = 0; i < num_adv_tests; ++i)
	{
		if (Calc(tests_adv[i], &calc_result))
		{
			test_result = FAILURE;
			printf("*****Calculator failed at index %d*****\n", i);
		}
		
		if (calc_result != results_adv[i])
		{
			test_result = FAILURE;
			printf("*****Failed test at index %d*****\n"
			"Input: %s\n"
			"Expected: %f\n"
			"Yielded: %f\n\n", i, tests_adv[i], results_adv[i], calc_result);
		}
	}
	
	if (FAILURE == test_result)
	{
		printf("Some advanced tests failed! See results above!\n");
	}
	else
	{
		printf("All advanced tests successful!\n");
	}
	
	return 0;
}
