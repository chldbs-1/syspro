#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int pid;

    pid = fork();

    if (pid == 0) {
        printf("[Child] Hello, world! Pid =%d\n", getpid());
    } else if (pid > 0) {
        printf("[Parent] Hello, world! Pid =%d\n", getpid());
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
