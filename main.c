#include <stdio.h>
#include <stdlib.h>
#include "sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

void destroyerNoMalloc(void *p)
{
	return;
}

void integerTest() 
{
	SortedListPtr SL;
	SortedListIteratorPtr SLIter;

	/* Prepare objects to add in an array. */
	int i = 0;
	int inputArray[6];
	printf("LIST OF OBJECTS:\n");
	for(i=0; i<=5; i++){
		int j = rand()%200;
		printf("%i\t",j);
		inputArray[i] = j;
	}
	printf("\n\n");


	/* Create and fill sorted list with 5 items. */
	SL = SLCreate(compareInts,destroyerNoMalloc);
	for(i=0; i<=5; i++){
		printf("%i\t",inputArray[i]);
		SLInsert(SL,&inputArray[i]);
	}


	/* Testing:  Inserting duplicate object and removing two objects. */
	printf("\nTESTING FUNCTIONALITY:\n%i\t",inputArray[3]);
	SLInsert(SL,&inputArray[3]);
	printf("%i\t",inputArray[4]);
	SLRemove(SL, &inputArray[4]);
	printf("<head>\t");
	SLRemove(SL, SL->head->data);


	/* Create iterator and print list in order. */
	printf("\nPRINTING:\n");
	SLIter = SLCreateIterator(SL);
	i = 0;
	if(SLGetItem(SLIter) != NULL)
		printf("0\t%d\n", *(int *)SLGetItem(SLIter));

	do{
		i++;
		printf("%i\t",i);
		if(SLNextItem(SLIter) != NULL)
			printf("%d", *(int *)SLGetItem(SLIter));
		printf("\n");
	}while(i<5);



	/* Freeing data structures. */
	SLDestroyIterator(SLIter);
	SLDestroy(SL);

}


int main(){

	integerTest();

	return 0;
}