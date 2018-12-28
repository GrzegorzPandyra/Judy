#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vigenere.h"
#include "config.h"
#include "debug.h"

/*
 * Creates MATRIX_SIZE x MATRIX_SIZE matrix of chars 
 * Each row of matrix is shifted by 1 position right
 * Rows ARE NOT null-terminated
 */
void buildMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]){
	char asciiNumber;
	LOG("|vigenere.c| INFO: BUILDING MATRIX\n");
	for(int i=0; i<MATRIX_SIZE; i++){																//run through matrix rows
		asciiNumber = MATRIX_START_CHAR;
		for(int j=i; j<MATRIX_SIZE; j++){															//run through chars <i;MATRIX_SIZE-1)
			matrix[i][j] = asciiNumber++;				
		}												
		for(int k=0; k<i; k++){																		//run through chars <0;i)
			matrix[i][k] = asciiNumber++;
		}
	}
	LOG("|vigenere.c| INFO: MATRIX BUILT\n");
}

/*
 * Encrypts data using square char matrix and a password
 *
 *   			        matrixCol
 *			         (password char)
 *				   1  2  3  4  5  6   
 *				  -- -- --  V -- --
 *				1|          |
 *				2|          |
 *				3|          |
 *	  matrixRow 4>----------X encrypted char
 *	 (data char)5|            
 *				6|
 *				
 */
void encryptData(char data[BUFFER_HEIGHT][BUFFER_WIDTH], char* password){
	char matrix[MATRIX_SIZE][MATRIX_SIZE];
	buildMatrix(matrix);
	unsigned bufferRow = 0;
	unsigned matrixRow, matrixCol;
	short isFound;
	char *dataPtr = (char*)data[0], *passwordPtr = password;
	while(bufferRow < BUFFER_HEIGHT){																//run through all rows in buffer
		isFound = 0;
		matrixRow = 0; 
		matrixCol = 0;
		if(*dataPtr != SPACE && *dataPtr != TAB){
			while(matrixRow < MATRIX_SIZE && isFound == 0){											//run through all rows in matrix
				if(matrix[matrixRow][0] == *dataPtr){                                               //check if data character has been found
					while( matrixCol < MATRIX_SIZE && isFound == 0){                                //run through all columns in matrix
						if(matrix[0][matrixCol] == *passwordPtr){									//check if password character has been found
							*dataPtr = matrix[matrixRow][matrixCol];								//encrypt buffer character with corresponding matrix character 
							passwordPtr++;
							if(*passwordPtr == '\0'){
								passwordPtr = password;
							}
							isFound = 1;
						}
						matrixCol++;
					}
				}
				matrixRow++;
			}
			if(isFound == 0){
				LOG("|vigenere.c|  ERROR: failed to locate a character :");
				LOG_CHAR("", *dataPtr);
				LOG("\n");
			}			
		}
		dataPtr++;																					//move to next character
		if(*dataPtr == '\0'){																		//unless it is \0, then move to next row
			bufferRow++;
			dataPtr = data[bufferRow];
		}
	}
}

/*
 * Decrypts the data by encrypting it again, but with "inverted" password 
 * More here: https://pl.wikipedia.org/wiki/Szyfr_Vigenère’a
 */
void decryptData(char data[BUFFER_HEIGHT][BUFFER_WIDTH], char* password){
	LOG("|vigenere.c|  INFO: DECRYPTING DATA... \n");
	char matrix[MATRIX_SIZE][MATRIX_SIZE];
	buildMatrix(matrix);
	invertPassword(password, matrix[0]);
	encryptData(data, password);
}

/*
 * Invert the password 
 * Used for decrypting data
 */
void invertPassword(char *password, char matrixChars[MATRIX_SIZE]){
	char *passPtr = password;
	LOG("|vigenere.c|  INFO: inverting password...\n");
	while(*passPtr != '\0'){
		LOG("|vigenere.c|  INFO: LOOP\n");
		*passPtr = matrixChars[( MATRIX_SIZE - indexOf(*passPtr, matrixChars )) % MATRIX_SIZE];
		passPtr++;
	}
	LOG("|vigenere.c|  INFO: inverting finished!\n");
}

/*
 * Find index of given character within an array
 * Used to invert the password
 */
int indexOf(char c, char matrixChars[MATRIX_SIZE]){
	for(int i=0; i<MATRIX_SIZE; i++){
		if(matrixChars[i] == c){
			return i;
		}
	}
	LOG("|vigenere.c|  ERROR: Failed to find index of character ");
	LOG_CHAR("", c);
	return -1;
}
