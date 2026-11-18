#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid, child, status;

    printf("[%d] Parent process start\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("[%d] Child process start\n", getpid());
        exit(1);
    }

    child = wait(&status);

    if (child == -1) {
        perror("wait");
        return 1;
    }

    printf("[%d] Child process %d end\n", getpid(), child);

    if (WIFEXITED(status)) {
        printf("\tExit code %d\n", WEXITSTATUS(status));
    }

    return 0;
}
