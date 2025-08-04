#include <stdio.h>
#include <stdlib.h>

extern void sigcont(int pid);

int main(int argc, char **argv) {
    if (argc == 2) {
        int pid = atoi(argv[1]);
        sigcont(pid);
        printf("Sent a SIGCONT signal to pid %d.\n", pid);
    }
    else {
        printf("Usage: sigcont <pid>\n");
    }
    return 0;
}
