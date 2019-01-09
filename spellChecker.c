/*************
 * name: Sarah Turner
 * CS261
 * 18 Nov 18
 * *************/
#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{   
    char* word = nextWord(file);
    while(word!=NULL){
        hashMapPut(map,word,1); 
        free(word);
        word = nextWord(file);
   } 
   free(word);    // you did this - test
}
	
/** 
 * computes levenshtein distance between two words and returns it
 * @param s1 - string
 * @param s2 - string
 * source https://rosettacode.org/wiki/Levenshtein_distance#C
 */ 
 int levDistance(const char* s1, const char* s2){
	int s1len = strlen(s1);
	int s2len = strlen(s2);
	int d[s1len+1][s2len+1];
	for(int i=0;i<=s1len;i++){
		for(int j=0;j<=s2len;j++){
			d[i][j] = -1;
	}}
	int dist(int i, int j){
		if(d[i][j]>=0) return d[i][j];

	int x;
	if(i == s1len)
		x = s2len-j;
	else if(j == s2len)
		x = s1len -i;
	else if(s1[i]==s2[j])
		x = dist(i+1,j+1);
	else{
		x = dist(i+1,j+1);
		int y;
		if((y=dist(i,j+1))<x) x=y;
		if((y=dist(i+1,j))<x) x=y;
		x++;
	}
	return d[i][j]=x;
	}
	return dist(0,0);

 }
  

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        if(inputBuffer[strlen(inputBuffer)-1]=='\n')
	            inputBuffer[strlen(inputBuffer)-1]=0;
        if(hashMapContainsKey(map, inputBuffer))
            printf("The inputted word \"%s\" is spelled correctly\n", inputBuffer);
        else{
            char wordGuess[5][256];//array to hold guesses 
            struct HashLink* temp = NULL;
	    for(int i =0;i<map->capacity;i++){
                temp = map->table[i]; 
                    while(temp!=NULL){//add levenshtein distances as values
                        temp->value = levDistance(inputBuffer, temp->key);
			 //printf("%d\n", temp->value); used for tests
			 temp = temp->next;
                    }    
            }     
            for(int j = 0; j<5;j++){
                strcpy(wordGuess[j],  " ");
            }
            int a = 50;
	    int b = 50;
	    int c = 50;
	    int d = 50;
	    int e = 50; 			
	    //adds strings to array	
            for(int k =0;k<map->capacity;k++){
                temp = map->table[k];	 
                while(temp!=NULL){
                    if(temp->value<=a){
                            strcpy(wordGuess[1], wordGuess[0]);
                            strcpy(wordGuess[0], temp->key);
                            b = a;
                            a = temp->value;
                        }
                    else if (temp->value<=b){
                            strcpy(wordGuess[2], wordGuess[1]);
                            strcpy(wordGuess[1], temp->key);
                            b = c;
                            b = temp->value;
                    }  
                    else if(temp->value<=c){
                            strcpy(wordGuess[3], wordGuess[2]);
                            strcpy(wordGuess[2], temp->key);
                            c = d;
                            c = temp->value; 
                    }  
                    else if(temp->value<=d){
                            strcpy(wordGuess[4], wordGuess[3]);
                            strcpy(wordGuess[3], temp->key);
                            d = e;
                            d = temp->value; 
                    }
                    else if(temp->value<=e){
                            strcpy(wordGuess[4], temp->key);
                            e = temp->value;
                    } temp = temp->next;
                }    
            }    
	    //printf("%d,%d,%d,%d,%d\n", a, b,c, d,e); used for tests  
            printf("The inputted word \"%s\" is spelled incorrectly\n", inputBuffer);
            printf("Did you mean: ");
            for (int i = 0; i<4;i++){
                printf(" %s, ", wordGuess[i]);
            }
            printf("%s?\n", wordGuess[4]);
        }    
   
       
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    hashMapDelete(map);	    
    return 0;
}
