#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd, status;
    pid_t pid, child;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s output_file command [arguments...]\n",
                argv[0]);
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);

        if (fd == -1) {
            perror(argv[1]);
            exit(1);
        }

        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            close(fd);
            exit(1);
        }

        close(fd);

        execvp(argv[2], &argv[2]);

        fprintf(stderr, "%s: cannot execute\n", argv[2]);
        exit(1);
    }

    child = wait(&status);

    if (child == -1) {
        perror("wait");
        return 1;
    }

    printf("[%d] child process %d end\n", getpid(), child);

    return 0;
}
