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
		//LOG3("|vigenere.c| ", matrix[i], "\n");
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
	
	//prep vigenere matrix
	char matrix[MATRIX_SIZE][MATRIX_SIZE];
	buildMatrix(matrix);
	//
	unsigned bufferRow = 0;
	unsigned matrixRow, matrixCol;
	short isFound;
	char *dataPtr = (char*)data[0], *passwordPtr = password;
	// LOG("|vigenere.c|  INFO: [1]\n");
	while(bufferRow < BUFFER_HEIGHT){																//run through all rows in buffer
		// LOG("|vigenere.c|  INFO: [2]\n");
		isFound = 0;
		matrixRow = 0; 
		matrixCol = 0;
		if(*dataPtr != SPACE && *dataPtr != TAB){
			// LOG("|vigenere.c|  INFO: [3]\n");
			while(matrixRow < MATRIX_SIZE && isFound == 0){											//run through all rows in matrix
				// LOG("|vigenere.c|  INFO: [4]\n");
				if(matrix[matrixRow][0] == *dataPtr){                                               //check if data character has been found
					// LOG("|vigenere.c|  INFO: [5]\n");
					while( matrixCol < MATRIX_SIZE && isFound == 0){                                //run through all columns in matrix
						// LOG("|vigenere.c|  INFO: [6]\n");
						if(matrix[0][matrixCol] == *passwordPtr){									//check if password character has been found
							// if(*dataPtr == ':'){
								// LOG_CHAR("|vigenere.c|  INFO: ENCRYPTED: ", *dataPtr);
								// LOG_CHAR("|vigenere.c|  INFO:        AS: ", matrix[matrixRow][matrixCol]);								
							// }
							// LOG("|vigenere.c|  INFO: [7]\n");
							*dataPtr = matrix[matrixRow][matrixCol];								//encrypt buffer character with corresponding matrix character 
							passwordPtr++;
							if(*passwordPtr == '\0'){
								// LOG("|vigenere.c|  INFO: [8]\n");
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
			// LOG("|vigenere.c|  INFO: [9]\n");
			bufferRow++;
			dataPtr = data[bufferRow];
			// LOG("|vigenere.c| INFO: buffer advances to next row\n");
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
	// LOG("|vigenere.c|  INFO: decrypt matrix built \n");
	// LOG("|vigenere.c|  INFO: 1\n");
	invertPassword(password, matrix[0]);
	// LOG("|vigenere.c|  INFO: password inverted \n");
	// LOG3("|vigenere.c|  INFO: decrypting with ", password, "\n");
	encryptData(data, password);
}

/*
 * Invert the password 
 * Used for decrypting data
 */
void invertPassword(char *password, char matrixChars[MATRIX_SIZE]){
	char *passPtr = password;
	LOG("|vigenere.c|  INFO: inverting password...\n");
	// int q = 0;
	while(*passPtr != '\0'){
		LOG("|vigenere.c|  INFO: LOOP\n");
		// q++;
		// LOG_CHAR("|vigenere.c|  INFO: ", *passPtr);
		// LOG3("|vigenere.c|  INFO: log char :", passPtr, "\n");
		*passPtr = matrixChars[( MATRIX_SIZE - indexOf(*passPtr, matrixChars )) % MATRIX_SIZE];
		passPtr++;
		// if(q > 5){
			// LOG("|vigenere.c|  ERROR: PASSWORD BOUNDS EXCEEDED!!!'n");
			// abort();
		// }
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
