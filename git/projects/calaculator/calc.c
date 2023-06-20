#include <math.h>   /*pow*/
#include <stdlib.h> /*strtod*/
#include <string.h> /*strlen*/
#include <assert.h> /*assert*/

#include "calc.h"
#include "stack.h"

#define CHARSPAN    127
#define NUMOFOPERATIONS    7
#define OPENPRIOR    2
#define PLUSMINUSPRIOR    3
#define MULTDIVPRIOR    4
#define POWPRIOR    5
#define CLOSEPRIOR    2
#define ILLEGALPRIOR    1



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


typedef void(*InputFunc)(calculator *calc);
typedef double(*CalcFunc)(double num1, double num2, calculator * calc);
typedef void(*CalcPrior)(calculator *calc, char oper);




InputFunc InputLUT[2];
InputFunc OperLUT[CHARSPAN];
CalcFunc CalcLUT[CHARSPAN];
int PriorLut[CHARSPAN];
CalcPrior CalcPriorLUT[CHARSPAN];

int InitFlag = 0;

void GetInputNum(calculator *calc);

void GetInputOper(calculator *calc);

double CalcPlus(double num1, double num2, calculator *calc);

double CalcMinus(double num1, double num2, calculator *calc);

double CalcMult(double num1, double num2, calculator *calc);

double CalcDiv(double num1, double num2, calculator *calc);

double CalcPow(double num1, double num2, calculator *calc);

void CalacAll(calculator *calc);

void OperMinus(calculator *calc);

void OperPlus(calculator *calc);

void LutInit();

void ErrorOper(calculator * calc);

void OperEnd(calculator *calc);

void OperMult(calculator *calc);

void OperDiv(calculator *calc);

void OperPow(calculator *calc);

void OperClos(calculator *calc);

void CalcPriorF(calculator *calc, char input_oper);

void CalcPriorC(calculator *calc, char input_oper);

int condition (calculator *calc, char oper);


int Calc(char *string, double *result)
{
    stack_ty *opers = NULL, *nums = NULL;
    size_t len = 0;
    calculator local_calc;

    assert(string);

    *result = 0;
    LutInit();
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

    local_calc.string = string;
    local_calc.curr_state = WAITINGNUM;
    local_calc.nums = nums;
    local_calc.opers = opers;
    local_calc.result = result;

    while(local_calc.curr_state < RESULT)
    {        
        InputLUT[local_calc.curr_state](&local_calc);
    }

    if (local_calc.curr_state == ERROR)
    {
        return 1;
    }
    CalcPriorF(&local_calc, 'a'); /*this is calculate all*/
    if (StackSize(opers) > 0)
    {
        StackDestroy(opers);
        StackDestroy(nums);
        return 1;
    }
    StackDestroy(opers);
    StackDestroy(nums);
    
    return 0;
}

void GetInputNum(calculator *calc)
{
    char *new_str = NULL;
    double num = 0.0;

    new_str = calc->string;
    num = strtod(new_str, &new_str);
    if(new_str == calc->string)
    {
        if(*new_str == '(')  
        {
            StackPush(calc->opers, (void*)new_str);
            ++calc->string;
            return;
        }
        calc->curr_state = ERROR;
        return;
    }
    StackPush(calc->nums, (void*)&num);
    calc->string = new_str;
    calc->curr_state = WAITINGOP;
}

void GetInputOper(calculator *calc)
{
    char *new_str = NULL;

    new_str = calc->string;
    OperLUT[*new_str](calc); 
    return;
}
/*each newly recieved operation will check the priority of previous ones, calculate the result so far if needed and insert it to the stack*/
void OperSpace(calculator *calc)
{
    ++calc->string;
}

void OperMult(calculator *calc)
{
    CalcPriorLUT['*'](calc, '*');
    StackPush(calc->opers, (void*)calc->string);
    ++calc->string;
    calc->curr_state = WAITINGNUM;
}

void OperClos(calculator *calc)
{
    CalcPriorLUT[')'](calc, ')');
    ++calc->string;
}

void OperDiv(calculator *calc)
{
    CalcPriorLUT['/'](calc, '/');
    StackPush(calc->opers, (void*)calc->string);
    ++calc->string;
    calc->curr_state = WAITINGNUM;
}

void OperPow(calculator *calc)
{
    CalcPriorLUT['^'](calc, '^');
    StackPush(calc->opers, (void*)calc->string);
    ++calc->string;
    calc->curr_state = WAITINGNUM;
}

void OperPlus(calculator *calc)
{
    CalcPriorLUT['+'](calc, '+');
    StackPush(calc->opers, (void*)calc->string);
    ++calc->string;
    calc->curr_state = WAITINGNUM;
}

void OperMinus(calculator *calc)
{
    CalcPriorLUT['-'](calc, '-');
    StackPush(calc->opers, (void*)calc->string);
    ++calc->string;
    calc->curr_state = WAITINGNUM;
}

void OperEnd(calculator *calc)
{
    calc->curr_state = RESULT;
}

/*HERE are the calculation functions - these will perform each of the operations they are responsible to*/

double CalcOpen(double num1, double num2, calculator *calc)    
{
    StackPush(calc->nums, (void*)&num2);
    return num1;
}

double CalcMult(double num1, double num2, calculator *calc)
{
    return (num2 * num1);
}

double CalcDiv(double num1, double num2, calculator *calc)
{
    return (num2 / num1);
}

double CalcPow(double num1, double num2, calculator *calc)
{
    return (pow(num2, num1));
}

double CalcPlus(double num1, double num2, calculator * calc)
{
    return (num2 + num1);
}

double CalcMinus(double num1, double num2, calculator * calc)
{
    return (num2 - num1);
}

void ErrorOper(calculator * calc)
{
    calc->curr_state = ERROR;
}

void LutInit()
{
    
    int i = 0;
    if(InitFlag == 1)
    {
        return;
    }    
    InitFlag = 1;
    InputLUT[0] = GetInputNum;
    InputLUT[1] = GetInputOper;
    for(i = 0; i < CHARSPAN; ++i)
    {
        OperLUT[i] = ErrorOper; 
        CalcLUT[i] = NULL;
        PriorLut[i] = ILLEGALPRIOR;
        CalcPriorLUT[i] = NULL;
    }
    OperLUT['\0'] = OperEnd;
    OperLUT['+'] = OperPlus;
    OperLUT['-'] = OperMinus;
    OperLUT['*'] = OperMult;
    OperLUT['/'] = OperDiv;
    OperLUT['^'] = OperPow;
    OperLUT[')'] = OperClos;
    OperLUT[' '] = OperSpace;

    CalcLUT['('] = CalcOpen;
    CalcLUT['+'] = CalcPlus;
    CalcLUT['-'] = CalcMinus;
    CalcLUT['*'] = CalcMult;
    CalcLUT['/'] = CalcDiv;
    CalcLUT['^'] = CalcPow;

    PriorLut['('] = OPENPRIOR;
    PriorLut['+'] = PLUSMINUSPRIOR;
    PriorLut['-'] = PLUSMINUSPRIOR;
    PriorLut['*'] = MULTDIVPRIOR;
    PriorLut['/'] = MULTDIVPRIOR;
    PriorLut['^'] = POWPRIOR;
    PriorLut[')'] = CLOSEPRIOR;

    CalcPriorLUT['+'] = CalcPriorF;
    CalcPriorLUT['-'] = CalcPriorF;
    CalcPriorLUT['*'] = CalcPriorF;
    CalcPriorLUT['/'] = CalcPriorF;
    CalcPriorLUT['^'] = CalcPriorF;
    CalcPriorLUT[')'] = CalcPriorC;
}

/*calculating the input so far according to the priority of the newly recieved input operation for +-/*^*/

void CalcPriorF(calculator *calc, char oper)
{
    char opera = '\0';
    double num1 = 0.0, num2 = 0.0;

    while(StackSize(calc->nums) > 1 && PriorLut[*(char*)StackPeek(calc->opers)] >= PriorLut[oper])
    {
        if (*(char*)StackPeek(calc->opers) == '(')
        {
            break;
        }
        opera = *(char*)StackPeek(calc->opers);
        StackPop(calc->opers);
        num1 = *(double*)StackPeek(calc->nums);
        StackPop(calc->nums);
        num2 = *(double*)StackPeek(calc->nums);
        StackPop(calc->nums);
        *(calc->result) = CalcLUT[opera](num1, num2, calc);
        StackPush(calc->nums, (void*)(calc->result));
    }
}
/*same as above but only for )*/
void CalcPriorC(calculator *calc, char input_oper)
{
    char oper = '\0';
    double num1 = 0.0, num2 = 0.0;

    while(StackSize(calc->nums) > 1 && *(char*)StackPeek(calc->opers) != '(')
    {
        oper = *(char*)StackPeek(calc->opers);
        StackPop(calc->opers);
        num1 = *(double*)StackPeek(calc->nums);
        StackPop(calc->nums);
        num2 = *(double*)StackPeek(calc->nums);
        StackPop(calc->nums);
        *(calc->result) = CalcLUT[oper](num1, num2, calc);
        StackPush(calc->nums, (void*)(calc->result));
    }

    if (StackSize(calc->opers) == 0 || *(char*)StackPeek(calc->opers) != '(')
    {
        calc->curr_state = ERROR;
    }
    StackPop(calc->opers);
}