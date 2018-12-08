#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TIMEOUT_COUNTER 100

void repCharInStr(char* str, char oldChar, char newChar){
	short i = 0;
	while(*(str+i) != '\0'){
		
		if(*(str+i) == oldChar){
			*(str+i) = newChar;
		
		}
		if(*(str+i) == 'X'){
		
		}
		if(i > TIMEOUT_COUNTER){
		
			break;
		}
		i++;
	}
}