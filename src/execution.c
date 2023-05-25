#include "ijvm.h"
#include "execution.h"
#include "stack_operations.h"
#include "util.h"

static unsigned int pc = 0;
static bool err_flag = false;

unsigned int get_program_counter(void) 
{
  return pc;
}

void set_program_counter(unsigned int _pc){
  pc = _pc;
  err_flag = false;
}


bool finished(void) 
{
  return err_flag || pc >= get_text_size();
}

bool step(void) 
{
  switch (get_instruction())
  {
  case OP_BIPUSH:
    bipush(get_text()[pc + 1]);
    break;

  case OP_DUP:
    dup();
    break;

  case OP_IADD:
    iadd();
    break;

  case OP_IAND:
    iand();
    break;

  case OP_IOR:
    ior();
    break;

  case OP_ISUB:
    isub();
    break;

  case OP_NOP:
    break;

  case OP_POP:
    pop();
    break;

  case OP_SWAP:
    swap();
    break;

  case OP_IN:
    in();
    break;

  case OP_OUT:
    out();
    break;

  default:
    err_flag = true; 
    break;
  }
  pc++;
  return true;
}

void run(void) 
{
  while (!finished()) {
    step();
  }
}

byte_t get_instruction(void) 
{ 
  return get_text()[get_program_counter()]; 
}
