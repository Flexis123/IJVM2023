#include "stack.h"
#include "ijvm.h"
#include <stdlib.h>
#include "math.h"
#include "execution.h"

extern struct stack prog_stack;
static int fp;

void increase_stack_pointer(uint16_t offset){
    int new_sp = prog_stack.sp += offset;
    if(prog_stack.size <= new_sp + 1){
        printf("stack overflow!");
        abort();
    }
    prog_stack.sp = new_sp;
}

uint16_t get_frame_varc(){
    return prog_stack.data[fp + VARC_OFFSET];
}

int get_vars_pool_start(){
    return fp + VARC_OFFSET + 1;
}

word_t get_local_variable(int i){
    return prog_stack.data[get_vars_pool_start() + i];
}

void set_local_var(int index, word_t val){
    prog_stack.data[get_vars_pool_start() + index] = val;
}

void add_frame(uint16_t argc, word_t* args, uint16_t var_pool_size){
    wpush(fp);
    fp = prog_stack.sp;
    wpush(get_program_counter());

    wpush(argc + var_pool_size);

    increase_stack_pointer(argc + var_pool_size);
    
    word_t* frame_args = prog_stack.data + get_vars_pool_start();
    for(size_t i = 0; i < argc; i++) frame_args[i] = args[i];
}

unsigned int goto_prev_frame(void){
    int prev_fp = prog_stack.data[fp + PREV_FP_OFFSET];
    int prev_pc = prog_stack.data[fp + PREV_PC_OFFSET];

    prog_stack.sp = fp - 1;
    fp = prev_fp;
    return prev_pc;
}

void create_stack(){
    prog_stack.sp = -1;
    prog_stack.size = STACK_SIZE;
    prog_stack.data = malloc(prog_stack.size);
    fp = 0;

    add_frame(0, NULL, 256); // add main frame
}

void destroy_stack(){
    prog_stack.sp = -1;
    prog_stack.size = 0;
    free(prog_stack.data);
    prog_stack.data = NULL;
    fp = 0;
}

word_t tos(void){
    if(prog_stack.sp > - 1  && prog_stack.sp < prog_stack.size) return prog_stack.data[prog_stack.sp];
    return 0;
}

void wpush(word_t w){
    increase_stack_pointer(1);
    prog_stack.data[prog_stack.sp] = w;
}

word_t wpop(void){
    word_t t = tos();
    prog_stack.sp--;
    return t;
}


