#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_SIZE 256

int main(int argc, char* argv[]){
    char *toks[MAX_SIZE];
    char cmd[MAX_SIZE];
    int i, redirIN, redirOUT;
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
        i = 0;
        char* tok = strtok(cmd, " ");
        while(tok != NULL){
            toks[i] = tok;

            if (strcmp("<", tok) == 0){
                redirIN = i;
                i--;
            }
            else if (strcmp(">", tok) == 0){
                redirOUT = i;
                i--;
            }
            i++;
            tok = strtok(NULL, " ");
        }
        toks[i] = NULL;

        if (pipe(fd) == -1){
            return 1;
        }
        
        pid_t pid = fork();
        
            if (pid < 0){
                printf("Failed to create a child.");
                exit(1);
            }
            else if(pid == 0 ){
                if (redirOUT){
                    close(fd[0]);
                    if ((fd[1] = open(toks[redirOUT], O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) == -1){
                        perror(toks[redirOUT]);
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd[1], 1);
                    close(fd[1]);
                    toks[redirOUT] = NULL;
                }
                else if (redirIN){
                    close(fd[1]);
                    if ((fd[0] = open(toks[redirIN], O_RDONLY, 0)) == -1){
                        perror(toks[redirIN]);
                        exit(EXIT_FAILURE);
                    }

                    dup2(fd[0], 0);
                    close(fd[0]);
                    toks[redirIN] = NULL;
                }

                execvp(toks[0], toks);
                printf("wrdsh: %s: %s\n", toks[0], strerror(errno));
                exit(1);
            }
            else {
                wait(NULL);
                // printf("Child Exited\n");
            }
    }
    return 0;
}