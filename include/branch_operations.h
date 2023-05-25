#ifndef BRANCH_OPERATIONS_H
#define BRANCH_OPERATIONS_H

#include <stdint.h>

void _goto(int16_t offset);
void ifeq(int16_t offset);
void iflt(int16_t offset);
void if_icmpeq(int16_t offset);

#endif