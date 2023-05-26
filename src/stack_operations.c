#include "stack_operations.h"
#include "ijvm.h"
#include "stack.h"
#include <stdlib.h>
#include "io.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"

void bipush(int8_t b){
    wpush(b);
    offset_pc(2);
}

void dup(){
    bipush(tos());
    offset_pc(1);
}

void pop(){
    wpop();
    offset_pc(1);
}

void swap(){
    word_t aux = prog_stack.data[prog_stack.sp - 1];
    prog_stack.data[prog_stack.sp - 1] = tos();
    prog_stack.data[prog_stack.sp] = aux;
    offset_pc(1);
}

void iand(){
    wpush(wpop() & wpop());
    offset_pc(1);
}

void iadd(){
    wpush(wpop() + wpop());
    offset_pc(1);
}

void ior(){
    wpush(wpop() | wpop());
    offset_pc(1);
}

void isub(){
    word_t rhs = wpop();
    word_t lhs = wpop();
    wpush(lhs - rhs);
    offset_pc(1);
}

void in(){
    byte_t b = fgetc(get_input());
    bipush(b);
    offset_pc(1);
}

void out(){
    fprintf(get_output(), "%c", wpop());
    offset_pc(1);
}
