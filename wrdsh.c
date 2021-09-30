#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    char cmd[256];
    char* path= "/bin/";
    int i;
    char filePath[50];
    
    while(1){    
        i = 0;
        printf("wrdsh>");
        fgets(cmd, 256, stdin);
        // printf(cmd);
        cmd[strlen(cmd) - 1] = 0;
        
        char* tok = strtok(cmd, " ");
        while(tok != NULL){
            argv[i] = tok;
            i++;
            tok = strtok(NULL, " ");
        }
        
        if (strcmp ("exit", cmd) == 0){
            break;
        }
        if (strcmp ("", cmd) == 0){
            continue;
        }
        
        argv[i] = NULL;
        
        strcpy(filePath, path);
        strcat(filePath, argv[0]);
        
        pid_t pid = fork();
        
            if (pid < 0){
                printf("Failed to create a child.");
                exit(1);
            }
            else if(pid == 0 ){
                execvp(argv[0], argv);
            }
            else {
                wait(NULL);
                printf("Child Exited\n");
            }
    }
    return 0;
}