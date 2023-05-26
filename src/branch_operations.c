#include "branch_operations.h"
#include "ijvm.h"
#include "execution.h"
#include "stack.h"

void _goto(int16_t offset){
    offset_pc(offset);
}

void ifeq(int16_t offset){
    if(wpop() == 0) offset_pc(offset);
    else offset_pc(3);
}

void iflt(int16_t offset){
    if(wpop() < 0) offset_pc(offset);
    else offset_pc(3);
}

void if_icmpeq(int16_t offset){
    if(wpop() == wpop()) offset_pc(offset);
    else offset_pc(3);
}