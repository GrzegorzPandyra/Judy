#include <stdio.h>
#include <stdlib.h>	
#include "fileIO.h"
#include "config.h"	
#include "interface.h"

extern int debug;

int readFile(char* path, char screen[SCREEN_HEIGHT][SCREEN_WIDTH]){
	FILE *f = fopen(path, "r");
	if (f == NULL)
	{
		perror("ERROR: Failed to open file");
		system("pause");
		return 1;
	}  
	char currentChar;
	int j=1;
	char* ptr = screen[INFO_WINDOW_HEIGHT+j];
	
	while( (currentChar = getc(f)) != EOF){
		if(currentChar != '\n'){
			//ptr = screen[INFO_WINDOW_HEIGHT+j];
			*ptr = currentChar;
			
		} else {
			//LOG("== \n");
			*ptr = '\0';
			j++;
			ptr = screen[INFO_WINDOW_HEIGHT+j];
		}
		ptr++;		
	}
	
	fclose(f);	
	fileInfo(path);
	return 0;
}

