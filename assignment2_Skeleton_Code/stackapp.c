/*	stack.c: Stack application.
 *	Sarah Turner
 *	6 Oct 2018
 *	*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	param:  d pointer to DynArr used for stack
	param:  temp char used to hold characters 
	param:  balance used in cases where there are more ]}) than ([{
	pre: s is not null
	post: d is deleted 
*/
int isBalanced(char* s)
{
	DynArr* d;
	d=newDynArr(1);
	assert (s!=NULL);
	char temp = *s;
	int balance=2;

	while(temp != '\0'){
	  temp = nextChar(s); 
          if( temp == '{'|| temp=='['|| temp=='('){
            pushDynArr(d, temp);
           }
         else if(temp == '}'|| temp==']'|| temp==')'){
	      if(!isEmptyDynArr(d)){
	        popDynArr(d);}
	      else{
	        balance=0;}
           }
	 //printf("next character: %c\n",temp);//used for test
	 }	
      if (balance==0 || !isEmptyDynArr(d)){
	deleteDynArr(d);
	return 0;
      }	
      else {		
         deleteDynArr(d); 	
         return 1;
      }	 	
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}

