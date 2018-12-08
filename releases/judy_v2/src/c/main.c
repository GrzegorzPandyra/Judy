/***
***Judy***
version 2.0
Grzegorz Pandyra
Wrocław 2018
***/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "config.h"
#include "fileIO.h"
#include <conio.h>

//extern char screen[SCREEN_HEIGHT][SCREEN_WIDTH];	
extern char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];	
char userInput;

int main(int argc, char **argv) {
	//init
	
	// clearBuffer();
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
			default:
	
			break;
		}
		rePrintInterface(argv[1]);
	}
	
	
}
