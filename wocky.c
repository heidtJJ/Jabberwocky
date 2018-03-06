#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "vector.h"

const int numBitsInByte = 8;

int Log2(int);
int ipow(int,int);
char* emptyString();
int binaryToInt(const char*);
void wocky( FILE *, FILE * );
inline void printWord(char*, FILE*);
char* insertLetter(const char, char*);
void printToFile(vector*, const char, char*, int*, FILE*);

int main( int argc, char *argv[] )
{
	FILE *ifp, *ofp;

	if (argc < 3) {
	  fprintf(stderr,"Not enough arguments\n");
	  exit(1);
	}
	if (!(ifp = fopen(argv[1],"r"))) {
	  fprintf(stderr,"Cannot open file %s\n",argv[1]);
	  exit(1);
	}
	if (!(ofp = fopen(argv[2],"w"))) {
	  fprintf(stderr,"Cannot open file %s\n",argv[2]);
	  exit(1);
	}
	
	wocky( ifp, ofp );

  	fclose(ifp);
  	fclose(ofp);

	return 0;
}

//----------------------------------------------------------------------------------------------------

int Log2( int n ){  
    // log(n)/log(2) is log2.  
    return ceil(log( (double)n ) / log( 2 ));  
}  

//----------------------------------------------------------------------------------------------------

int ipow(int base, int exponent){ 
	int returnValue = 1;
	int i;
	for(i = 1; i <= exponent; ++i){
		returnValue *= base;
	}
	return returnValue;
}


//----------------------------------------------------------------------------------------------------

char* emptyString(){
	char* toReturn = malloc(sizeof(char));
	toReturn[0] = '\0';
}

//----------------------------------------------------------------------------------------------------

int binaryToInt(const char* bitSequence){
	int size = strlen(bitSequence);
	int total = 0;
	int i;
	for(i = 0; i < size; ++i){
		total += ipow(2, size - 1 -i) * (bitSequence[i] - '0');
	}
	
	return total;
}	

//----------------------------------------------------------------------------------------------------

void wocky( FILE *infile, FILE *outfile ){
	char c;// the next character to read from the file
	vector strTable;// this table will hold the patterns of retrieved input bits
	vector_init(&strTable);
	char* buffer = emptyString();

	vector_add( &strTable, emptyString() );// initialize index 0 with empty string
	int foundIndex = 0;// contains the index of the largest pattern in the table
	int counter = 0;// this will count up to log2(size of strTable)
	
	while ((c = getc( infile )) != EOF){// read each character from file 
		if(!isspace(c)){// make sure that the character is not whitespace
			
			if( counter >= Log2(vector_count(&strTable)) ){
				printToFile(&strTable, c, buffer, &counter, outfile);
			}
			else{
				buffer = insertLetter(c, buffer);
				++counter;
			}
			
		}
	}
	if(counter != 0){
		printToFile(&strTable, c, buffer, &counter, outfile);
	}
	vector_free(&strTable);
}

//----------------------------------------------------------------------------------------------------

void printWord(char* word, FILE *outfile ){
	if(word != NULL) { 
		int i;// "loop initial declarations" not allowed in this version of C
		for(i = 0; word[i]!='\0'; ++i){
		 	putc(word[i], outfile);
		 }
	}
}

//----------------------------------------------------------------------------------------------------

char* insertLetter(const char c, char* buffer){
	int curSize = strlen(buffer);
	char* newBuffer = malloc(sizeof(char)*(curSize+1+1));
	if(curSize > 0){
		memcpy(newBuffer, buffer, curSize);
		free(buffer);
	}
	newBuffer[curSize] = c;
	newBuffer[curSize+1] = '\0';
	
	return newBuffer;
}

//----------------------------------------------------------------------------------------------------

void printToFile(vector* strTable, const char c, char* buffer, int* counter, FILE *outfile){
	int bufferValue = binaryToInt(buffer);
	char* matchedStr = vector_get(strTable, bufferValue);
	char* strCopy = malloc(sizeof(char) * (strlen(matchedStr) + 1));
	strcpy(strCopy, matchedStr);

	if(c != EOF){
		strCopy = insertLetter(c, strCopy);
	}
	printWord(strCopy, outfile);	

	vector_add(strTable, strCopy);	
	free(buffer);
	buffer = emptyString();
	*counter = 0;
}