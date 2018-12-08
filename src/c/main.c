/***
***Judy***
version 3.0
Grzegorz Pandyra
Wrocław 2018
***/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "config.h"
#include "fileIO.h"
#include "debug.h"
#include <conio.h>

extern char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];	
char userInput;
char password[PASSWORD_MAX_LENGTH] = {};

int main(int argc, char **argv) {
	//init
	LOG_INIT();
	clearBuffer();
	readFile(argv[1], buffer);	
	rePrintInterface(argv[1]);
	while( (userInput = getch()) != 'q'){
		switch(userInput){
			case 's':
				scrollDown();
			break;
			case 'w':
				scrollUp();
			break;
			case 'l':
				pageDown();
			break;
			case 'p':
				pageUp();
			break;
			case '`':
				LOG("|main.c|  INFO: Waiting for password input\n");
				gets(password);
				LOG3("|main.c|  INFO: Received password: ", password, "\n");
			break;
			default:
				LOG3("|main.c|  INFO: pressed: ", &userInput, "\n");
			break;
		}
		rePrintInterface(argv[1]);
	}
	LOG_CLOSE();
}
