#include "operations.h"
#include "stack.h"
#include "util.h"

#define ARGC_TEXT_OFFSET 0
#define VARC_TEXT_OFFSET 2

int16_t iinvokevirtual(uint16_t method_ref){
    word_t method_pointer = get_constant(method_ref);

    uint16_t argc = read_uint16_t(get_text() + method_pointer + ARGC_TEXT_OFFSET);
    uint16_t varc = read_uint16_t(get_text() + method_pointer + VARC_TEXT_OFFSET);
    word_t args[argc];

    for(int i = argc - 1; i >= 0; i--) args[i] = wpop();

    add_frame(argc, args, varc);

    return (method_pointer + 4) - get_program_counter();
}

int16_t ireturn(){
    word_t ret_val = tos();
    unsigned int prev_pc = goto_prev_frame();
    wpush(ret_val);
    return (prev_pc + 3) - get_program_counter();
}
