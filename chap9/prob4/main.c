#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int mysystem(const char *cmdstring)
{
    pid_t pid;
    int status;

    if (cmdstring == NULL) {
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        return -1;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)NULL);
        _exit(127);
    }

    while (1) {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) {
                return -1;
            }
        } else {
            return status;
        }
    }
}

int main(void)
{
    int status;

    status = mysystem("date");

    if (status == -1) {
        perror("mysystem");
    } else if (WIFEXITED(status)) {
        printf("end code %d\n", WEXITSTATUS(status));
    }

    status = mysystem("hello");

    if (status == -1) {
        perror("mysystem");
    } else if (WIFEXITED(status)) {
        printf("end code %d\n", WEXITSTATUS(status));
    }

    status = mysystem("who; exit 44");

    if (status == -1) {
        perror("mysystem");
    } else if (WIFEXITED(status)) {
        printf("end code %d\n", WEXITSTATUS(status));
    }

    return 0;
}
