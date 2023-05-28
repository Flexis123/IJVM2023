#ifndef BRANCH_OPERATIONS_H
#define BRANCH_OPERATIONS_H

#include <stdint.h>

int16_t ifeq(int16_t offset);
int16_t iflt(int16_t offset);
int16_t if_icmpeq(int16_t offset);

#endif