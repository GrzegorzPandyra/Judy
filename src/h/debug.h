#ifndef LOGS_H
#define LOGS_H
#include "config.h"

void LOG_INIT();
// void LOG_CLOSE();
void LOG(char*);
void LOG2(char*, char*);
void LOG3(char*, char*, char*);
void LOG_VALUE(char*, int);
void LOG_CHAR(char*, char);
void LOG_DUMP_MATRIX(char matrix[BUFFER_HEIGHT][BUFFER_WIDTH]);
void LOG_DUMP_MATRIX2(char matrix[BUFFER_HEIGHT][BUFFER_WIDTH]);
void LOG_COMP_CHARS(char*, char, char);
void LOG_COUNT();
#endif