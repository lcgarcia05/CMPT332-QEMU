#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	printf("Number of cmpt procs in system: %d", sys_howmanycmpt());
	exit(0);
}