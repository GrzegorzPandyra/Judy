#include "interface.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "toolbox.h"

char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];
char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
unsigned firstLine = 0;
unsigned totalLines = 0;

void clearBuffer(){
	int i = 0;
	while(i < BUFFER_HEIGHT){
		fillEmptySpace(buffer[i], ' ');
		i++;
	}
	// LOG_DUMP_MATRIX(buffer);
}

void loadBorders(){
	/*horizontal borders*/
	int i=0;
	while(i<SCREEN_WIDTH-1){
		screen[0][i] = HORIZONTAL_BORDER_CHAR;
		screen[SCREEN_HEIGHT-1][i] = HORIZONTAL_BORDER_CHAR;
		i++;
	}
	screen[0][SCREEN_WIDTH-1] = '\0';
	/*vertical borders*/
	i=1;
	while(i < SCREEN_HEIGHT-1){
		screen[i][0] = VERTICAL_BORDER_CHAR;
		screen[i][SCREEN_WIDTH-2] = VERTICAL_BORDER_CHAR;
		screen[i][SCREEN_WIDTH-1] = '\0';
		i++;
	}
	/*Info bar*/
	i=0;
	while(i<SCREEN_WIDTH-1){
		screen[INFO_WINDOW_HEIGHT][i] = HORIZONTAL_BORDER_CHAR;
		i++;
	}
	/*Program name*/
	strcpy(screen[PROGRAM_NAME_Y]+PROGRAM_NAME_X, PROGRAM_NAME);
	fillEmptySpace(screen[PROGRAM_NAME_Y], HORIZONTAL_BORDER_CHAR);
}

void loadFileInfo(char* path){
	char* pathStr = malloc(INTERFACE_MAX_PATH_LENGTH*sizeof(char));
	strcpy(pathStr, "Path: ");
	strcat(pathStr, path);
	strcat(pathStr, "\0");
	strcpy(screen[FILEPATH_Y]+FILEPATH_X, pathStr);
	// LOG("|interface.c|  INFO: !!!\n");
	fillEmptySpace(screen[FILEPATH_Y], SPACE);
}

void loadScreen(){
	int i = INFO_WINDOW_HEIGHT;
	char* lineNum = malloc(15*sizeof(char));
	char* line = malloc(SCREEN_WIDTH*sizeof(char));
	while(i < SCREEN_HEIGHT){
		sprintf(lineNum, " %4d| ", i+firstLine-INFO_WINDOW_HEIGHT);
		strcpy(line, "");
		strcat(line, lineNum);
		strcat(line, buffer[i+firstLine]);
		fillEmptySpace(line, ' ');	
		repCharInStr(line, TAB, SPACE, i+firstLine-INFO_WINDOW_HEIGHT); 
		strcpy(screen[i], line);
		i++;
	}
	// LOG_DUMP_MATRIX(screen);
	// LOG_DUMP_MATRIX(buffer);
	free(line);
	free(lineNum);
}

void fillEmptySpace(char* str, char c){
	/*Fill rest of the string with empty chars to keep consistent string length and '\0' char location */
	int charCount = strlen(str);
	while(charCount < SCREEN_WIDTH-1){
		*(str+charCount) = c;
		charCount++;
	}
	*(str+charCount) = '\0';
}

void rePrintInterface(char* path){
	system("cls");
	loadFileInfo(path);
	loadScreen();
	loadBorders();
	//print screen
	int i = 0;
	while(i < SCREEN_HEIGHT){
		printf("%s", screen[i]);	
		i++;
		printf("\n");
	}
	// LOG_DUMP_MATRIX(buffer);
	// LOG_VALUE("|interface.c|  INFO: First line: ", firstLine);
}

void scrollDown(){
	if(firstLine+SCREEN_HEIGHT < totalLines){
		firstLine++;
	}
}	

void scrollUp(){
	if(firstLine > 0){
		firstLine--;
	} 
}	

void pageDown(){
	if(totalLines > SCREEN_HEIGHT){
		if(firstLine + PAGING_DISTANCE + SCREEN_HEIGHT > totalLines){
			firstLine = totalLines - SCREEN_HEIGHT;
		} else {
			firstLine += PAGING_DISTANCE;
		}	
	}
}	

void pageUp(){
	if(totalLines > SCREEN_HEIGHT){
		if(firstLine < PAGING_DISTANCE){
			firstLine = 0;
		} else {
			firstLine -= PAGING_DISTANCE;
		}
	}
}	

