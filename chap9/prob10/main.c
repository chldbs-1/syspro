#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 128

int main(void)
{
    char line[MAXLINE];
    char *args[MAXARG];
    char *token;
    char *saveptr;
    int argc;
    int background;
    pid_t pid;

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0) {
        }

        printf("[Shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        argc = 0;
        background = 0;

        token = strtok_r(line, " \t\n", &saveptr);

        while (token != NULL) {
            if (argc >= MAXARG - 1) {
                fprintf(stderr, "Too many arguments\n");
                break;
            }

            args[argc++] = token;
            token = strtok_r(NULL, " \t\n", &saveptr);
        }

        if (argc == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            argc--;
        }

        args[argc] = NULL;

        if (argc == 0) {
            continue;
        }

        pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);
            perror(args[0]);
            _exit(1);
        }

        if (background) {
            printf("Background PID: %d\n", pid);
        } else {
            if (waitpid(pid, NULL, 0) == -1) {
                perror("waitpid");
            }
        }
    }

    return 0;
}
