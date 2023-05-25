#include "stack_operations.h"
#include "ijvm.h"
#include "stack.h"
#include <stdlib.h>
#include "io.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


word_t tos(void){
    return prog_stack.data[prog_stack.sp];
}

void wpush(word_t w){
    if(prog_stack.size <= prog_stack.sp + 1){
        prog_stack.size += prog_stack.size;
        prog_stack.data = realloc(prog_stack.data, prog_stack.size);
    }

    prog_stack.sp++;
    prog_stack.data[prog_stack.sp] = w;
}

void bipush(int8_t b){
    wpush(b);
}

void dup(){
    bipush(tos());
}

void pop(){
    if(prog_stack.sp > -1){
        prog_stack.sp--;

        int new_size = prog_stack.sp + 1;
        if(new_size % INIT_ST_SIZE == 0){
            prog_stack.size = new_size;
            prog_stack.data = realloc(prog_stack.data, prog_stack.size);
        }
    }
}

word_t wpop(){
    word_t t = tos();
    pop();
    return t;
}

void swap(){
    word_t aux = prog_stack.data[prog_stack.sp - 1];
    prog_stack.data[prog_stack.sp - 1] = tos();
    prog_stack.data[prog_stack.sp] = aux;
}

void iand(){
    wpush(wpop() & wpop());
}

void iadd(){
    wpush(wpop() + wpop());
}

void ior(){
    wpush(wpop() | wpop());
}

void isub(){
    word_t rhs = wpop();
    word_t lhs = wpop();
    wpush(lhs - rhs);
}

void in(){
    byte_t b = fgetc(get_input());
    bipush(b);
}

void out(){
    fprintf(get_output(), "%c", wpop());
}
