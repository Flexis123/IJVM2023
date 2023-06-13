#include "operations.h"
#include "ijvm.h"
#include "stack.h"
#include <stdlib.h>
#include "io.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "execution.h"

int16_t bipush(int8_t b){
    wpush(b);
    return 2;
}

int16_t dup(){
    wpush(tos());
    return 1;
}

int16_t pop(){
    wpop();
    return 1;
}

int16_t swap(){
    word_t aux = prog_stack.data[prog_stack.sp - 1];
    prog_stack.data[prog_stack.sp - 1] = tos();
    prog_stack.data[prog_stack.sp] = aux;
    return 1;
}

int16_t iand(){
    wpush(wpop() & wpop());
    return 1;
}

int16_t iadd(){
    wpush(wpop() + wpop());
    return 1;
}

int16_t ior(){
    wpush(wpop() | wpop());
    return 1;
}

int16_t isub(){
    word_t rhs = wpop();
    word_t lhs = wpop();
    wpush(lhs - rhs);
    return 1;
}

int16_t in(){
    int b = fgetc(get_input());
    bipush(b != EOF ? b : 0);
    return 1;
}

int16_t out(){
    fprintf(get_output(), "%c", wpop());
    return 1;
}
