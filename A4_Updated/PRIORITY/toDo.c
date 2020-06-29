/*
 * CS 261 Assignment 4
 * Name: Sarah Turner 
 * Date: 13 Nov 2018
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
     //wouldn't you want to heapsort first?	
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)//changed heap to temp;
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Purges the newline from input
 * @param input
 */
void purgeNewline(char* s){
	if(s[strlen(s)-1]=='\n')
	s[strlen(s)-1]=0;
}
/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    char *task = malloc(sizeof(char)*256);
    char *fileName = malloc(sizeof(char)*50);
    int pri = 0;
    char c = ' ';
    switch(command){	

    case 'l':
        if(dySize(list)>0){
            printf("This will override your current entries\n");
            printf("Enter 'Q' if you want to return to the main menu, any other key to proceed\n");
            c = getchar();
        // Eat newlines
            while (getchar() != '\n');
            if(c == 'Q')
                return;
            else{
                while(dySize(list)>0)
                    dyHeapRemoveMin(list, taskCompare);
            }
         }
        printf("Please enter the full filename: \n"); 
        scanf("%[^\n]%*c", fileName);
	purgeNewline(fileName);
        FILE* inputFile = fopen(fileName, "r");
        if(inputFile == NULL)
                printf("File did NOT load successfully, please try again\n");
        else{
                listLoad(list, inputFile);
                fclose(inputFile);
                printf("File loaded successfully \n");
        }            
    	break;

    case 's':
        printf("Please enter the name to save to: \n");
        scanf("%[^\n]%*c", fileName);
	purgeNewline(fileName);
        FILE* outputFile = fopen(fileName,"w");
        listSave(list, outputFile);
	if(outputFile==NULL){
		printf("the list was not saved\n");
	}
	else{
		printf("The list was saved \n");
	}
	fclose(outputFile);
	break;    
 
    case 'a':
        printf("enter a priority\n");
        scanf("%d", &pri);
	while(getchar() !='\n'); 
	printf("enter the task\n");
        scanf("%[^\n]%*c",task);
	purgeNewline(task);
        Task* t = taskNew(pri,task);
     //   if(dyBagContains(list,t,taskCompare)){
       //     printf("duplicate priority will not be added\n");
         //   taskDelete(t);
      // }	
      // else{    
            dyHeapAdd(list, t, taskCompare); 
       // }
	break;
        
    case 'g':
	if(dySize(list)==0){
		printf("whoops, your list is empty\n");
	}
	else{
		printf("Your top priority is:%d\n",((struct Task*)dyHeapGetMin(list))->priority); 
		printf("Your task is: %s\n", ((struct Task*)dyHeapGetMin(list))->name);   
        	printf("\n");
	}
        break;
      
    case 'r':
        if(dySize(list)==0)
            printf("whoops, your list is already empty\n");
        else{
            taskDelete((struct Task*)(dyHeapGetMin(list)));
            dyHeapRemoveMin(list, taskCompare);
	    printf("removed the first task\n");
    	}	
	break;

    case 'p':
	if(dySize(list)>0){
		listPrint(list);
	}
	else{
		printf("whoops, your list is empty\n");
	}
    	break;

    case 'e':
    while(dySize(list)>0){
         taskDelete((struct Task*)(dyHeapGetMin(list)));
         dyHeapRemoveMin(list, taskCompare);   
    }
	printf("so long!\n");  
    	break;
   }
	free(task);
	free(fileName);
       // FIXME: Implement
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
