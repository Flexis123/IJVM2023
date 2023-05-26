#include "ijvm.h"
#include "execution.h"
#include "stack_operations.h"
#include "util.h"
#include "branch_operations.h"

static unsigned int pc = 0;
static bool err_flag = false;

unsigned int get_program_counter(void) 
{
  return pc;
}

void reset_program_counter(){
  pc = 0;
  err_flag = false;
}

void offset_pc(int16_t offset){
  pc += offset;
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

  case OP_GOTO:
    _goto(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_IFEQ:
    ifeq(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_IFLT:
    iflt(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_IF_ICMPEQ:
    if_icmpeq(read_uint16_t(get_text() + pc + 1));
    break;

  default:
    err_flag = true; 
    break;
  }
  return true;
}

void run(void) 
{
  while (!finished()) step();
}

byte_t get_instruction(void) 
{ 
  return get_text()[get_program_counter()]; 
}
