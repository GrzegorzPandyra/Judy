#include <stdio.h>
#include <stdlib.h>
#include "userIO.h"

extern int debug;

void getData(char* data){
	printf("Enter data:\n");
	scanf("%s", data);
}

void getPassword(char* password){
	printf("Enter password: ");
	scanf("%s", password);
}

void printMenu(){	
	system("cls");
	printf("\nVigenere encryption tool \nGrzegorz Pandyra - 2018\n");
	debug?printf("Debug mode -ON-\n\n"):printf("");
	printf("       .:MENU:.\n");
	printf("1) Encrypt raw data\n");
	printf("2) Decrypt raw data\n");
	printf("3) Read file\n");
	printf("4) Write to file\n");
	printf("5) Encrypt buffer \n");
	printf("6) Decrypt buffer \n");
	debug?printf("7) Print matrix\n"):printf("");
	debug?printf("8) Open file\n"):printf("");
	printf("9) Exit\n");
	printf("Select option: ");
}