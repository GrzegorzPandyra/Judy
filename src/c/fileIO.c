#include <stdio.h>
#include <stdlib.h>	
#include "fileIO.h"
#include "config.h"	
#include "interface.h"
#include "debug.h"
#include "toolbox.h"
#include "string.h"

extern unsigned totalLines;

/*
 * Open file for read and put it's content into buffer
 */

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
	int rowNum=0;
	char* ptr = buffer[rowNum];	
	while( (currentChar = getc(f)) != EOF){
		if(currentChar != '\n'){
			//LOG("|fileIO.c|  INFO: looop\n");
			//LOG_VALUE("|fileIO.c|  INFO: iteration: ", *ptr);
			if(*(ptr+LINE_NUM_OFFSET+1) == '\0'){
				// LOG_CHAR("|fileIO.c|  INFO: WRAP: ", currentChar);
				totalLines++;
				rowNum++;
				ptr = buffer[rowNum]+SCREEN_WRAP_DISTANCE;
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
			rowNum++;
			ptr = buffer[rowNum];
		}
	}
	LOG_VALUE("|fileIO.c|  INFO: Total lines: ", totalLines);
	fclose(f);	
	loadFileInfo(path);
	LOG_DUMP_MATRIX(buffer);
	return 0;
}

/*
 * Open file for write and put in it contents of the buffer
 * Move '\0' to the actual end of string to remove spaces at the end of string
 */
int writeFile(char *path, char buffer[BUFFER_HEIGHT][BUFFER_WIDTH]){
	FILE *f = fopen(path, "w");
	if (f == NULL)
	{
		LOG("|fileIO.c|  ERROR: Failed to open file for write\n");
		return -1;
	}
	int currentLine = 0;
	int i;
	char *row = malloc(BUFFER_WIDTH*sizeof(row));
	while(currentLine <= totalLines){
		i = BUFFER_WIDTH-2;
		strcpy(row, buffer[currentLine]);
		while(i >= 0){
			if(*(row+i) != SPACE){
				*(row+i+1) = '\n';
				*(row+i+2) = '\0';
				// LOG3("|fileIO.c|  INFO: ", row,"|\n");
				break;
			} else {
				if(i == 0){
					*(row+i) = '\n';
					*(row+i+1) = '\0';
					// *(row+i) = '\0';
					// LOG("|fileIO.c|  INFO: I = 0!!!!\n");
				} 
			}
			i--;
		}
		fputs(row, f);
		// fputc('|', f);
		// LOG2("|fileIO.c|  INFO:", row);
		currentLine++;
	}
	fclose(f);
	free(row);
	return 0;
}