#include "config.h"

#ifndef FILEIO_H
#define FILEIO_H

int readFile(char* path, char data[BUFFER_HEIGHT][BUFFER_WIDTH]);
void loadFileInfo(char*);

#endif