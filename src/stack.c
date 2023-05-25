#include "stack.h"
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