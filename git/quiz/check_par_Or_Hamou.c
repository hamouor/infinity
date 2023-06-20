#include <stdio.h>	/*printf*/

int CheckPar(char* str)
{
	void* check = Stack_Create(sizeof(char), strlen(str));
	while ('\0' != *str)
	{
		switch(*str)
		{
			case('(','[','{'):
				Stack_Push(check, *str);
				break;
			case(')'):
				if (*(char*)Stack_Peek(check) == '(')
				{
					Stack_Pop(check);
				}
				else
				{
					return 1;
				}
				break;
			case(']','}')
				if(*str - *(char*)Stack_Peek(check) == -2)
				{
					Stack_Pop(check);
				}
				else
				{
					return 1;
				}
				break;
		}	
		++str;
	}
	if (!Stack_Is_Empty)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
