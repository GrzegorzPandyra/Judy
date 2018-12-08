/*
Vigenere encryption/decryption tool - version 4
Grzegorz Pandyra, August 2018

Change log
v1 - initial release, basic encryption on 28 characters, hardcoded matrix
v2 - encryption and decryption on 95-character matrix, generated matrix, user menu added
v3 - 
v4 - program split into multiple files, fixed bug with saving filename
v5 - separated fileIO and encryption tool, files can be read and encrypted without instantly saving them
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "userIO.h"
#include "vigenere.h"

const int STRING_MAX_LENGTH = 21;
const int DATA_BUFFER_LENGTH = 10000;
const int MATRIX_SIZE = 95;
int debug = 0;
int error = 0;

int main(int argc, char **argv) {
	if(argv[1] != NULL && strcmp(argv[1],"debug") == 0){
		debug = 1;
	}
	char matrix[MATRIX_SIZE][MATRIX_SIZE];		
	buildMatrix(matrix);
	//printMatrix(matrix);
	char* data = (char*) malloc(sizeof(char)*DATA_BUFFER_LENGTH);
	char* password = (char*) malloc(sizeof(char)*STRING_MAX_LENGTH);
	char* outputData = (char*) malloc(sizeof(char)*DATA_BUFFER_LENGTH);
	char* filePath = (char*) malloc(sizeof(char)*STRING_MAX_LENGTH);
	int select = 0;
	while(select!=9){
		printMenu();			
		scanf("%d", &select);
		switch(select){
			case 1:
				printf("\n===ENCRYPTING RAW DATA===\n");
				getData(data);
				getPassword(password);
				encryptData(data, password, outputData, matrix);
				printf("Encrypted data: %s\n", outputData);
				system("pause");
			break;
			case 2:
				printf("\n===DECRYPTING RAW DATA===\n");
				getData(data);
				getPassword(password);
				decryptData(data, password, outputData, matrix);
				printf("Decrypted data: %s\n", outputData);
				system("pause");
			break;
			case 3:
				printf("\n===READING FILE===\n");
				getFilePath(filePath);
				error = readFile(filePath, data);
				if( !error ){
					printf("Read data:\n%s\n", data);
					outputData = data;
				}				
				system("pause");
				break;
			case 4:	
				printf("\n===WRITING TO FILE===\n");
				getFilePath(filePath);
				writeFile(filePath, outputData);
				break;
			case 5:
				printf("\n===ENCRYPTING DATA===\n");
				getPassword(password);
				encryptData(data, password, outputData, matrix);
				debug?printf("\nencrypted data:\n%s\n", outputData):printf("");
				printf("Encrypted data:\n%s\n", outputData);	
				system("pause");
				break;
			case 6:
				printf("\n===DECRYPTING DATA===\n");
				getPassword(password);
				decryptData(data, password, outputData, matrix);
				printf("Decrypted data:\n%s\n", outputData);
				system("pause");
				break;
			case 7:
				if(debug){
					printf("\n");
					printMatrix(matrix);
					system("pause");
				} 
				break;
			case 8:
				if(debug){
					getFilePath(filePath);
					printFile(filePath);
					system("pause");
				} 
				break;
			case 9:
				free(outputData);
				free(data);
				free(password);
				printf("\nShutting down...\n");
				return 0;
				break;
			default:
				printf("\nUnknown command\n");
			break;
		}
	}
}
