#include "config.h"

#ifndef FILEIO_H
#define FILEIO_H

int readFile(char* path, char[BUFFER_HEIGHT][BUFFER_WIDTH]);
int writeFile(char* path, char[BUFFER_HEIGHT][BUFFER_WIDTH]);
void loadFileInfo(char*);

#endif