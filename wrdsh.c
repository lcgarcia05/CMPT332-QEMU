#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 256

int main(int argc, char* argv[]){
    char *toks[MAX_SIZE];
    char cmd[MAX_SIZE];
    // char* path= "/bin/";
    int i;
    // char filePath[50];
    
    while(1){

        // Prompt and get the command
        printf("wrdsh>");
        fgets(cmd, 256, stdin);
        // printf("Arguments given: %s", cmd);
        cmd[strlen(cmd) - 1] = 0;

        if (strcmp("", cmd) == 0 ){
            continue;
        }
        
        if (strcmp ("exit", cmd) == 0){
            break;
        }

        // Convert command into tokens
        i = 0;
        char* tok = strtok(cmd, " ");
        while(tok != NULL){
            toks[i] = tok;
            i++;
            tok = strtok(NULL, " ");
        }
        toks[i] = NULL;

        if (i == 0){
            continue;
        }
        
        
        pid_t pid = fork();
        
            if (pid < 0){
                printf("Failed to create a child.");
                exit(1);
            }
            else if(pid == 0 ){
                execvp(toks[0], toks);
                printf("wrdsh: %s: %s\n", toks[0], toks);
            }
            else {
                wait(NULL);
                // printf("Child Exited\n");
            }
    }
    return 0;
}