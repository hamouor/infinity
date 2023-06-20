#include"slist.h"

#include <stdlib.h> /*size_t*/
#include<stdio.h> /*printf*/

int Matcha(void *a, void *b);
int userfunction(void* data, void* parameter);

int main()
{
	slist_iter_ty it = NULL;
	slist_ty* list = NULL;
	size_t len = 0;
	int testint = 15, testint2 = 5, testint3 = 9, testint4 = 3, testint5 = 7, testint6 = 0;
	
	list = SlistCreate();
	it = SlistEnd(list);
	len = SlistCount(list);
	printf("len is 0:%zu\n", len);
	it = SlistInsertBefore(it, (void*)&testint);
	len = SlistCount(list);
	printf("len is 1:%zu\n", len);
	it = SlistRemove(it);
	it = SlistInsertBefore(it, (void*)&testint);
	it = SlistInsertBefore(it, (void*)&testint2);
	it = SlistInsertBefore(it, (void*)&testint3);
	it = SlistInsertBefore(it, (void*)&testint4);	
	len = SlistCount(list);
	printf("len is 4:%zu\n", len);
	it = SlistFind(SlistBegin(list), SlistEnd(list), Matcha, (void*)&testint2);
	printf("found%d so value is %d\n",testint2,*(int*)SlistGetData(it));
	it = SlistNext(SlistBegin(list));
	printf("should be%d so value is %d\n",testint3,*(int*)SlistGetData(it));
	SlistSetData(it, (void*)&testint6);
	printf("should be%d so value is %d\n",testint6,*(int*)SlistGetData(it));
	testint6 = SlistForEach(SlistBegin(list), SlistEnd(list), userfunction, (void *)&testint5);
	printf("success of foreach%d\n", testint6);
	SlistDestroy(list);
	
	return 0;
}

int Matcha(void* a, void *b)
{
	if ( *(int*)a == *(int*)b )
	{
	return 1;
	}
	return 0;
}

int userfunction(void* data, void* parameter)
{
	*(int*)data += *(int*)parameter;
	return 1;
}
