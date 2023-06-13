#ifndef STACK_H
#define STACK_H

#include "ijvm.h"
#include "math.h"

struct stack
{
    int sp;
    int size;
    word_t* data;
};

struct stack prog_stack;
#define STACK_SIZE pow(2, 22)

void create_stack(void);
void destroy_stack(void);
word_t wpop(void);
void wpush(word_t w);

#define PREV_FP_OFFSET 0
#define PREV_PC_OFFSET 1
#define VARC_OFFSET 2

void add_frame(uint16_t argc, word_t* args, uint16_t val_pool_size);
unsigned int goto_prev_frame(void);
void set_local_var(int index, word_t val);


#endif
