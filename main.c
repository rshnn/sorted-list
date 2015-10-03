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
	char *s1 = *(char**)p1;
	char *s2 = *(char**)p2;

	return strcmp(s1, s2);
}


/*  
	Structure defintion and comparator function for type band.
	Comparator function will return 0 if equal and negative arg1's year is less than arg2's. 
*/
typedef struct Band
{
	char* 			name;
	int 			formationYear;
} band;

int compareBands(void* p1, void* p2){

	band* b1 = (band *)p1;
	band* b2 = (band *)p2;
	
	int y1 = b1->formationYear;
	int y2 = b2->formationYear;

	if(y1-y2 == 0){
		if(strcmp(b1->name, b2->name)==0)
			return 0;
		else
			return 1;
	}
	return y1 - y2;
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
	printf("\nTESTING FUNCTIONALITY:\n%i\t",inputArray[3]);
	SLInsert(SL,&inputArray[3]);
	printf("%i\t",inputArray[4]);
	SLRemove(SL, &inputArray[4]);
	printf("%i\t", *(int*)SL->head->data);
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


void stringTest()
{
	printf("\n\t\tSTRING TESTING\n");
	SortedListPtr SL;
	SortedListIteratorPtr SLIter;

	/* Prepare objects to add in an array. */
	int i = 0;
	char* inputArray[15] = {"modestmouse", "ledzeppelin", "beyonce", \
								"blink182", "mastodon", "nujabes", "radiohead"};
	printf("LIST OF OBJECTS:\n");
	for(i=0; i<=5; i++){
		printf("%s\t",inputArray[i]);
	}
	printf("\n\n");


	/* Create and fill sorted list with 5 items. */
	 SL = SLCreate(compareStrings,destroyerNoMalloc);
	for(i=0; i<=5; i++){
		printf("Add %15s\t\t",inputArray[i]);
		SLInsert(SL,&inputArray[i]);
	}


	/* Testing:  Inserting duplicate object and removing two objects. */
	printf("\nTESTING FUNCTIONALITY:\n%15s\t\t",inputArray[3]);
	SLInsert(SL,&inputArray[3]);
	printf("%15s\t\t",inputArray[4]);
	SLRemove(SL, &inputArray[4]);
	printf("%15s\t\t", *(char**)SL->head->data);
	SLRemove(SL, SL->head->data);

	printf("Add %15s\t\t",inputArray[6]);
	SLInsert(SL,&inputArray[6]);


	/* Create iterator and print list in order. */
	printf("\nPRINTING:\n");
	SLIter = SLCreateIterator(SL);
	i = 0;
	if(SLGetItem(SLIter) != NULL)
		printf("0\t%s\n", *(char **)SLGetItem(SLIter));

	SLRemove(SL,&inputArray[1]);

	do{
		i++;
		printf("%i\t",i);
		if(SLNextItem(SLIter) != NULL)
			printf("%s", *(char **)SLGetItem(SLIter));
		printf("\n");
	}while(i<5);



	/* Freeing data structures. */
	SLDestroyIterator(SLIter);
	SLDestroy(SL);
	

}

void bandTest()
{
	printf("\n\t\tBAND STRUCT TESTING\n");
	SortedListPtr SL;
	SortedListIteratorPtr SLIter;
	int i = 0;

	/* Prepare objects to add. */
	band* modestmouse	=	(band *)malloc(sizeof(band));
	band* ledzeppelin	=	(band *)malloc(sizeof(band));
	band* destinyschild	=	(band *)malloc(sizeof(band));
	band* blink182		=	(band *)malloc(sizeof(band));
	band* mastodon		=	(band *)malloc(sizeof(band));
	band* nujabes		=	(band *)malloc(sizeof(band));

	modestmouse->name 	= 	"Modest Mouse";		modestmouse->formationYear	=	1992;
	ledzeppelin->name 	= 	"Led Zeppelin";		ledzeppelin->formationYear	= 	1968;
	destinyschild->name = 	"Destiny's Child";	destinyschild->formationYear = 	1990;
	blink182->name 		= 	"blink 182";		blink182->formationYear		=	1992;
	mastodon->name 		= 	"Mastodon";			mastodon->formationYear 	= 	2000;
	nujabes->name 		= 	"Nujabes";			nujabes->formationYear 		= 	1996;

	band* inputArray[6] 	= 	{modestmouse, blink182, destinyschild, ledzeppelin, mastodon, nujabes};


	/* Create and fill sorted list with 5 items. */
	SL = SLCreate(compareBands,destroyerWithMalloc);
	SLInsert(SL, modestmouse);
	SLInsert(SL, destinyschild);
	SLInsert(SL, blink182);
	SLInsert(SL, mastodon);
	SLInsert(SL, nujabes);
	SLInsert(SL, ledzeppelin);


	/* Testing:  Inserting duplicate object and removing two objects. */
	printf("\nTESTING FUNCTIONALITY:\n%15s\t\t",inputArray[3]->name);
	SLInsert(SL,&inputArray[3]->name);
		printf("%15s\t\t",inputArray[2]->name);
	SLRemove(SL, &inputArray[2]->name);
		printf("%15s\t\t", *(char**)SL->head->data);
	SLRemove(SL, SL->head->data);


	/* Create iterator and print list in order. */
	printf("\nPRINTING:\n");
	SLIter = SLCreateIterator(SL);

	if(SLGetItem(SLIter) != NULL){
		printf("0\t%s\n", ((band*)SLGetItem(SLIter))->name);
	}
	do{
		i++;
		printf("%i\t",i);
		if(SLNextItem(SLIter) != NULL)
			printf("%s", ((band*)SLGetItem(SLIter))->name);
		printf("\n");
	}while(i<5);



	/* Freeing data structures. */
	SLDestroyIterator(SLIter);
	SLDestroy(SL);
	

}


int main(int argc, char** argv){

	char* errMsg = "\nUsage error.  Please use keyword \"integer\", \"string\", or \"struct\" as arg1 value for each respective example.\n";

	if(argc == 1){
		fprintf(stderr, "%s", errMsg);
		exit(0);
	}

	
	if(!strcmp(argv[1],"integer"))
		integerTest();
	else if(!strcmp(argv[1],"string"))
		stringTest();
	else if(!strcmp(argv[1],"struct"))
		bandTest();
	else
		fprintf(stderr, "%s", errMsg);

	return 0;
}