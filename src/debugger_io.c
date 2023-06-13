#include "debugger_operations.h"
#include "ijvm.h"
#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
        printf("err in loading binary file!");
    }
}

void input(char* file_path){
    set_input(fopen(file_path, "w"));
}
