#include "config.h"
//void printMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void buildMatrix(char[MATRIX_SIZE][MATRIX_SIZE]);
//void encryptData(char* data, char* password, char* outputData);
void encryptData(char[BUFFER_HEIGHT][BUFFER_WIDTH], char *);
void decryptData(char[BUFFER_HEIGHT][BUFFER_WIDTH], char *);
void invertPassword(char *, char[MATRIX_SIZE]);
int indexOf(char, char[MATRIX_SIZE]);
