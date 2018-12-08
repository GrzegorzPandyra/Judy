#include <stdlib.h>	
#include <string.h>
#include <stdio.h>
#include "debug.h"
#include "config.h"
FILE *f;
extern char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];
void LOG_INIT(){
	f = fopen(LOG_PATH, "w");
	if (f == NULL){
		perror("ERROR: Failed to open log file");	
		system("pause");
	} 
	LOG("===================== LOG =====================\n");
	LOG3("PROJECT_ROOT: ", PROJECT_ROOT, ENDL);
	LOG3("PROGRAM_VERSION: ", PROGRAM_VERSION, ENDL);
	LOG("===============================================\n");
	LOG_VALUE("SCREEN_WIDTH: ", SCREEN_WIDTH);
	LOG_VALUE("SCREEN_HEIGHT: ", SCREEN_HEIGHT);
	LOG_VALUE("SCREEN_X: ", SCREEN_X);
	LOG_VALUE("SCREEN_Y: ", SCREEN_Y);
	LOG_VALUE("SCREEN_WRAP_DISTANCE: ", SCREEN_WRAP_DISTANCE);
	LOG_VALUE("BUFFER_WIDTH: ", BUFFER_WIDTH);
	LOG_VALUE("BUFFER_HEIGHT: ", BUFFER_HEIGHT);
	LOG_VALUE("INFO_WINDOW_HEIGHT: ", INFO_WINDOW_HEIGHT);
	LOG_VALUE("FILEPATH_X: ", FILEPATH_X);
	LOG_VALUE("FILEPATH_Y: ", FILEPATH_Y);
	LOG("HORIZONTAL_BORDER_CHAR: ");
	LOG_CHAR(HORIZONTAL_BORDER_CHAR);
	LOG(ENDL);
	LOG("VERTICAL_BORDER_CHAR: ");
	LOG_CHAR(VERTICAL_BORDER_CHAR);
	LOG(ENDL);
	LOG_VALUE("PROGRAM_NAME_X:", PROGRAM_NAME_X);
	LOG_VALUE("PROGRAM_NAME_Y:", PROGRAM_NAME_Y);
	LOG3("PROGRAM_VERSION:", PROGRAM_VERSION, "\n");
	LOG_VALUE("PADDING:", PADDING);
	LOG_VALUE("INTERFACE_MAX_PATH_LENGTH:", INTERFACE_MAX_PATH_LENGTH);
	LOG_VALUE("PASSWORD_MAX_LENGTH:", PASSWORD_MAX_LENGTH);
	LOG_VALUE("DEBUG_MAX_STRING_LENGTH:", DEBUG_MAX_STRING_LENGTH);
	LOG_VALUE("PAGING_DISTANCE:", PAGING_DISTANCE);
	LOG_VALUE("LINE_NUM_OFFSET:", LINE_NUM_OFFSET);
	LOG_VALUE("TAB:", TAB);
	LOG_VALUE("INTERFACE_MAX_PATH_LENGTH:", INTERFACE_MAX_PATH_LENGTH);
	LOG("===============================================\n");
}
void LOG(char* str1){
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		if(str1 == NULL){
			str1 = "NULL";
		}
		fputs(str1,f);
	}
}

void LOG2(char* str1, char* str2){
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		if(str1 == NULL){
			str1 = "NULL";
		}
		if(str2 == NULL){
			str2 = "NULL";
		}
		char* newStr = malloc(DEBUG_MAX_STRING_LENGTH*sizeof(char));
		strcpy(newStr, "");
		strcat(newStr, str1);
		strcat(newStr, str2);
		fputs(newStr,f);
		free(newStr);
	}
}

void LOG3(char* str1, char* str2, char* str3){
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		if(str1 == NULL){
			str1 = "NULL";
		}
		if(str2 == NULL){
			str2 = "NULL";
		}
		if(str3 == NULL){
			str3 = "NULL";
		}
		char* newStr = malloc(DEBUG_MAX_STRING_LENGTH*sizeof(char));
		strcpy(newStr, "");
		strcat(newStr, str1);
		strcat(newStr, str2);
		strcat(newStr, str3);
		fputs(newStr,f);
		free(newStr);
	}
}

void LOG_VALUE(char* str1, int value){
	char* str = malloc(sizeof(char)*DEBUG_MAX_STRING_LENGTH);
	sprintf(str, "%d", value);
	LOG3(str1, str, "\n");
	free(str);
}

void LOG_CHAR(char c){
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		fputc(c,f);
	}
}

void LOG_CLOSE(){
	fclose(f);	
}

void LOG_DUMP_MATRIX(char matrix[BUFFER_HEIGHT][BUFFER_WIDTH]){
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		for(int i=0; i<BUFFER_HEIGHT; i++){
			for(int j=0; j<BUFFER_WIDTH; j++){
				putc(buffer[i][j],f);
			}	
				putc('\n',f);
		}
	}
}