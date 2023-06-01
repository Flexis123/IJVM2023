#include "frames.h"
#include <stdlib.h>
#include "ijvm.h"
#include "stack.h"

extern frame* curr_frame = NULL;

frame new_frame(int16_t argc, int16_t var_pool_size){
    frame* fresh_frame;

    if(curr_frame == NULL){
        curr_frame = malloc(sizeof(frame));
        curr_frame->frame_stack_base = 0;

        fresh_frame = curr_frame;
    }else{
        fresh_frame = malloc(sizeof(frame));
        curr
    }

    fresh_frame->frame_pc = get_program_counter();
    fresh_frame->params.size = argc;
    fresh_frame->params.data = malloc(sizeof(word_t) * argc);

    fresh_frame->vars.size = var_pool_size;
    fresh_frame->params.data = malloc(sizeof(word_t) * var_pool_size);
}

frame goto_prev_frame();