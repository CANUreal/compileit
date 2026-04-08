#include "builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void build_project(char *lang, char *project_path){
//utils.c den bilgi alan fonksiyon
char **argv = NULL;

if (strcmp(lang, "C") == 0) {
        argv = prepare_args("gcc" , path);
    }
else if (strcmp(lang, "Rust") == 0) {
        argv = prepare_args("cargo", path);
    }
if (argv != NULL){
        printf("\n[BUILD] Project %s is getting compiled...", lang)
        run_command(argv);
    }
for (int i = 0; argv[i] != NULL; i++){
        free(argv[i]);
    }
free(argv);
}
void run_command(char **argv){
//derleme komudunu string dizisine çevirecek fonksiyon
pid_t pid;
int status;
pid=fork();

if (pid < 0){
    perror("we have a problem and its not good");
    return;
    }
else if (pid == 0) {
    if(execvp(argv[0,argv]) == -1){
        perror("execvp error");
    }
    exit(EXIT_FAILURE);
}
else {
    do{
        waitpid(pid,&status,WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0){
        printf("\n[SUCCESS] Compiling is over without any problems\n");
    } else {
        printf("\n[ERROR] debug time lil bro");
    } 
  }
}
void handle_compile_error(int status){
    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        printf("\n[DEBUG] Compiler exited with code:%d \n");
    
    if (exit_code == 1){
        printf("\n[ERROR] Syntax Error (tip:debug it with gdb)\n");
    } else if (exit_code == 127) {
        printf("\n[ERROR]No installed compiler on your computer install a compiler and come back.");
    } else if (WIFSIGNALED(status)) {
        printf("\n[FATAL] Compiler got out with a signal:%d \n");
    }
  }
}
