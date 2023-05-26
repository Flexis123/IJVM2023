#include "stack.h"
#include "ijvm.h"
#include <stdlib.h>

extern struct stack prog_stack;

void create_stack(){
    prog_stack.sp = -1;
    prog_stack.size = INIT_ST_SIZE;
    prog_stack.data = malloc(prog_stack.size);
}


void destroy_stack(){
    prog_stack.sp = -1;
    prog_stack.size = 0;
    free(prog_stack.data);
    prog_stack.data = NULL;
}

word_t tos(void){
    if(prog_stack.sp > - 1) return prog_stack.data[prog_stack.sp];
    return 0;
}

void wpush(word_t w){
    if(prog_stack.size <= prog_stack.sp + 1){
        prog_stack.size += prog_stack.size;
        prog_stack.data = realloc(prog_stack.data, prog_stack.size);
    }

    prog_stack.sp++;
    prog_stack.data[prog_stack.sp] = w;
}

word_t wpop(){
    word_t t = tos();
    if(prog_stack.sp > -1){
        prog_stack.sp -= 1;

        int new_size = prog_stack.sp + 1;
        if(new_size % INIT_ST_SIZE == 0){
            prog_stack.size = new_size;
            prog_stack.data = realloc(prog_stack.data, prog_stack.size);
        }
    }
    return t;
}