#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_SIZE 256

int main(int argc, char* argv[]){
    char *toks[MAX_SIZE];
    char cmd[MAX_SIZE];
    char *rcmd[MAX_SIZE];
    char *newcmd[MAX_SIZE];
    int i, redirIN, redirOUT, index,j;
    int fd[2];

    while(1){

        // Prompt and get the command
        printf("wrdsh> ");
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
        redirIN = 0;
        redirOUT = 0;
        index = 0;
        i = 0;
        j=0;
        char *tok = strtok(cmd, " ");
        rcmd[index] = tok;
        index++;
        while(tok != NULL){
            toks[i] = tok;

            if (strcmp(">", tok) == 0){
                redirIN = i;
                i--;
            }
            else if (strcmp("<", tok) == 0){
                redirOUT = i;
                i--;
            }
            i++;
            tok = strtok(NULL, " ");
            index++;
        }
        index--;

        // If the given args is not a single command
        // This is where the hardcoded parts are
        if (i > 2){
            for (j=index-1; j>=0; j--){
                newcmd[j] = toks[j];
            }

            char *temp = newcmd[1];
            char *temp2 = newcmd[0];
            newcmd[0] = temp;
            newcmd[1] = newcmd[2];
            newcmd[2] = temp2;
        }

        toks[i] = NULL;
        newcmd[i] = NULL;

        // Create pipe
        if (pipe(fd) == -1){
            return 1;
        }
        
        // Fork
        pid_t pid = fork();
        
        // Fork error checking
        if (pid < 0){
            printf("Failed to create a child.");
            exit(EXIT_FAILURE);
        }
        // Child process
        else if(pid == 0 ){
            // If user wants to redirect stdout
            if (redirOUT){
                close(fd[0]);
                redirOUT = 0;
                if((fd[1] = open(toks[redirOUT], O_WRONLY | O_CREAT, 0777)) == -1){
                    perror(toks[redirOUT]);
                    exit(EXIT_FAILURE);
                }
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    toks[redirOUT] = NULL;
                }
                // If user wants to redirect stdin
                else if (redirIN){
                    redirIN = 0;
                    if ((fd[0] = open(toks[redirIN], O_RDONLY, 0)) == -1){
                        perror(toks[redirIN]);
                        exit(EXIT_FAILURE);
                    }

                    dup2(fd[0], STDIN_FILENO);
                    close(fd[0]);
                    toks[redirIN] = NULL;
                }

                // If given args is more than 2, which means that we are redirecting so use newcmd for the complete commands
                if (i > 2){
                    execvp(newcmd[0], newcmd);
                    printf("wrdsh: %s: command not found\n", newcmd[0]);
                    exit(1);
                }
                // If only 1 argument
                else{
                    execvp(toks[0], toks);
                    printf("wrdsh: %s: command not found\n", toks[0]);
                    exit(1);
                }
            }
            else {
                wait(NULL);
                // printf("Child Exited\n");
                
            }
    }
    return 0;
}