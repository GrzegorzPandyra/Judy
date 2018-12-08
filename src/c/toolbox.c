#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#define TIMEOUT_COUNTER 131

/*Replace all occurences of oldChar with newChar within str*/
void repCharInStr(char* str, char oldChar, char newChar, int lineNum){
	short cnt = 0;
	char* strPtr = str;
	while(*strPtr != '\0'){
		// LOG("|toolbox.c|  WARNING: CHAR: ");
		// LOG_CHAR(*strPtr);
		// LOG("\n");
		if(*strPtr == oldChar){
			*strPtr = newChar;
		} 
		if(cnt > TIMEOUT_COUNTER){
			LOG_VALUE("|toolbox.c|  WARNING: TIMEOUT COUNTER REACHED - FAILED TO LOCATE '\\0' at line ", lineNum);
			break;
		}
		strPtr++;
		cnt++;
	}
	// LOG_VALUE("|toolbox.c|  INFO: Found '\\0' after ", cnt);
}