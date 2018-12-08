#include <stdio.h>
#include <stdlib.h>	
#include "fileIO.h"

extern int debug;

void writeFile(char* path, char* outputData){
	debug?printf("\n<<<Writing to file %s>>>\n", path):printf("");
	FILE *f = fopen(path, "w+");		
	fputs( outputData, f);
	fclose(f);		
}

int readFile(char* path, char* data){
	debug?printf("\n<<<Reading file %s>>>\n", path):printf("");
	char* dataPtr = data;
	FILE *f = fopen(path, "r");
	if (f == NULL)
	{
		perror("Failed to open file");
		return 1;
	}
	char currentChar;
	while( (currentChar = getc(f)) != EOF){
		*dataPtr = currentChar;
		debug?printf("[%d] => [%c]\n",*dataPtr, *dataPtr):printf("");
		dataPtr++;
	}
	fclose(f);	
	*dataPtr = '\0';
	return 0;
}

int printFile(char* path){
	debug?printf("\n<<<Contents of %s>>>\n", path):printf("");
	FILE *f = fopen(path, "r");
	if (f == NULL)
	{
		perror("Failed to open file");
		return 1;
	}
	char currentChar = '0';
	while(currentChar != EOF){
		currentChar=fgetc(f);
		printf("%c", currentChar);
	}
	fclose(f);	
	return 0;
}

void getFilePath(char* filePath){
	printf("Enter path to file: ");
	scanf("%s", filePath);
}

void printDebugData(char* data){
	char* dataPtr = data;
	while(*dataPtr != '\0'){
		printf("%d => %c\n", *dataPtr, *dataPtr);	
		dataPtr++;
	}
	
}