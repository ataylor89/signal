#include <stdio.h>
#include <stdlib.h>

extern int sigint(int pid);

int main(int argc, char **argv) {
    if (argc == 2) {
        int pid = atoi(argv[1]);
        sigint(pid);
        printf("Sent a SIGINT signal to pid %d\n", pid);
    }
    else {
        printf("Usage: sigint <pid>");
    }
    return 0;
}
