extern const int MATRIX_SIZE;
extern int debug;

void printMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void buildMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE]);
int indexOf(char* c, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void encryptData(char* data, char* password, char* outputData, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void decryptData(char* data, char* password, char* outputData, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
