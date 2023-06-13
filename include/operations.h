#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "ijvm.h"

int16_t bipush(int8_t b);
int16_t dup();
int16_t iand();
int16_t iadd();
int16_t ior();
int16_t isub();
int16_t pop();
int16_t swap();
int16_t in();
int16_t out();

int16_t ifeq(int16_t offset);
int16_t iflt(int16_t offset);
int16_t if_icmpeq(int16_t offset);

int16_t ldc_w(uint16_t index);
int16_t iload(byte_t* index);
int16_t istore(byte_t* index);
int16_t iinc(byte_t* args);
int16_t wide();

int16_t iinvokevirtual(uint16_t method_ref);
int16_t ireturn();


#endif

