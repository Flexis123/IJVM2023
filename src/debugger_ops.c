#include "debugger_operations.h"
#include "ijvm.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "util.h"

void help(){
    FILE* fp = fopen("debugger_help.txt", "r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char help_msg[size];
    fread(help_msg, sizeof(char), size, fp);
    printf("%s", help_msg);
}

void file(char* binary_path){
    destroy_ijvm();
    if(init_ijvm(binary_path) != 0){
        printf("err in loading program %s!", binary_path);
        return;
    }
    printf("loaded %s program\n", binary_path);
}

void input(char* file_path){
    FILE* fp = fopen(file_path, "r");
    if(fp == NULL){
        printf("err in opening input %s", file_path);
        return;
    }
    set_input(fp);
}

unsigned int breakpoints[256];
unsigned int b = 0;

void breakpoint(unsigned int addr){
    breakpoints[b] = addr;
    b++;
}

void bstep(){
    if(!step()) printf("program finished cannot step anymore");
}

void brun(){
    while(get_program_counter()){}
}
