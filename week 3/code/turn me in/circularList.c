/*
Name: Sarah Turner, turnesar@oregonstate.edu
Date: 11 Oct 2018
CS 261, assignment 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = (struct Link*)malloc(sizeof(struct Link));
	assert(list->sentinel !=0);
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link* newb = (struct Link*)malloc(sizeof(struct Link));
	assert(newb!=0);
	newb->value = value;
	newb->prev = NULL;
	newb->next = NULL;
	return newb;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link* newb = createLink(value);
	assert (newb!=0);
	assert (link !=0);
	link->next->prev = newb;
	newb->next = link->next;
	link->next = newb;
	newb->prev = link;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list !=NULL);
	assert(link !=NULL);
	assert(list->size >0);
	link->next->prev = link->prev;
	link->prev->next = link->next;
	link->next = NULL;
	link->prev = NULL;
	free(link);
	link = 0;
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = (struct CircularList*)malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
		while(list->size >0){
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	list->sentinel = 0;
	free(list);
	list=0;
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	return list->size==0;
}

/*
* Prints the values of the links in the deque from front to back.
*/
void circularListPrint(struct CircularList* list)
{
	assert(list!=NULL);
	struct Link* temp = list->sentinel->next;
	if(circularListIsEmpty(list)){
		printf("No links in the list\n");
	}
	else{
		printf("Values in list:\n");
		while(temp != list->sentinel){
			printf("%f,  ", temp->value);
			temp=temp->next;
		}
	printf("\n"); 
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list!=NULL);
	struct Link* temp = NULL;
	struct Link* node = list->sentinel;
	do{
		temp = node->prev;
		node->prev = node->next;
		node->next = temp;
		node = node->prev;
	}while(node != list->sentinel);
}
