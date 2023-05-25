#include "io.h"
#include <stdio.h>

static FILE *in;   // use fgetc(in) to get a character from in.
            // This will return EOF if no char is available.
static FILE *out;  // use for example fprintf(out, "%c", value); to print value to out

void set_input(FILE *fp) 
{ 
  in = fp; 
}

void set_output(FILE *fp) 
{ 
  out = fp; 
}

FILE* get_output(){
  return out;
}

FILE* get_input(){
  return in;
}