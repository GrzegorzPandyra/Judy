/***
***Judy***
version 1.0
Grzegorz Pandyra
Wrocław 2018
***/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "config.h"
#include "fileIO.h"

extern char screen[SCREEN_HEIGHT][SCREEN_WIDTH];	

int main(int argc, char **argv) {
	//init
	readFile(argv[1], screen);		
}
