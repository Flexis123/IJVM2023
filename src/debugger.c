#include <stdio.h>
#include <string.h>
#include "debugger_operations.h"
#include "ijvm.h"
#include "util.h"
#include <readline/readline.h>
#include <stdlib.h>

int main(){
    printf("IJVM debugger, type 'help' for more info\n");

    while(1){
        char* cmd = readline("IJVMdbg> ");
        char* cmd_name;
        
        cmd_name = strtok(cmd, " ");
        printf("cmd_name=%s\n", cmd_name);

        if(strcmp(cmd_name, "help") == 0){
            help();
        }else if(strcmp(cmd_name, "file") == 0){
            file(strtok(NULL, " "));
        }else if(strcmp(cmd_name, "run") == 0){

        }else if(strcmp(cmd_name, "input") == 0){
            input(strtok(NULL, " "));
        }else if(strcmp(cmd_name, "break") == 0){
            
        }else if(strcmp(cmd_name, "step") == 0){
            step();
        }else if(strcmp(cmd_name, "continue") == 0){

        }else if(strcmp(cmd_name, "info") == 0){

        }else if(strcmp(cmd_name, "backtrace") == 0){

        }else if(strcmp(cmd_name, "q") == 0){
            destroy_ijvm();
            break;
        }else{
            printf("invalid command here are the valid commands:\n");
            help();
        }

        free(cmd);
        cmd = NULL;
    }
    return 0;
}
