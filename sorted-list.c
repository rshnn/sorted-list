
#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"



/*
	Creates and initializes the sorted list structure. 
*/
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){

	SortedListPtr list 	= (SortedListPtr) malloc(sizeof(struct SortedList));

	if(list == NULL){
		return NULL;
	}

	list->head 			= NULL;
	list->comparator	= cf;
	list->destroyer 	= df;

	return list;
}



/*
	destroyNode will recursively free all of the nodes of a linked list.
	SLDestroy will use destroyNode to free the dynamic memory of list structure.
 */

void destroyNode(Node* n, DestructFuncT df){

	if(n == NULL){
		return;
	}
	destroyNode(n->next, df);
	df(n->data);
	free(n);
	return;
}

void SLDestroy(SortedListPtr list){
	destroyNode(list->head, list->destroyer);
	free(list);
}





/* 
 	SLInset will insert a new object into the sorted list.
 		Sorted order is maintained with the comparator function.
 		Ignores duplicates.
 	If the function succeeds, it returns 1, otherwise it returns 0.
 */

int SLInsert(SortedListPtr list, void *newObj){
	if(newObj == NULL){
		return 0;
	}

	Node*	temp	= (Node*)malloc(sizeof(Node));

	if(temp == NULL){
		printf("Error. Failure to allocate memory for new object.\n");
		return 0;
	}

	/* Initialize node to add. */
	temp->data 			= newObj;
	temp->pointerCount	= 0;
	CompareFuncT cf 	= list->comparator;


	Node* 	current		= list->head;
	Node* 	previous	= NULL;

	while(current != NULL && cf(current->data, newObj) > 0){
		if(current!=NULL){
			//printf("%d %s vs %s\t",cf(current->data, newObj), *(char**)current->data, *(char**)newObj);
		}
		previous 	= current;
		current 	= current->next;
	}
	if(current!=NULL){
			//printf("%d %s vs %s\t",cf(current->data, newObj), *(char**)current->data, *(char**)newObj);
	}




	if(current == NULL){

		printf("Current IS NULL\t");

		if(previous == NULL){
			/* This is the first node of the list. */
			list->head 		= temp;
			printf("Successfully added first object.\n");
		} 
		else{
			previous->next 	= temp;
			printf("Successfully added new object at end of list.\n");
		}

		temp->next = NULL;
	} 
	else{
		if(cf(current->data, newObj) == 0){
			/* Duplicate node. Do not add to list. */
			free(temp);
			if(current->data != newObj){
				list->destroyer(newObj);
			}
			printf("Duplicate object. Was not added to list.\n");
			return 0;
		}
		if(previous == NULL){
			/* Temp is the new head of the list. */
			temp->next 		= current;
			list->head 		= temp;
			printf("New head.\t");
		}
		else{
			temp->next 		= current;
			previous->next 	= temp;
		}
		printf("Successfully added new object.\n");

	}
	temp->pointerCount++;
	return 1;

}




/*	
	HELPER FUNCTION.
	checkNodeValidity will free the input node if it possesses no pointers.
*/
void checkNodeValidity(Node *n, DestructFuncT df) {
	if(n == NULL) {
		return;
	}
	if(n->pointerCount <= 0) {
		df(n->data);
		free(n);
		return;
	}
}


/*
 	SLRemove will remove a given Object from the sorted list.
 		Ordering is maintained.  Does not change the object pointer.
 
 	If the function succeeds, it returns 1, otherwise it returns 0.
 */
int SLRemove(SortedListPtr list, void *newObj){
	Node* 	previous 	= NULL;
	Node*	current 	= NULL;

	for(current = list->head; current != NULL; current = current->next){
		if(current->data == newObj){
			break;
		}
		previous = current;
	}
	if(current == NULL){
		/* Could not find target. */
		return 0;
	}
	if(previous == NULL){
		/* Target is the head of the list. */
		list->head = list->head->next;
		printf("Replaced head of list.\t");
	}
	else{
		/* Successfully found target.  Remove from list. */
		previous->next = current->next;
	}
	current->pointerCount--;
	printf("Removed object. \n");
	checkNodeValidity(current, list->destroyer);
	return 1;
}




/*
 	SLCreateIterator initializes the iterator structure.
		Points to the first item of the sorted list if non-empty.
		If sorted list is empty, returns null pointer.
 	Returns a non-NULL pointer to the iterator structure.  Otherewise, NULL.
 */

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){

	if(list == NULL){
		/* Sorted List structure DNE. */
		return NULL;
	}
	if(list->head == NULL){
		/* Sorted list is initialized, but empty. */
		return NULL;
	}
	SortedListIteratorPtr iterator 	= (SortedListIteratorPtr)malloc(sizeof(struct SortedListIterator));
	iterator->iterNode	= list->head;
	iterator->destroyer	= list->destroyer;
	list->head->pointerCount++;
	return iterator;
}





/*
	SLDestroyIterator frees the iterator structure.  Sorted list unaffected.
 */

void SLDestroyIterator(SortedListIteratorPtr iter){
	if(iter == NULL){
		printf("Error: Iterator object does not exist.\n");
		return;
	}
	if(iter->iterNode != NULL){
		iter->iterNode->pointerCount--;
		checkNodeValidity(iter->iterNode, iter->destroyer);
	}
	free(iter);
}




/*
	SLGetItem returns a void pointer to the data associated with iterNode.
		Will return 0 if iterator advances out of bounds or if iterator DNE.
*/

void * SLGetItem( SortedListIteratorPtr iter ){

	if(iter == NULL){
		printf("Error: Iterator object does not exist.\n");
		return NULL;
	}
	if(iter->iterNode == NULL){
		return 0;
	}
	return iter->iterNode->data;
}




/*

 * One complication you MUST consider/address is what happens if a
 * sorted list associated with an iterator is modified while that
 * iterator is active.  For example, what if an iterator is "pointing"
 * to some object in the list as the next one to be returned but that
 * object is removed from the list using SLRemove() before SLNextItem()
 * is called.
 *

 	SLNextItem increments the iterator and returns data of the next node.
 	Returns NULL when at end of list.

 */

void * SLNextItem(SortedListIteratorPtr iter){

	Node* 	temp;

	if(iter == NULL){
		printf("Error: Iterator object does not exist.\n");
		return NULL;
	}
	if(iter->iterNode == NULL){
		return NULL;
	}

	temp 	= iter->iterNode;
	iter->iterNode->pointerCount--;
	//printf("Next Item:\t%s\t\n", (char*)(iter->iterNode->data));

	iter->iterNode 	= iter->iterNode->next;
	checkNodeValidity(temp, iter->destroyer);

	if(iter->iterNode == NULL){
		return NULL;
	}
	iter->iterNode->pointerCount++;
	//printf("Current Item:\t%s\n", (char*)(iter->iterNode->data));
	return iter->iterNode->data;

}





