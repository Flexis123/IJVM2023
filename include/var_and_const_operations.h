#ifndef VAR_AND_CONST_OPERATIONS_H
#define VAR_AND_CONST_OPERATIONS_H

#include <stdint.h>
#include "ijvm.h"

int16_t ldc_w(uint16_t index);
int16_t iload(byte_t index);
int16_t istore(byte_t index);
int16_t iinc(byte_t index, byte_t inc);
int16_t wide();

#endif