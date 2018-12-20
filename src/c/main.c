/***
***Judy***
version 3.0
Grzegorz Pandyra
Wrocław 2018
***/


/*
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "config.h"
#include "fileIO.h"
#include "debug.h"
#include <conio.h>
#include "vigenere.h"

extern char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];													//holds entire data from file, encryption is performed here
extern char screen[SCREEN_HEIGHT][SCREEN_WIDTH];													//used to display a slice of buffer along with UI
int main(int argc, char **argv) {
	char userInput;
	char *password = malloc(sizeof(*password)*PASSWORD_MAX_LENGTH);
	//init
	LOG_INIT();
	clearBuffer();
	int fileOpened = readFile(argv[1], buffer);	
	if(fileOpened == 0){
		//read cmd flags
		if(argc >= 3){ 
			LOG_VALUE("|main.c|  INFO: argc = ", argc);
			if( (strcmp(argv[2],"-e") == 0 || strcmp(argv[2],"--encrypt") == 0 ) && argc == 4){
				LOG("|main.c|  INFO: ENCRYPTING FILE\n");
				encryptData(buffer, argv[3]);
			} else {
				if( (strcmp(argv[2],"-d") == 0 || strcmp(argv[2],"--decrypt") == 0) && argc == 4 ) {
					LOG("|main.c|  INFO: DECRYPTING FILE\n");
				} else {
					LOG("|main.c|  WARNING: UNKNOWN ARGUMENT\n");
				}
			}			
		}
		rePrintInterface(argv[1]);
		//user input
		while( (userInput = getch()) != 'q'){
			switch(userInput){
				case SCROLL_DOWN_BTN_1:
				case SCROLL_DOWN_BTN_2:
					scrollDown();
				break;
				case SCROLL_UP_BTN_1:
				case SCROLL_UP_BTN_2:
					scrollUp();
				break;
				case PAGE_DOWN_BTN_1:
				case PAGE_DOWN_BTN_2:
					pageDown();
				break;
				case PAGE_UP_BTN_1:
				case PAGE_UP_BTN_2:
					pageUp();
				break;
				case DECRYPT_BTN_1:
				case DECRYPT_BTN_2:
					LOG("|main.c|  INFO: Waiting for password input\n");
					gets(password);
					if(strcmp(password, "") != 0){
						LOG3("|main.c|  INFO: Received password: ", password, "\n");
						decryptData(buffer, password);						 
					} else {
						LOG("|main.c|  WARNING: password is null\n");
					}
				break;
				case ENCRYPT_BTN_1:
				case ENCRYPT_BTN_2:
					LOG("|main.c|  INFO: Waiting for password input\n");
					gets(password);
					if(strcmp(password, "") != 0){
						LOG3("|main.c|  INFO: Received password: ", password, "\n");
						encryptData(buffer, password);
					} else {
						LOG("|main.c|  WARNING: password is null\n");
					}
				break;
				default:
					LOG3("|main.c|  INFO: pressed: ", &userInput, "\n");
				break;
			}
			rePrintInterface(argv[1]);
		}		
	}
}
