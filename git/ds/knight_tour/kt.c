#include <stddef.h> /*size_t*/
#include <stdlib.h>
#include <stdio.h>
#include"kt.h"


#define Ul -17
#define Ur -15
#define Dl 15
#define Dr 17
#define Ru -6
#define Rd 10
#define Lu -10
#define Ld 6
#define NO 20

typedef struct arra
{
    int moves[8];
    int counter;
}aux_ty;


static void UpDCounter(aux_ty *aux);
static int SortFunc(const void* a, const void* b);
static void UpDArr(int* arr, char flag);
static void CopArr(int* arr1, int* arr2);
static void LUTSetup(aux_ty *LUT);
static int KnightsRec(size_t* bita, aux_ty* LUT, int index, int *path, char flag);
static int condition(int a, int b, char flag);



static void PrintLut(aux_ty* aux);

static void PrintPath(int *path);
static void PrintBita(size_t *bita);



int KnightTour(int path[BOARD_SIZE], int start_index)
{
    aux_ty LUT[BOARD_SIZE];
    size_t bita = 0, mask = 1;
    int res = 0;
    char flag;


    LUTSetup(LUT);
    if (start_index == 49 || start_index == 24 || start_index == 27)
    {
        flag = 'b';
    }
    else
    {
        flag = 'a';
    }
    path[0] = start_index;
    bita = bita + (mask<<start_index);
    res = KnightsRec(&bita, LUT, start_index, path, flag);

    return 0;

}

static int KnightsRec(size_t* bita, aux_ty* LUT, int index, int *path, char flag)
{
    int i = 0;
    int min_access = 99;
    int move = -1;
    int counter = 0;
    int new_index = 64;
    int res = 0;
    size_t mask = 1;

    if(!(~(*bita)) || LUT[index].counter == 0)
    {
        return 63;
    }

    for(; i < 8; ++i)
    {
        move = LUT[index].moves[i]; 
        if (move == NO)
        {
            break;
        }
        if(!(((*bita)>>(index + move)) & mask))
        {
            --(LUT[index + move].counter);
            /*printf("current : %d checking : %d\n",index, index+move);
            PrintLut(&LUT[index+move]);*/

            counter = LUT[index + move].counter;
            if (condition(counter, min_access, flag))
            {
                min_access =counter;
                new_index = index + move;
            }
        }
    }

    *bita = *bita + (mask<<new_index);
    res = KnightsRec(bita, LUT, new_index, path, flag);

    path[res] = new_index;
    return res - 1;
}

static int condition(int a, int b, char flag)
{
    if(flag == 'a')
    {
        return a < b;
    }
    else
    {
        return a <= b;
    }
}
static void PrintBita(size_t *bita)
{
    int i = 0;

    printf("bita data:");
    for(; i < 64; ++i)
    {
        printf("%ld", ((*bita)>>i) & 1);
    }
    printf("\n");
}

static void PrintPath(int *path)
{
    int i = 0;

    printf("path data:");
    for(; i < 64; ++i)
    {
        printf("%d", path[i]);
    }
    printf("\n");
}

static void PrintLut(aux_ty* aux)
{
    int i = 0;

    printf("Lut data: moves:");
    for(; i < 8; ++i)
    {
        printf("%d,", aux->moves[i]);
    }
    printf("\n");
    printf("counter:%d\n", aux->counter);
} 


static void LUTSetup(aux_ty *LUT)
{
    int arra[8] = {Ul, Ur, Dl, Dr, Ru, Rd, Lu, Ld};
    int mod8res = 0, i = 0;

    for(; i < 64; ++i)
    {
        mod8res = i % 8;

        CopArr(arra, LUT[i].moves);
        
        if(mod8res == 0)
        {
            UpDArr(LUT[i].moves, 'l');
        }
        else if(mod8res == 1)
        {
            UpDArr(LUT[i].moves, 'L');
        }
        else if(mod8res == 6)
        {
            UpDArr(LUT[i].moves, 'R');
        }
        else if(mod8res == 7)
        {
            UpDArr(LUT[i].moves, 'r');
        }

        if(i < 8)
        {
            UpDArr(LUT[i].moves, 'u');
        }
        else if (i < 16)
        {
            UpDArr(LUT[i].moves, 'U');
        }
        else if(i > 55)
        {
            UpDArr(LUT[i].moves, 'd');
        }
        else if(i > 47)
        {
            UpDArr(LUT[i].moves, 'D');
        }
        
        qsort(LUT[i].moves, 8, sizeof(int), SortFunc);

        UpDCounter(&LUT[i]);

    }
}

static void CopArr(int* arr1, int* arr2)
{
    int i = 0;

    for(; i < 8; ++i)
    {
        *(arr2 + i) = *(arr1 + i);
    }
}


static void UpDArr(int* arr, char flag)
{
    if(flag == 'l')
    {
        *(arr) = NO;
        *(arr + 2) = NO;
        *(arr + 6) = NO;
        *(arr + 7) = NO;

        return;
    }

    if(flag == 'L')
    {
        *(arr + 6) = NO;
        *(arr + 7) = NO;
        
        return;
    }

    if(flag == 'r')
    {
        *(arr + 1) = NO;
        *(arr + 3) = NO;
        *(arr + 4) = NO;
        *(arr + 5) = NO;

        return;
    }

    if(flag == 'R')
    {
        *(arr + 4) = NO;
        *(arr + 5) = NO;
        
        return;
    }

    if(flag == 'u')
    {
        *(arr) = NO;
        *(arr + 1) = NO;
        *(arr + 4) = NO;
        *(arr + 6) = NO;

        return;
    }

    if(flag == 'U')
    {
        *(arr) = NO;
        *(arr + 1) = NO;
        
        return;
    }

    if(flag == 'd')
    {
        *(arr + 2) = NO;
        *(arr + 3) = NO;
        *(arr + 5) = NO;
        *(arr + 7) = NO;

        return;
    }

    if(flag == 'D')
    {
        *(arr + 2) = NO;
        *(arr + 3) = NO;
        
        return;
    }
}


static int SortFunc(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

static void UpDCounter(aux_ty *aux)
{
    int i = 0;
    
    aux->counter = 0; 
    
    while(i < 8 && aux->moves[i] != NO)
    {
        ++aux->counter;
        ++i;
    }
    /*printf("%d\n", aux->counter);*/
}