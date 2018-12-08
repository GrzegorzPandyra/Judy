#include "interface.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
extern int debug;

void printBorders(){
	/*Outer borders*/
	int i=0;
	while(i<SCREEN_WIDTH-1){
		screen[0][i] = HORIZONTAL_BORDER_CHAR;
		screen[SCREEN_HEIGHT-1][i] = HORIZONTAL_BORDER_CHAR;
		i++;
	}
	screen[0][SCREEN_WIDTH-1] = '\0';
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
}

void printScreen(){
	int i=0, j=0;
	while(i < SCREEN_HEIGHT){
		while(j < SCREEN_WIDTH){
			printf("%c", screen[i][j]);
			j++;
		}	
		i++;
		j=0;
		printf("\n");
	}
}

void fileInfo(char* path){
	char pathStr[INTERFACE_MAX_PATH_LENGTH] = {};
	strcat(strcat(pathStr, "Path:"), path);
	strcpy(screen[FILEPATH_Y]+FILEPATH_X, pathStr);
}



void rePrintInterface(){
	system("cls");
	/*Misc*/
	printBorders();
	/*Content*/
	printScreen();
}

