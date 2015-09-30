#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"


/* Comparator function for pointers to integers. */
int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

/* Comparator function for pointers to stings. */
int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}




/* Destroyer functions for dynamically and nondynamically allocated pointers. */
void destroyerWithMalloc(void* pointer){
	free(pointer);
}
void destroyerNoMalloc(void* pointer)
{
	return;
}



/* Test function for created an integer sorted-list. */
void integerTest() 
{
	printf("\n\t\tINTEGER TESTING\n");
	SortedListPtr SL;
	SortedListIteratorPtr SLIter;

	/* Prepare objects to add in an array. */
	int i = 0;
	int inputArray[6];
	printf("LIST OF OBJECTS:\n");
	for(i=0; i<=5; i++){
		int j = rand()%100;
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
	// printf("\nTESTING FUNCTIONALITY:\n%i\t",inputArray[3]);
	// SLInsert(SL,&inputArray[3]);
	// printf("%i\t",inputArray[4]);
	// SLRemove(SL, &inputArray[4]);
	// printf("%i\t", *(int*)SL->head->data);
	// SLRemove(SL, SL->head->data);


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


void stringTest()
{
	printf("\n\t\tSTRING TESTING\n");
	SortedListPtr SL;
	SortedListIteratorPtr SLIter;

	/* Prepare objects to add in an array. */
	int i = 0;
	char* inputArray[15] = {"b", "a", "f", \
								"d", "e", "c"};
	printf("LIST OF OBJECTS:\n");
	for(i=0; i<=5; i++){
		printf("%s\t",inputArray[i]);
	}
	printf("\n\n");


	/* Create and fill sorted list with 5 items. */
	 SL = SLCreate(compareStrings,destroyerNoMalloc);
	for(i=0; i<=5; i++){
		printf("%15s\t\t",inputArray[i]);
		SLInsert(SL,&inputArray[i]);
	}


	/* Testing:  Inserting duplicate object and removing two objects. */
	// printf("\nTESTING FUNCTIONALITY:\n%15s\t\t",inputArray[3]);
	// SLInsert(SL,&inputArray[3]);
	// printf("%15s\t\t",inputArray[4]);
	// SLRemove(SL, &inputArray[4]);
	// printf("%15s\t\t", *(char**)SL->head->data);
	// SLRemove(SL, SL->head->data);


	/* Create iterator and print list in order. */
	printf("\nPRINTING:\n");
	SLIter = SLCreateIterator(SL);
	i = 0;
	if(SLGetItem(SLIter) != NULL)
		printf("0\t%s\n", *(char **)SLGetItem(SLIter));
	do{
		i++;
		printf("%i\t",i);
		if(SLNextItem(SLIter) != NULL)
			printf("%s", *(char **)SLGetItem(SLIter));
		printf("\n");
	}while(i<5);



	// /* Freeing data structures. */
	// SLDestroyIterator(SLIter);
	// SLDestroy(SL);
	

}



int main(){

	//integerTest();
	stringTest();

	printf("\n\n%d\n",strcmp("aaa","baa"));


	return 0;
}