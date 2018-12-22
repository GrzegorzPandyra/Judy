#include <stdio.h>
#include <stdlib.h>	
#include "fileIO.h"
#include "config.h"	
#include "interface.h"
#include "debug.h"
#include "toolbox.h"

extern unsigned totalLines;

int readFile(char* path, char buffer[BUFFER_HEIGHT][BUFFER_WIDTH]){
	FILE *f = fopen(path, "r");
	if (f == NULL)
	{
		LOG("|fileIO.c|  ERROR: Failed to open file for read\n");
		// perror("ERROR: Failed to open file");
		
		return -1;
	}  
	clearBuffer();
	LOG("|fileIO.c|  INFO: Reading input file\n");
	char currentChar;
	int j=1;
	char* ptr = buffer[INFO_WINDOW_HEIGHT+j];	
	while( (currentChar = getc(f)) != EOF){
		if(currentChar != '\n'){
			//LOG("|fileIO.c|  INFO: looop\n");
			//LOG_VALUE("|fileIO.c|  INFO: iteration: ", *ptr);
			if(*(ptr+1+LINE_NUM_OFFSET) == '\0'){
				// LOG_CHAR("|fileIO.c|  INFO: WRAP: ", currentChar);
				totalLines++;
				j++;
				ptr = buffer[INFO_WINDOW_HEIGHT+j]+SCREEN_WRAP_DISTANCE;
				*ptr = currentChar;
				ptr++;
				// continue;
			} else {
				*ptr = currentChar;
				ptr++;					
			}
		} else {
			//LOG3("|fileIO.c|  INFO: Read line:", buffer[INFO_WINDOW_HEIGHT+j], "\n");
			totalLines++;
			//*ptr = '\0';
			j++;
			ptr = buffer[INFO_WINDOW_HEIGHT+j];
		}
	}
	LOG_VALUE("|fileIO.c|  INFO: Total lines: ", totalLines);
	fclose(f);	
	loadFileInfo(path);
	// LOG_DUMP_MATRIX(buffer);
	return 0;
}

int writeFile(char *path, char buffer[BUFFER_HEIGHT][BUFFER_WIDTH]){
	FILE *f = fopen(path, "w");
	if (f == NULL)
	{
		LOG("|fileIO.c|  ERROR: Failed to open file for write\n");
		return -1;
	}
	int currentLine = 0;
	while(currentLine <= totalLines){
		fputs(buffer[currentLine], f);
		currentLine++;
	}
	fclose(f);
	return 0;
}