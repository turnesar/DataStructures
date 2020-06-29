/*
Name: Sarah Turner turnesar@oregonstate.edu
Date: 11 Oct 2018
CS 261 Assignment 3
*/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	list->frontSentinel = (struct Link*) malloc(sizeof(struct Link));
	assert(list->frontSentinel);
	list->backSentinel = (struct Link*) malloc(sizeof(struct Link));
	assert(list->backSentinel);
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	list->size =0;		
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	struct Link* newb = (struct Link*) malloc(sizeof(struct Link));
	assert(newb!=0);
	newb->next = link;
	newb->prev = link->prev;
	link->prev->next = newb;
	link->prev = newb;
	newb->value = value;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != NULL);
	link->next->prev = link->prev;
	link->prev->next = link->next;
	free(link);
	link = 0;
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while(list->size>0){
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	list->frontSentinel=0;
	list->backSentinel=0;
	free(list);
	list=0;
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(!linkedListIsEmpty(list));
	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(!linkedListIsEmpty(list));
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(!linkedListIsEmpty(list));
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	return list->size==0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list!=NULL);
	struct Link* temp = list->frontSentinel->next;
	if(linkedListIsEmpty(list)){
		printf("No links in list\n");
	}
	else{
		printf("Values in list:\n");
		while(temp!=list->backSentinel){
			if(temp->next == list->backSentinel){
			printf("%d.", temp->value);
			}else{
			printf("%d, ", temp->value);
			}
			temp = temp->next;
		}
	printf("\n");
	}
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list!=NULL);
	int test=0;
	struct Link* temp = list->frontSentinel->next;
	while(temp!=list->backSentinel || test!=1){
		if(temp->value == value){
			test=1;
		}
		temp=temp->next;
	}
	return test;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list!=NULL);
	assert(!linkedListIsEmpty(list));
	struct Link* temp = list->frontSentinel;
	struct Link* takeme = NULL;
	int done = 0;
	if(linkedListContains(list, value)){
		while(done != 1 ){
			if(temp->next->value == value){
				takeme = temp->next;
				temp->next = temp->next->next;
				removeLink(list, takeme);
				done = 1;
			}
		temp = temp->next;
		}
	}	
}


