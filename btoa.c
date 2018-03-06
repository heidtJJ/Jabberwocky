#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

const int numBitsInByte = 8;

int ipow(int,int);
void btoa( FILE *, FILE * );

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


	btoa( ifp, ofp );

  	fclose(ifp);
  	fclose(ofp);

	return 0;
}

//----------------------------------------------------------------------------------------------------

/*
	IDEA: This takes as input a text file of bits (where each bit is given by either
	the character '0' or the character '1') and outputs a sequence of ASCII characters.
	Here, each sequence of 8 bits is converted to a single ASCII character. The number 
	of bits in the input file is a multiple of 8.
*/

void btoa( FILE *infile, FILE *outfile ) {
	char c;// the next character to read from the file
	char bitWord[numBitsInByte];// this will contain the bits of each byte from the file

	while ((c = getc( infile )) != EOF) {// read each character from file 
		assert(c == '0' || c == '1');
		bitWord[0] = c;
		
		// 7 more bit characters to retrieve from file
		int i;
		for (i = 1; i < numBitsInByte; i++) {
			c = getc( infile );
			assert(c != EOF);
			bitWord[i] = c;
		}
		
		int byteTotal = 0;
		for(i = 0; i < numBitsInByte; ++i){
			if(bitWord[i] == '1'){
				byteTotal += ipow(2, numBitsInByte-1-i ); 
			}
		}
		putc((char)byteTotal, outfile);
	}
}

//----------------------------------------------------------------------------------------------------

int ipow(int base, int exponent) {  
	int returnValue = 1;
	int i;
	for(i = 1; i <= exponent; ++i) {
		returnValue *= base;
	}
	return returnValue;
}		
