#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	int pid;
    int n = 0;
    for (n = 0; n < argc; ++n){
        pid = fork();
        sys_howmanycmpt();
    }
    printf("Number of cmpt procs in system: %d", sys_howmanycmpt());
    exit(0);
}