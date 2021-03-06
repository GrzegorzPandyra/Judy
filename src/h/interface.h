#ifndef INTERFACE_H
#define INTERFACE_H

void rePrintInterface(char*);
void loadBorders();
void fileInfo(char*);
void scrollDown();
void scrollUp();
void pageDown();
void pageUp();
void equalizeRowLength(char*, char);
void clearBuffer();
void loadNavigationInfo();
void initRow(char*, char);
void appendLine(char*);
#endif