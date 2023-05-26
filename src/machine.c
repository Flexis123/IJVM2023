#include <stdio.h>  // for getc, printf
#include <stdlib.h> // malloc, free
#include "ijvm.h"

#define DEBUG_LEVEL 1
/* Adjust the above value to 0 to 5 to control debug prints.

The file util.h defines several macros for debug prints,
namely dprintf, d2printf, d3printf, d4printf and d5printf.

Which debug prints give outputs and which do not depends on the debug level.
If the debug level is 0, no debug prints will be printed. If the debug level
is n, all prints with a debug level less than or equal to n will be printed.

Debug prints which are disabled are not compiled into the program, so they
do not affect performance.

This gives you a method to log all kinds of things for debugging, and control
the granularity with a single variable.

Example: d2printf("Current program text %02x %02x\n", text[pc] , text[pc+1]);
*/
#include "util.h"
#include "stack.h"
#include "io.h"
#include "execution.h"

// see ijvm.h for descriptions of the below functions
struct block
{
  uint32_t size;
  byte_t* data;
};

struct block cons;
struct block text;

struct block read_block(FILE* fp){
  struct block bl;
  fread(&bl.size, sizeof(uint32_t), 1, fp);
  fread(&bl.size, sizeof(uint32_t), 1, fp);
  bl.size = swap_uint32(bl.size);

  bl.data = malloc(bl.size);
  fread(bl.data, sizeof(byte_t), bl.size, fp);
  return bl;
}

void destroy_block(struct block* bl){
  free(bl->data);
  bl->data = NULL;
  bl->size = 0;
}


int init_ijvm(char *binary_path) 
{
  set_input(stdin);
  set_output(stdout);
  reset_program_counter();

  uint32_t magic_num;
  FILE* fp = fopen(binary_path, "r");
  fread(&magic_num, sizeof(uint32_t), 1, fp);
  
  int res = -1;
  if(swap_uint32(magic_num) == MAGIC_NUMBER){
    res = 0;

    cons = read_block(fp);
    text = read_block(fp);

    create_stack();
  }

  fclose(fp);
  return res;
}

void destroy_ijvm(void) 
{
  destroy_block(&cons);
  destroy_block(&text);
  destroy_stack();
}

byte_t *get_text(void) 
{
  return text.data;
}

unsigned int get_text_size(void) 
{
  return text.size;
}

word_t get_constant(int i) 
{
  return read_uint32_t(&cons.data[i * sizeof(word_t)]);
}

