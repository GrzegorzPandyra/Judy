#include <stdlib.h>	
#include <string.h>
#include <stdio.h>
#include "debug.h"
#include "config.h"
/*************************************************/
#define LOG_MAX_COUNT 1000000
static int logCounter = 0;
extern char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];

/*
 * Log config data
 */
void LOG_INIT(){
	FILE *f = fopen(LOG_PATH, "w");
	if (f == NULL){
		perror("ERROR: Failed to open log file");	
		system("pause");
	}  else  {
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
		// LOG_CHAR("HORIZONTAL_BORDER_CHAR: ", HORIZONTAL_BORDER_CHAR); //crash
		// LOG_CHAR("VERTICAL_BORDER_CHAR: ", VERTICAL_BORDER_CHAR); //crash
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
	fclose(f);
}

/*
 * Create log entry
 */
void LOG(char* str1){
	FILE *f = fopen(LOG_PATH, "a");
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		if(str1 == NULL){
			str1 = "NULL";
		}
		fputs(str1,f);
		fclose(f);
		LOG_COUNT();
	}
}

/*
 * Create log entry comprising of 2 strings
 */
void LOG2(char* str1, char* str2){
	FILE *f = fopen(LOG_PATH, "a");
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
		fclose(f);
		LOG_COUNT();
	}
}

/*
 * Create log entry comprising of 3 strings
 */
void LOG3(char* str1, char* str2, char* str3){
	FILE *f = fopen(LOG_PATH, "a");
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
		fclose(f);
		LOG_COUNT();
	}
}

/*
 * Log a numerical value along with description
 * Carrie to next line
 */
void LOG_VALUE(char* str1, int value){
	char* str = malloc(sizeof(char)*DEBUG_MAX_STRING_LENGTH);
	sprintf(str, "%d", value);
	LOG3(str1, str, "\n");
	free(str);
	LOG_COUNT();
}

/*
 * Log single char + description 
 * carrie to next line
 */
void LOG_CHAR(char *strPrefix, char c){
	// LOG("|debug.c|  INFO: log char start\n");
	FILE *f = fopen(LOG_PATH, "a");
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
		LOG("|debug.c|  ERROR: Lost handle for log file\n");
	} else {
		// LOG("|debug.c|  INFO: file OK\n");
		char *str = malloc(DEBUG_MAX_STRING_LENGTH*sizeof(str));
		// LOG("|debug.c|  INFO: malloc\n");
		sprintf(str, "%s %c (ascii %d)\n", strPrefix, c, c);
		// LOG("|debug.c|  INFO: sprintf\n");
		fputs(str,f);
		// LOG("|debug.c|  INFO: puts\n");
		free(str);
		// LOG("|debug.c|  INFO: free\n");
		fclose(f);
		// LOG("|debug.c|  INFO: fclose\n");
		LOG_COUNT();
		// LOG("|debug.c|  INFO: done\n");
	}
}

/*
 * Dump matrix into log file 
 * The matrix does not have to be null-terminated
 */
void LOG_DUMP_MATRIX(char matrix[BUFFER_HEIGHT][BUFFER_WIDTH]){
	FILE *f = fopen(LOG_PATH, "a");
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		for(int i=0; i<BUFFER_HEIGHT; i++){
			for(int j=0; j<BUFFER_WIDTH; j++){
				putc(buffer[i][j],f);
			}	
			putc('\n',f);
			LOG_COUNT();
		}
		fclose(f);
	}
}

/*
 * Dump matrix into log file 
 * The matrix does not have to be null-terminated
 */
void LOG_DUMP_MATRIX2(char matrix[SCREEN_HEIGHT][SCREEN_WIDTH]){
	FILE *f = fopen(LOG_PATH, "a");
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		for(int i=0; i<SCREEN_HEIGHT; i++){
			for(int j=0; j<SCREEN_WIDTH; j++){
				putc(buffer[i][j],f);
			}	
			putc('\n',f);
			LOG_COUNT();
		}
		fclose(f);
	}
}

/*
 * Print two characters for comparison along with their ASCII number
 * Use strPrefix to indicate point(file) of comparison
 */
void LOG_COMP_CHARS(char *strPrefix, char c1, char c2){
	FILE *f = fopen(LOG_PATH, "a");
	if (f == NULL){
		perror("ERROR: Lost handle for log file");
	} else {
		char *str = malloc(DEBUG_MAX_STRING_LENGTH*sizeof(str));
		if(c1 == c2){
			sprintf(str, "%s     [%c](ascii %d) ?= [%c](ascii %d)      result: MATCH\n", strPrefix, c1, c1, c2, c2);
		} else {
			sprintf(str, "%s     [%c](ascii %d) ?= [%c](ascii %d)      result: NO MATCH\n", strPrefix, c1, c1, c2, c2);
		}
		fputs(str,f);
		free(str);
		fclose(f);
		LOG_COUNT();
	}
}

/*
 * Called at every LOG operation
 * Will terminate the program in case of uncontrolled LOG operations
 */
void LOG_COUNT(){
	logCounter++;
	if(logCounter > LOG_MAX_COUNT){
		FILE *f = fopen(LOG_PATH, "a");
		if (f == NULL){
			perror("ERROR: Lost handle for log file");
		} else {
			fputs("|debug.c|  LOCKUP ERROR: Number of logs has exceeded it's maximum value - PROGRAM ABORTED\n",f);
			fclose(f);
			abort();
		}
	}
}