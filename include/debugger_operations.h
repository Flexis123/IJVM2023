#ifndef DEBUGGER_OPERATIONS_H
#define DEBUGGER_OPERATIONS_H

void help();
void err();
void file(char* binary_path);
void input(char* file_path);
void bbreak(unsigned int addr);
void bstep();
void brun();
void bcontinue();

#endif
