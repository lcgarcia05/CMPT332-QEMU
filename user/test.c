#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <kernel/proc.h>



int main(int argc, char *argv[]) {
	for(int i = 0; i<15; i++){
        pidt pid = fork();
        if (pid == 0) {
            printf(strcat("Processing P's child number ", i));
        }
        else{
            waitstat();
            exit(0);
        }
    }
    exit(0);
}