#include <stdio.h>
#include <stdlib.h>

extern void sigterm(int pid);

int main(int argc, char **argv) {
    if (argc == 2) {
        int pid = atoi(argv[1]);
        sigterm(pid);
        printf("Sent a quit signal to pid %d.\n", pid);
    }
    else {
        printf("Usage: sigterm <pid>\n");
    }
    return 0;
}
