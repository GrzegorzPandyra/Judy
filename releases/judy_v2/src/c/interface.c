#include "interface.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolbox.h"

char buffer[BUFFER_HEIGHT][BUFFER_WIDTH] = {};
char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
unsigned firstLine = 0;
unsigned totalLines = 0;

void clearBuffer(){
	// char* str = malloc(BUFFER_WIDTH*sizeof(char));
	// strcpy(str, "");
	// LOG3( "|interface.c|  INFO: clear str", str, "\n");
	// for(int i=0; i<BUFFER_WIDTH; i++){
		// *str = buffer[0][i];
		// str++;
	// }
	// LOG3( "|interface.c|  INFO: str[0]", str, "\n");
	// strcpy(str, "");
	// LOG3( "|interface.c|  INFO: clear str", str, "\n");
	// for(int i=0; i<BUFFER_WIDTH; i++){
		// strcat(str, buffer[0][i]);
	// }
	// LOG3( "|interface.c|  INFO: str[1]",buffer[1], "\n");
	// strcpy(str, "");
	// LOG3( "|interface.c|  INFO: clear str", str, "\n");
	// for(int i=0; i<BUFFER_WIDTH; i++){
		// strcat(str, buffer[0][i]);
	// }
	// LOG3( "|interface.c|  INFO: str[2]",buffer[2], "\n");
}
void clearScreen(){
	// int i=0;
	// while(i < SCREEN_HEIGHT){
		// strcpy(screen[i], "");
	// }
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
		//repCharInStr(line, '0', '9'); TODO: FIX THIS FUNCTION
		strcpy(screen[i], line);
		i++;
	}
	free(line);
}

void fillEmptySpace(char* str, char c){
	/*Fill rest of the string with empty chars to keep consistent string length and '\0' char location */
	int charCount = strlen(str);
	while(charCount < SCREEN_WIDTH-1){
		*(str+charCount) = c;
		charCount++;
	}
	//*(str+charCount-2) = 'X';
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
	if(firstLine + PAGING_DISTANCE + SCREEN_HEIGHT > totalLines){
		firstLine = totalLines - SCREEN_HEIGHT;
	} else {
		firstLine += PAGING_DISTANCE;
	}
}	

void pageUp(){
	if(firstLine < PAGING_DISTANCE){
		firstLine = 0;
	} else {
		firstLine -= PAGING_DISTANCE;
	}
}	

