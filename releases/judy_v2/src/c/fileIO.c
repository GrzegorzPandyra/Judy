#include <stdio.h>
#include <stdlib.h>	
#include "fileIO.h"
#include "config.h"	
#include "interface.h"

extern unsigned totalLines;

int readFile(char* path, char buffer[BUFFER_HEIGHT][BUFFER_WIDTH]){
	FILE *f = fopen(path, "r");
	if (f == NULL)
	{
		
		perror("ERROR: Failed to open file");
		system("pause");
		return 1;
	}  
	
	char currentChar;
	int j=1;
	char* ptr = buffer[INFO_WINDOW_HEIGHT+j];	
	while( (currentChar = getc(f)) != EOF){
		if(currentChar != '\n'){
			*ptr = currentChar;
			ptr++;	
		} else {
			//LOG3("|fileIO.c|  INFO: Read line:", buffer[INFO_WINDOW_HEIGHT+j], "\n");
			totalLines++;
			*ptr = '\0';
			j++;
			ptr = buffer[INFO_WINDOW_HEIGHT+j];
		}
			
	}
	
	fclose(f);	
	loadFileInfo(path);
	return 0;
}

