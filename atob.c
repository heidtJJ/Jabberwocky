#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>

const int lastBitPos = 7;
const int numBitsInByte = 8;

void atob( FILE *, FILE * );
	
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

	atob( ifp, ofp );

  	fclose(ifp);
  	fclose(ofp);

	return 0;
}

//----------------------------------------------------------------------------------------------------

// ASCII to bits: Print the ascii characters from infile to bits in outfile
void atob( FILE *infile, FILE *outfile ) {
	char c;// the next character to read from the file
	while ((c = getc( infile )) != EOF) {// read each character from file 
		int i;
		for (i = 0; i < sizeof(char)*numBitsInByte; i++) {
			putc( ( (c >> (lastBitPos - i)) & 0x01) == 1 ? '1': '0' , outfile );
		}
	}
}
