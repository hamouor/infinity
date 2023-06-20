#include"string.h"
/*duplicates given str and returns pointer to duplicant*/
char* Strdup(const char* str)
	{
	size_t len = 0;
	char* dup = NULL;
	
	len = strlen(str);
	dup = malloc(len + 1);
	dup = strcpy(dup, str);
	return dup;
	}



