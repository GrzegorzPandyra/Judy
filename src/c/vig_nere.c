#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vigenere.h"

void printMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]){
	for(int i=0; i<MATRIX_SIZE; i++){
		for(int j=0; j<MATRIX_SIZE; j++){
			printf("%c", matrix[i][j]);
		};
		printf("\n");
	}
}
void buildMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]){
	char asciiNumber;
	for(int i=0; i<MATRIX_SIZE; i++){
		asciiNumber = 0x20;
		for(int j=i; j<MATRIX_SIZE; j++){
			matrix[i][j] = asciiNumber++;
		}
		for(int k=0; k<i; k++){
			matrix[i][k] = asciiNumber++;
		}
	}
}

int indexOf(char* c, char matrix[MATRIX_SIZE][MATRIX_SIZE]){
	for(int i=0; i<MATRIX_SIZE; i++){
		if(matrix[0][i] == *c){
			return i;
		}
	}
	return -1;
}

void encryptData(char* data, char* password, char* outputData, char matrix[MATRIX_SIZE][MATRIX_SIZE]){
	// 1. Find data letter in first column 
	// 2. Find password letter in first row
	// 3. Save letter on the crossing 
	int dataLength = strlen(data);
	int i = 0, j = 0, k = 0, isFound = 0;
	char* dataPtr = data, *passwordPtr = password, *outputDataPtr = outputData;
	while(k < dataLength){
		while(i < MATRIX_SIZE && isFound==0){
			if(matrix[i][0] == *dataPtr && *dataPtr != 0x09 && *dataPtr != 0x0A){
				while( j < MATRIX_SIZE && isFound == 0){
					if(matrix[0][j] == *passwordPtr){
						*outputDataPtr = matrix[i][j];
						passwordPtr++;
						outputDataPtr++;
						if(*passwordPtr == '\0'){
							passwordPtr = password;
						}
						isFound =1;
					}
					j++;
				}
			} else {
				if(*dataPtr == 0x09 || *dataPtr == 0x0A){
					*outputDataPtr = *dataPtr;
					outputDataPtr++;
					break;
				}
			}
			i++;
		}
		if(i >= MATRIX_SIZE && isFound==0){
			printf("failed to locate a character [%d] => [%c]\n", *dataPtr, *dataPtr);	
		}
		dataPtr++;
		k++;
		isFound = 0;
		i=0; 
		j=0;
	}
	*outputDataPtr = '\0';
}

void decryptData(char* data, char* password, char* outputData, char matrix[MATRIX_SIZE][MATRIX_SIZE]){
	char* passPtr = password;
	//"inverting" the password -https://pl.wikipedia.org/wiki/Szyfr_Vigenère’a
	while(*passPtr != '\0'){
		*passPtr = matrix[0][( MATRIX_SIZE - indexOf(passPtr, matrix )) % MATRIX_SIZE];
		passPtr++;
	}
	encryptData(data, password, outputData, matrix);
}

