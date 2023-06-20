#include <stdio.h>

#include"trie.h"

int main()
{
    trie_ty* test = NULL;
    char path = 'a';

    test = TrieCreate(8);
    printf("size when 0 : %ld\n", TrieSize(test));  

    printf("%d\n%d\n",TrieCreateNewPath(test, &path), path);
    printf("making sure %d\n", path);  
    printf("size when 1 : %ld\n", TrieSize(test));  

    printf("%d\n%d\n",TrieFreePath(test, &path), path);
    printf("making sure %d\n", path);  
    printf("size when 0 : %ld\n", TrieSize(test));  


    printf("%d\n%d\n",TrieCreateNewPath(test, &path), path); 
    printf("size when 1 : %ld\n", TrieSize(test));  
 
    printf("making sure %d\n", path);  
    TrieDestroy(test);
    return 0;
}