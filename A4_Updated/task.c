/*
 * CS 261 Assignment 4
 * Name: Sarah Turner 
 * Date: 13 Nov 2018
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    Task* newb = malloc(sizeof(Task));
    newb->priority = priority;
    strcpy(newb->name, name);
    return newb;
    //you did this one
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    struct Task* l = (struct Task*)left;
    struct Task* r = (struct Task*)right;  	
    if(l->priority < r->priority)
            return -1;
    else if(l->priority > r->priority)
            return 1;

    return 0;
        //you did this one.    
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
