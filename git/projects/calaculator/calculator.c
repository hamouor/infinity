#include <math.h>   /*pow*/
#include <stdlib.h> /*strtod*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/
#include "stack.h"

#define CHARSPAN    55
#define CHAROFFSET  40


typedef enum
{
    WAITINGNUM = 0,
    WAITINGOP = 1,
    RESULT = 2,
    ERROR = 3
}states;

typedef struct calc
{
    char* string;
    stack_ty *nums;
    stack_ty *opers;
    states  curr_state;
    double *result;
}calculator;



/*typedef void(*StateHandle)(stack_ty* operands, stack_ty* nums); 
typedef void(*CalcMe)(stack_ty* operands, stack_ty* nums);

StateHandle StateLUT[LUTSIZE1][LUTSIZE2];
CalcMe CalcLUT[LUTSIZE2];


void ErrorFunc(stack_ty* operands, stack_ty* nums);

void LUTSetup();

double Calc(char *string, double *result);

void NumHandle(int state, double num, stack_ty* nums, stack_ty* operands);

void OpenParenthesis(stack_ty* operands, stack_ty* nums);

void Plus(stack_ty* operands, stack_ty* nums);

void Minus(stack_ty* operands, stack_ty* nums);

void CalcPlus(stack_ty* operands, stack_ty* nums);

void CalcMinus(stack_ty* operands, stack_ty* nums);

double CalacAll(stack_ty* operands, stack_ty* nums);

void ErrorFunc(stack_ty* operands, stack_ty* nums);


#include<stdio.h>

int main()
{
    char str[30] = "1+1";
    double res = 0.0;
    int f = 0;

    f = Calc(str, &res);

    printf("%f", res);

    

    return 0;
}
*/
int Calc(char *string, double *result)
{
    stack_ty *opers = NULL, *nums = NULL;
    size_t len = 0;
    calculator *local_calc = NULL;
    int retval = 0;

    assert(string && result);

    len = strlen(string);
    opers = StackCreate(sizeof(char), len);
    if(!opers)
    {
        return 1;
    }
    nums = StackCreate(sizeof(double), len);
    if(!nums)
    {
        StackDestroy(opers);
        return 1;
    }

    local_calc->string = string;
    local_calc->curr_state = WAITINGNUM;
    local_calc->nums = nums;
    local_calc->opers = opers;
    local_calc->result = result;

    while(local_calc->curr_state < RESULT)
    {
        InputLut[local_calc->curr_state](local_calc);
    }

    retval = CalacAll(local_calc);
    
    StackDestroy(opers);
    StackDestroy(nums);
    
    return retval;
}


void LUTSetup()
{
    int i = 0, j = 0;

    for(; i < LUTSIZE1; ++i)
    {
        for(; j < LUTSIZE2; ++j)
        {
            StateLUT[i][j] = ErrorFunc;
        }
    }
    /*LUT[waitingnum]['('] = OpenParenthesis;*/  /*recieved "(" while waiting for number*/ /*push (to operstack*/
    /*LUT[waitingop]['*'] = Multi;*/             /*recieved "*" while waiting for operation*/ /*check priority - if last operator is higher, calc and push*/
    StateLUT[WAITINGOP]['+'] = Plus;              /*recieved "+" while waiting for operation*/
    StateLUT[WAITINGOP]['-'] = Minus;
    /*LUT[waitingop]['/'] = Div;*/
    /*LUT[waitingop][')'] = ClosedParenthesis;*/
    /*LUT[waitingop]['^'] = Pow;*/
    /*StateLUT[WAITINGOP]['\0'] = CalacAll;*/
    /*CalcLUT['*'] = calcMul;    */              /*perform multiplication of last two numbers*/
    CalcLUT['+'] = CalcPlus;
    CalcLUT['-'] = CalcMinus;
    /*CalcLUT['/'] = CalcDiv;
    CalcLUT['^'] = CalcPow;*/

}

void GetInputNum(calculator *calc)
{
    char *new_str = NULL;
    double num = 0.0;

    new_str = calc->string;
    num = strtod(new_str, &new_str);
    if(new_str == calc->string)
    {
        calc->curr_state = ERROR;
        return;
    }
    StackPush(calc->nums, (void*)&num);/*change string*/
    calc->curr_state = WAITINGOP;
}

void GetInputOper(calculator *calc)
{
    char *oper = NULL, *new_str = NULL;

    new_str = calc->string;
    strtod(new_str, &new_str);
    if(new_str == calc->string)
    {
        OperLUT[*new_str](calc); /*CHANGE sTATE!!! change string ptr*/
        return;
    }
    calc->curr_state = ERROR;
}

double CalcMinus(double num1, double num2)
{
    return (num2 + num1);
}


double CalcMinus(double num1, double num2)
{
    return (num2 - num1);
}

double CalacAll(calculator *calc)
{
    char oper = '\0';
    double res = 0.0, num1 = 0.0, num2 = 0.0;
    while(!StackIsEmpty(calc->opers))
    {
        oper = *(char*)StackPeek(calc->opers);
        StackPop(calc->opers);
        num1 = *(double*)StackPeek(calc->nums);
        StackPop(calc->nums);
        num2 = *(double*)StackPeek(calc->nums);
        StackPop(calc->nums);
        res = CalcLUT[oper](num1, num2);
        StackPush(calc->nums, (void*)&res);
    }

    return res;
}
