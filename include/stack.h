#ifndef STACK_H
#define STACK_H

#include "ijvm.h"

struct stack
{
    int sp;
    int size;
    word_t* data;
};

struct stack prog_stack;
#define INIT_ST_SIZE 1024

void create_stack();
void destroy_stack();
word_t wpop();
void wpush(word_t w);


#endif
