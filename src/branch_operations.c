#include "branch_operations.h"
#include "ijvm.h"
#include "execution.h"
#include "stack.h"

int16_t ifeq(int16_t offset){
    if(wpop() == 0) return offset;
    else return 3;
}

int16_t iflt(int16_t offset){
    if(wpop() < 0) return offset;
    else return 3;
}

int16_t if_icmpeq(int16_t offset){
    if(wpop() == wpop()) return offset;
    else return 3;
}