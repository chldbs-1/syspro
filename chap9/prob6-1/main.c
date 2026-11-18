#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;

    printf("[PARENT] PID = %d GID = %d\n", getpid(), getpgrp());

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("[CHILD] PID = %d GID = %d\n", getpid(), getpgrp());
    }

    return 0;
}
