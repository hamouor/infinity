#include<stdio.h> /*printf*/
#include "ws4.h"

typedef void (*funcptr)(void); /*pointer to function variable*/
static funcptr printfuncs[255] = {0}; /*array of pointer to function variable. size is according to keyboard inputs*/

void InteractSwitch()
{
	char selection = '/0'; /*will house the users pressed key*/
	while ((int)(selection) != 27) /*ascii of Esc*/
	{
		selection = getc(stdin); /*accepting key press from user*/
		switch(selection)
		{
			case 'T':
				printf("\nT-pressed\n");
				break;
			case 'A':
				printf("\nA-pressed\n");
				break;
		}
	}
}

void InteractIf()
{
	char selection = '/0';/*will house the users pressed key*/
	while ((int)(selection) != 27) /*ascii of Esc*/
	{
		selection = getc(stdin);/*accepting key press from user*/
		if (selection == 'T')
		{
			printf("\nT-pressed\n");
		}
		else if (selection == 'A')
		{
			printf("\nA-pressed\n");
		}
	}
}

void InteractLut()
{
	char selection = '/0';/*will house the users pressed key*/
	printfuncs[(size_t)'A'] = *PrintA;
	printfuncs[(size_t)'T'] = *PrintT;
	while ((int)(selection) != 27) /*ascii of Esc*/
	{
		selection = getc(stdin);/*accepting key press from user*/
		printfuncs[(size_t)selection]();
	}		
}
	
void PrintT()
{
	printf("\nT-pressed\n");
}

void PrintA()
{
	printf("\nA-pressed\n");
}

