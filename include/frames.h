#ifndef FRAMES_H
#define FRAMES_H

#include "ijvm.h"


typedef struct _val_pool
{
    unsigned int size;
    word_t* data;
} val_pool;

typedef struct _frame
{
    int frame_stack_base;
    unsigned int frame_pc;
    val_pool params;
    val_pool vars;
    frame* prev;
} frame;

frame* curr_frame = NULL;
frame new_frame(int16_t argc, int16_t val_pool_size);
frame goto_prev_frame();


#endif