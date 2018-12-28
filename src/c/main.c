/***
***Judy***
version 4
Grzegorz Pandyra
Kraków 2018
***/


/*
 * KNOWN ISSUES:
 * > FIXED 'save as' saves buffer with offset, which corrupts the encrypted data
 * > FIXED crash when no file is selected
 * > FIXED missing lines at the start and end of buffer (when scrolling the screen)
 * > FIXED navigation window is missing content on startup
 *
 *
 * TO DO:
 * > DONE file navigation(open/close file)
 * > DONE save buffer to file
 * > work with multiple files
 * > word search
 * > path auto-completion
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
	char userInput = '0';
	char *password = malloc(sizeof(*password)*PASSWORD_MAX_LENGTH);
	char *filePath = malloc(sizeof(*filePath)*PASSWORD_MAX_LENGTH);
	char *loadedFilePath;
	short fileStatus = 0;
	LOG_INIT();
	clearBuffer();
	/*
	 * ARGS EXECUTION
	 */
	if(argc == 1){
		loadedFilePath = "<select file>";															//program launched without target file						
	} else {
		loadedFilePath = argv[1];															
	}	
	switch(argc){
		case 1:
			LOG("|main.c|  INFO: no file loaded\n");
		break;
		case 2:
			readFile(loadedFilePath, buffer);	
		break;
		case 3:
			readFile(loadedFilePath, buffer);	
			LOG("|main.c|  WARNING: UNKNOWN ARGUMENT\n");
		break;
		case 4:
			readFile(loadedFilePath, buffer);
			if(strcmp(argv[2],"-e") == 0 || strcmp(argv[2],"-E") == 0 || strcmp(argv[2],"--encrypt") == 0){
				LOG("|main.c|  INFO: ENCRYPTING FILE\n");
				encryptData(buffer, argv[3]);
			} else {
				if(strcmp(argv[2],"-d") == 0 || strcmp(argv[2],"-D") == 0 || strcmp(argv[2],"--decrypt") == 0) {
					LOG("|main.c|  INFO: DECRYPTING FILE\n");
					decryptData(buffer, argv[3]);						 
				} else {
					LOG("|main.c|  WARNING: UNKNOWN ARGUMENT\n");
				}
			}
		break;
		default:
			LOG("|main.c|  WARNING: Too many arguments - no file loaded\n");
	    break;
	}
	
	rePrintInterface(loadedFilePath);																// for some reason navigation panel appears only after second rePrint, dunno why
	rePrintInterface(loadedFilePath);																// it's not pretty, but it works
	/*
	 * USER INPUT
	 */
	while( userInput != QUIT_BTN_1 && userInput != QUIT_BTN_2){
		userInput = getch();
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
				printf("Enter password: ");
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
				printf("Enter password: ");
				gets(password);
				if(strcmp(password, "") != 0){
					LOG3("|main.c|  INFO: Received password: ", password, "\n");
					encryptData(buffer, password);
				} else {
					LOG("|main.c|  WARNING: password is null\n");
				}
			break;
			case OPEN_FILE_BTN_1:
			case OPEN_FILE_BTN_2:
				printf("Path to file: ");
				gets(filePath);
				fileStatus = readFile(filePath, buffer);
				if(fileStatus == -1){
					printf("No such file\n");
					system("pause");
					fileStatus = 0;
				}
			break;
			case CLOSE_FILE_BTN_1:
			case CLOSE_FILE_BTN_2:
				clearBuffer();
				LOG("|main.c|  INFO: file closed\n");
			break;
			case SAVE_AS_BTN_1:
			case SAVE_AS_BTN_2:
				printf("Save as: ");
				gets(filePath);
				fileStatus = writeFile(filePath, buffer);
				if(fileStatus == -1){
					printf("No such file\n");
					system("pause");
					fileStatus = 0;
				}
				LOG("|main.c|  INFO: saved as...\n");
			break;
			default:
				LOG3("|main.c|  INFO: pressed: ", &userInput, "\n");
			break;
		}
		rePrintInterface(loadedFilePath);
	}		
}
