#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{

    int pid = fork();
    int rtime = 0;
    int wtime = 0;

    if (pid < 0){
        printf("Failed to create child...\n");
        exit(-1);
    }
    else if(pid == 0){
        printf("Child process created...\n");
        exit(0);
    }
    else{
        waitstat(0, &wtime, &rtime);
    }

    exit(0);
}
