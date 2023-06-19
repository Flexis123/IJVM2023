#include "debugger_operations.h"
#include "ijvm.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "util.h"
#include <readline/readline.h>

void help(){
    FILE* fp = fopen("debugger_help.txt", "r");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char help_msg[size];
    fread(help_msg, sizeof(char), size, fp);
    printf("%s", help_msg);
}

static char* curr_bin;

void file(char* binary_path){
    destroy_ijvm();
    if(init_ijvm(binary_path) != 0){
        printf("err in loading program %s!", binary_path);
        return;
    }
    printf("loaded %s program\n", binary_path);
    curr_bin = binary_path;
}

void input(char* file_path){
    FILE* fp = fopen(file_path, "r");
    if(fp == NULL){
        printf("err in opening input %s", file_path);
        return;
    }
    set_input(fp);
}

static unsigned int breakpoints[256];
static unsigned int b = 0;
static bool prog_running = false;

bool is_breakpoint(unsigned int addr){
    for(unsigned int i = 0; i < b; i++){
        if(breakpoints[i] == addr) return true;
    }
    return false;
}

void bbreak(unsigned int addr){
    breakpoints[b] = addr;
    b++;
}

void _prog_epilogue(){
    bool decision_ok = false;
    while(!decision_ok){
        decision_ok = true;
        char* decision = readline("Program has finished, wan't to kill or restart? [k/r]: ");

        if(strcmp("k", decision) == 0) destroy_ijvm();
        else if (strcmp("r", decision) == 0) file(curr_bin);
        else decision_ok = false;
    }
}

void bstep(){
    if(!step() || finished()) _prog_epilogue();
}

void _run(){
    while(!is_breakpoint(get_program_counter()) && !finished()) step();

    if(finished()) _prog_epilogue();
    else printf("breakpoint reached at addr %u\n", get_program_counter());
}

void brun(){
    if(!prog_running) {
        prog_running = true;
        _run();
    }
    else {
        bool decision_ok = false;
        while(!decision_ok){
            decision_ok = true;
            char* decision = readline("Program is running, wan't to kill or restart the current program? [k/r]: ");

            if(strcmp("k", decision) == 0){
                prog_running = false;
                destroy_ijvm();
            } 
            else if (strcmp("r", decision) == 0) {
                file(curr_bin);
                _run();
            }
            else decision_ok = false;
        }
    }
}

void bcontinue(){
    if(is_breakpoint(get_program_counter())) bstep();
    _run();
}
