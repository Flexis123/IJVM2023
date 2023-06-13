#include <stdio.h>
#include <string.h>
#include "debugger_operations.h"
#include "ijvm.h"
#include "util.h"
#include <readline/readline.h>

int main(){
    printf("IJVM debugger, type 'help' for more info\n");

    while(1){
        char* cmd;
        char* cmd_name;
        
        cmd = readline("IJVMdbg> ");

        cmd_name = strtok(cmd, " ");

        if(strcmp(cmd_name, "help") == 0){
            help();
        }else if(strcmp(cmd_name, "file") == 0){
            file(strtok(cmd, NULL));
        }else if(strcmp(cmd_name, "run") == 0){

        }else if(strcmp(cmd_name, "input") == 0){
            input(strtok(cmd, NULL));
        }else if(strcmp(cmd_name, "break") == 0){

        }else if(strcmp(cmd_name, "step") == 0){

        }else if(strcmp(cmd_name, "continue") == 0){

        }else if(strcmp(cmd_name, "info") == 0){

        }else if(strcmp(cmd_name, "backtrace") == 0){

        }else if(strcmp(cmd_name, "q") == 0){
            break;
        }else{
            printf("invalid command here are the valid commands:\n");
            help();
        }
        
      
    }
    return 0;
}
