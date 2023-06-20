#include<stdio.h> /*printf*/
#include<stdlib.h> /*system*/
#include<string.h>
#include "ws5.h"

typedef void (*funcptr)(int); /*pointer to function recieving int and returning void*/
typedef int (*funcptr2)(const char*,const char*,size_t);/*pointer specificaly for strncmp*/
typedef int (*funcptr3)(char*,char*);/*will house the functions -exit -count etc..*/

#define BUFFER_SIZE 1000
/*struct composed of int tnd pointer to function*/
struct IntNFunc
{
	int valu;
	funcptr Func;
};
/*composed of string and two functions*/
struct StrNFuncs
{
	char val[10];/*define len and use instead of 10*/
	funcptr2 Func; 
	funcptr3 Func2;
};

static struct StrNFuncs Operations[5]={0};

void ThePrintMe()
{
	int arr_size = 10;
	struct IntNFunc Print_me[10];
	int i;
	
	for(i=0;i<arr_size;++i)
	{
		Print_me[i].valu=i;
		Print_me[i].Func = PrintThisInt;
	}
	for(i=0;i<arr_size;++i)
	{
		Print_me[i].Func(Print_me[i].valu);
	}

}

void PrintThisInt(int val)
{
	printf("\n%d\n", val);
}
	
void EnterFile()
{
	char filename[BUFFER_SIZE];
    	int success = 0;	
	printf("\nEnter file name: ");
    	scanf("%s\n", filename);
	while (0 == success)
	{
		success = Interact(filename);
	}
}

int Interact(char* file_name) 
{
	char opfromuser[BUFFER_SIZE];
	int i = 0;
	int flag = 0;
	int retval = 0; /*will house the return value before returning it*/
	FILE *pfile = fopen(file_name, "r+");
	strcpy(Operations[0].val, "-remove"); /*initialization of array funcs and names*/
	strcpy(Operations[1].val, "-count");
	strcpy(Operations[2].val, "-exit");
	strcpy(Operations[3].val, "-append");		
	strcpy(Operations[4].val, "<");
	Operations[0].Func = strncmp;
	Operations[1].Func = strncmp;
	Operations[2].Func = strncmp;	
	Operations[3].Func = strncmp;
	Operations[4].Func = strncmp;
	Operations[0].Func2 = Rem;
	Operations[1].Func2 = Count;
	Operations[2].Func2 = Exit;	
	Operations[3].Func2 = Append;	
	Operations[4].Func2 = Prepend;
	
	if (pfile == NULL)   /*checks if file is existing*/
	{
		printf("\nawsome! now enter a real file name\n");
		return 1;
	}
	fclose(pfile);    	
	printf("\nEnter operation: ");
    	fgets(opfromuser, BUFFER_SIZE, stdin);
    	for(; i < 5; ++i)  /* checks operation entered by user to be same as operations in the array*/
    	{
    		if (0 == Operations[i].Func(opfromuser, Operations[i].val, strlen(Operations[i].val)))/*compares command by user to list of commands according to the listing length*/
    		{
    			retval = (Operations[i].Func2(file_name, opfromuser));
    			return retval;
    			flag = 1; /*indicates an action has been made and no need to append*/
    		}
    	}
    	if (flag == 0)
    	{
    		return (Append(file_name, opfromuser));
    	}
    	
	return 1;
}

int Append(char* file_name, char* dataToAppend)
{
	FILE *pfile = fopen(file_name, "a");
    	fputs(dataToAppend, pfile);
    	fclose(pfile);
	return 0;
}

int Rem(char* file_name, char* dataToAppend)
{
	return remove(file_name);
}

int Count(char* file_name, char* dataToAppend)
{
	char c = '/0';	
	FILE *pfile = fopen(file_name, "r+");
	int count_lines = 0;
	for (c = getc(pfile); c != EOF; c = getc(pfile))
        {
        	if (c == '\n')
		{
			count_lines = count_lines + 1;
		}  
	}
    	fclose(pfile);
    	printf("The file %s has %d lines\n ", file_name, count_lines);
	return 0;
}

int Exit(char* file_name, char* dataToAppend)
{
	return 1;
}

int Prepend(char* file_name, char* dataToPrepend)
{
	FILE *opfile; 
	FILE *pfile;  
	char c = '/0';	
	rename(file_name, "temp.c");
    	opfile = fopen("temp.c", "r+");
    	pfile = fopen(file_name, "a");    	
    	fputs(dataToPrepend+1, pfile);
	for (c = getc(opfile); c != EOF; c = getc(opfile))
        {
    		fputc(c, pfile);
    	}
    	Rem("temp.txt", "f");
    	fclose(pfile);
	return 0;	
}
