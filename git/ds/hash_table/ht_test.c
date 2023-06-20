#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ht.h"
char *strdup(const char *s);

int HashFunc(const void* data)
{
    char* letter = NULL;

    letter = (char*)data;
    
    if(*letter >= 'A' && *letter <='Z')
    {
        return *letter - 'A';
    }
    if(*letter >= 'a' && *letter <= 'z')
    {
        return *letter - 'a' + 26;
    }
    return 52;
}

int comp_func(void *data, void *param)
{
    return !strcmp((char*)data, (char*)param);
}

int foreach(void* data, void* data2)
{

    free(data);


    return 0;
}

int foreach2(void* data, void* data2)
{

    if(!(data))
    {
        /*printf("%s\n",(char*)(data));*/
        printf("yahel\n"/*,(char*)(data)*/);

    }

    return 0;
}

int main()
{
    ht_ty *new = NULL;
    int g = 10;
    FILE *dictionary = NULL;
    char line[256];
    char delete_flag = 'a';
    char *ptr = "web";


    dictionary = fopen("/usr/share/dict/words", "r");

    new = HTCreate(HashFunc, comp_func, 53);

    while (EOF != fscanf(dictionary, "%s" ,line ))
    {
        if(HTInsert(new, (void*)strdup(line)))
        {
            return 1;
        }
    }
    
    printf("shtok\n");
    fscanf(stdin, "%s",line);
    printf("i found this : %s", (char*)HTFind(new, (void*)line));


    fclose(dictionary);


/*
    printf("size when empty: %ld.\nis empty when empty:%d\n", HTSize(new), HTIsEmpty(new));

    HTInsert(new, (void*)&g);

    printf("size when has 1: %ld.\nis empty when not empty:%d\n", HTSize(new), HTIsEmpty(new));


    printf("i removed this:%d\n",*(int*)HTRemove(new, (void*)&g));

*/
    HTForEach(new, foreach, (void*)delete_flag);

    HTDestroy(new);
    return 0;
}