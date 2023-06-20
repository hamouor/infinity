#include"vector.h"
#include<stdio.h> /*printf*/
int main()
{
	vector_ty* myvect = NULL, *myvect2 = NULL;
	int testint = 15, testint2 = 5;
	myvect = VectorCreate(4,4);
	myvect2 = VectorCreate(8,4);
	VectorPushBack(myvect, (void*)&testint);
	VectorPushBack(myvect, (void*)&testint);
	VectorPushBack(myvect, (void*)&testint);	
	VectorPushBack(myvect, (void*)&testint);
	VectorPushBack(myvect, (void*)&testint);
	printf("%d\n", (5 - (int)VectorSize(myvect)));
	VectorPushBack(myvect2, (void*)&testint2);
	VectorPushBack(myvect2, (void*)&testint2);
	VectorPushBack(myvect2, (void*)&testint2);
	VectorPopBack(myvect2);
	printf("%d\n", (5 - *(int*)VectorGetAccessToElement(myvect2, 1)));
	printf("%d\n", (8 - (int)VectorCapacity(myvect)));
	printf("%d\n", VectorReserve(myvect, 16));
	printf("%d\n", (16 - (int)VectorCapacity(myvect)));
	VectorShrinkToFitSize(myvect);
	printf("%d\n", (5 - (int)VectorCapacity(myvect)));
	printf("%d\n", (5 - (int)VectorSize(myvect)));
	VectorDestroy(myvect);
	VectorDestroy(myvect2);
	return 0;	
}
