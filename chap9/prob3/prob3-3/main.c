#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid, child, status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [arguments...]\n", argv[0]);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], &argv[1]);

        fprintf(stderr, "%s: cannot execute\n", argv[1]);
        exit(1);
    }

    child = wait(&status);

    if (child == -1) {
        perror("wait");
        return 1;
    }

    printf("[%d] child process %d end\n", getpid(), child);

    if (WIFEXITED(status)) {
        printf("\tend code %d\n", WEXITSTATUS(status));
    }

    return 0;
}
