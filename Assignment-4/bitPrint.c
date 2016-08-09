#include "bitPrint.h"
#include <string.h>
static char* reverseBytes(void *ptr, char nBytes);
static void printBits(void *ptr, char nBytes);

static void printBits(void *ptr, char nBytes){
	
	char *cPtr = (char*) ptr;
	for(int i=0;i<nBytes;i++){
		//for example to gt second byte
		//1100 0000 >> 6 = 0000 0011
		//               & 0000 0001     
		//                 0000 0001
		for(int b=7;b>=0;b--){
			printf("%d",(cPtr[i] >> b) & 1);
		}	
		printf(" ");
	}
	printf("\n");
}
static char* reverseBytes(void *ptr, char nBytes){
	char *cptr=malloc(nBytes);
	memcpy(cptr,ptr,nBytes);
	char *left=(char*) cptr;
	char *right=left+nBytes-1;
	while(left <right){
		char temp=*left;
		*left++=*right;
		*right--=temp;
	}
	return(cptr);
}
void printBitsEndian(void *ptr, char nBytes, char endian){
	if(nBytes == 1 || !endian) {
		printBits(ptr,nBytes);
	 return;
	}
	
	uint16_t test=1;
	//0000 0000  0000 0001 BigEndian
	//0000 0001  0000 0000 Little Endian
	char *a = (char*) & test; //pointer cast to byte type
	char BigEndianSystem=a[1] & 1; //look at second byte
	if(endian == 1 && BigEndianSystem) printBits(ptr,nBytes);
	else if(endian ==1 && !BigEndianSystem){
		char *revptr=reverseBytes(ptr,nBytes);
		printBits(revptr,nBytes);
		free(revptr);
	}
	else if(endian=-1 && BigEndianSystem){
		char *revptr=reverseBytes(ptr,nBytes);
		reverseBytes(ptr,nBytes);
		printBits(revptr,nBytes);
		free(revptr);
	}
	else{
		printBits(ptr,nBytes);
	}	
}

