#include "ijvm.h"
#include "execution.h"
#include "operations.h"
#include "util.h"

static unsigned int pc = 0;
static bool err_flag = false;

unsigned int get_program_counter(void) {
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
  int16_t pc_offset = 0;
  switch (get_instruction())
  {
  case OP_BIPUSH:
    pc_offset = bipush(get_text()[pc + 1]);
    break;

  case OP_DUP:
    pc_offset = dup();
    break;

  case OP_IADD:
    pc_offset = iadd();
    break;

  case OP_IAND:
    pc_offset = iand();
    break;

  case OP_IOR:
    pc_offset = ior();
    break;

  case OP_ISUB:
    pc_offset = isub();
    break;

  case OP_NOP:
    pc_offset = 1;
    break;

  case OP_POP:
    pc_offset = pop();
    break;

  case OP_SWAP:
    pc_offset = swap();
    break;

  case OP_IN:
    pc_offset = in();
    break;

  case OP_OUT:
    pc_offset = out();
    break;

  case OP_GOTO:
    pc_offset = read_uint16_t(get_text() + pc + 1);
    break;

  case OP_IFEQ:
    pc_offset = ifeq(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_IFLT:
    pc_offset = iflt(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_IF_ICMPEQ:
    pc_offset = if_icmpeq(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_LDC_W:
    pc_offset = ldc_w(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_ILOAD:
    pc_offset = iload(get_text() + pc + 1);
    break;

  case OP_ISTORE:
    pc_offset = istore(get_text() + pc + 1);
    break;

  case OP_IINC:
    pc_offset = iinc(get_text() + pc + 1);
    break;

  case OP_WIDE:
    pc += wide();
    return step();

  case OP_INVOKEVIRTUAL:
    pc_offset = iinvokevirtual(read_uint16_t(get_text() + pc + 1));
    break;

  case OP_IRETURN:
    pc_offset = ireturn();
    break;

  default:
    err_flag = true; 
    return false;
  }

  pc += pc_offset;
  
  return true;
}

void run(void) {
  while (!finished()) step();
}

byte_t get_instruction(void) { 
  return get_text()[get_program_counter()]; 
}
