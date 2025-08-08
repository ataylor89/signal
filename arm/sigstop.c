#include <stdio.h>
#include <stdlib.h>

extern void sigstop(int pid);

int main(int argc, char **argv) {
    if (argc == 2) {
        int pid = atoi(argv[1]);
        sigstop(pid);
        printf("Sent a stop signal to pid %d.\n", pid);
    }
    else {
        printf("Usage: sigstop <pid>\n");
    }
    return 0;
}
