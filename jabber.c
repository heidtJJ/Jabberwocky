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
char* emptyString();
void jabber( FILE *, FILE * );
int foundInVec(vector*, char[]);
inline void printWord(char*, FILE*);
char* insertLetter(const char, char*);
char* intToBinary(const int, const int);

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

	jabber( ifp, ofp );

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

char* emptyString(){
	char* toReturn = malloc(sizeof(char));
	toReturn[0] = '\0';
}

//----------------------------------------------------------------------------------------------------

void jabber( FILE *infile, FILE *outfile ) {
	char c;// the next character to read from the file
	vector strTable;// this table will hold the patterns of retrieved input bits
	vector_init(&strTable);
	char* buffer = emptyString();

	vector_add( &strTable, emptyString() );// initialize index 0 with empty string
	int foundIndex = 0;// contains the index of the largest pattern in the table
	
	while ((c = getc( infile )) != EOF){// read each character from file 
		if(!isspace(c)){// make sure that the character is not whitespace
			buffer = insertLetter(c, buffer);
			int tempFoundIndex = foundInVec(&strTable, buffer);		

			if(tempFoundIndex == -1){// match could not be made
				printWord(intToBinary(foundIndex, Log2(vector_count(&strTable))), outfile);
				putc(c, outfile);

				vector_add(&strTable, buffer);
				
				buffer = emptyString();
				foundIndex = 0;
			}
			else{
				foundIndex = tempFoundIndex;// match was made. Update foundIndex in vector
			}
		}
	}
	if(buffer[0] != '\0'){
		printWord(intToBinary(foundIndex, Log2(vector_count(&strTable))), outfile);	
	}
	vector_free(&strTable);
}

//----------------------------------------------------------------------------------------------------

// returns i if the pattern was found in the vector
// returns -1 if the pattern was not found in vector
int foundInVec(vector* strTable, char pattern[]){
	int i;
	for(i = 0; i < strTable->count; ++i){
		int equalStrings = strcmp( vector_get(strTable, i), pattern);	
		if(equalStrings == 0){// string match
			return i;
		}
	}
	return -1;
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

char* intToBinary(const int num, const int numBits){
	if( !(numBits > 0) ){
		return emptyString();
	}	
	char* binaryString = malloc(sizeof(char)*numBits+1);
	binaryString[numBits] = '\0';
	
	int bitsCounter = 0;
	int i;
	for (i = 0; i < numBits && i < sizeof(int)*numBitsInByte; ++i){
		binaryString[numBits-1-i] = (num >> i) & 0x1 ? '1' : '0';
		++bitsCounter;
	}

	for (i = bitsCounter; i < numBits; i++){

		binaryString[i] = '0';
	}
	return binaryString;
}
