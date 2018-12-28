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

/*
 * Restore buffer to default state
 */
void clearBuffer(){
	int i = 0;
	while(i < BUFFER_HEIGHT){
		initRow(buffer[i], SPACE);
		i++;
	}
	firstLine = 0;
	totalLines = 0;
}

/*
 * Load screen with characters to form UI
 */
void loadBorders(){
	/*Info bar*/
	int i=0;
	while(i<SCREEN_WIDTH-1){
		screen[INFO_WINDOW_HEIGHT-1][i] = HORIZONTAL_BORDER_CHAR;
		i++;
	}
	/*Navigation panel*/
	i=0;
	while(i<SCREEN_WIDTH-1){
		screen[SCREEN_HEIGHT-NAVIGATION_PANEL_HEIGHT][i] = HORIZONTAL_BORDER_CHAR;
		i++;
	}
	/*horizontal borders*/
	i=0;
	while(i<SCREEN_WIDTH-1){
		screen[0][i] = HORIZONTAL_BORDER_CHAR;
		screen[SCREEN_HEIGHT-1][i] = HORIZONTAL_BORDER_CHAR;
		i++;
	}
	screen[0][SCREEN_WIDTH-1] = '\0';
	/*vertical borders*/
	i=1;
	while(i < SCREEN_HEIGHT){
		screen[i][0] = VERTICAL_BORDER_CHAR;
		screen[i][SCREEN_WIDTH-2] = VERTICAL_BORDER_CHAR;
		screen[i][SCREEN_WIDTH-1] = '\0';
		i++;
	}
	/*Program name*/
	strcpy(screen[PROGRAM_NAME_Y]+PROGRAM_NAME_X, PROGRAM_NAME);
	equalizeRowLength(screen[PROGRAM_NAME_Y], HORIZONTAL_BORDER_CHAR);
}


/*
 * Load screen with data about current file
 */
void loadFileInfo(char* path){
	char* pathStr = malloc(INTERFACE_MAX_PATH_LENGTH*sizeof(pathStr));
	strcpy(pathStr, "Path: ");
	strcat(pathStr, path);
	strcpy(screen[FILEPATH_Y]+FILEPATH_X, pathStr);
	free(pathStr);
	equalizeRowLength(screen[FILEPATH_Y], SPACE);
}

/*
 * Load screen with navigation info
 */
void loadNavigationInfo(){
	char* pathStr = malloc(INTERFACE_MAX_PATH_LENGTH*sizeof(pathStr));
	strcpy(screen[SCREEN_HEIGHT-NAVIGATION_PANEL_HEIGHT+1]+FILEPATH_X, 
			"O - open file, C - close file, T - save as..,  E - encrypt, D - decrypt, A - append text");
	strcpy(screen[SCREEN_HEIGHT-NAVIGATION_PANEL_HEIGHT+2]+FILEPATH_X, 
			"P/L - page up/down, W/S - scroll up/down, Q - quit");
	free(pathStr);
	equalizeRowLength(screen[SCREEN_HEIGHT-NAVIGATION_PANEL_HEIGHT+1], SPACE);
	equalizeRowLength(screen[SCREEN_HEIGHT-NAVIGATION_PANEL_HEIGHT+2], SPACE);
}

/*
 * Load screen with data from buffer
 * Suppress TABs to single empty char
 */
void loadScreen(){
	int i = 0;
	char* lineNum = malloc(15*sizeof(char));
	char* line = malloc(SCREEN_WIDTH*sizeof(char));
	while(i < SCREEN_HEIGHT-NAVIGATION_PANEL_HEIGHT-INFO_WINDOW_HEIGHT){
		sprintf(lineNum, " %4d| ", i+firstLine+1);													// +1 for the first line to be num 1 instead of num 0
		strcpy(line, "");
		strcat(line, lineNum);
		strcat(line, buffer[i+firstLine]);
		equalizeRowLength(line, ' ');	
		repCharInStr(line, TAB, SPACE, i+firstLine); 
		strcpy(screen[i+INFO_WINDOW_HEIGHT], line);
		i++;
	}
	free(line);
	free(lineNum);
}

/*
 * Move '\0' to the end of string's allocated memory and fill the string with given char
 * |_foo\0             |
 * |_foo_____________\0|
 */
void equalizeRowLength(char* str, char c){
	int charCount = strlen(str);
	while(charCount < SCREEN_WIDTH-1){
		*(str+charCount) = c;
		charCount++;
	}
	*(str+charCount) = '\0';
}


/*
 * init row with char 
 */
void initRow(char* str, char c){
	int i = 0;
	while(i < SCREEN_WIDTH-1){
		*(str+i) = c;
		i++;
	}
	*(str+i) = '\0';
}

/*
 * Re-print the screen
 */
void rePrintInterface(char* path){
	system("cls");
	loadFileInfo(path);
	loadNavigationInfo();
	loadScreen();
	loadBorders();
	int i = 0;
	while(i < SCREEN_HEIGHT){
		printf("%s\n", screen[i]);	
		i++;
	}
}


/*
 * File navigation functions
 */
 
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
			firstLine = totalLines - SCREEN_HEIGHT + NAVIGATION_PANEL_HEIGHT + INFO_WINDOW_HEIGHT;
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

/*
 * Append line to the end of buffer 
 */
void appendLine(char *str){
	strcpy(buffer[totalLines], str);
	equalizeRowLength(buffer[totalLines], ' ');	
	totalLines++;
}