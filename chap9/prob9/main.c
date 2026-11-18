#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 128

void run_command(char *command)
{
    char spaced[MAXLINE * 3];
    char *args[MAXARG];
    char *input_file = NULL;
    char *output_file = NULL;
    char *token;
    char *saveptr;
    int argc = 0;
    int background = 0;
    int i, j = 0;
    pid_t pid;

    /* Make <, > and & separate tokens. */
    for (i = 0; command[i] != '\0'; i++) {
        if (command[i] == '<' ||
            command[i] == '>' ||
            command[i] == '&') {
            spaced[j++] = ' ';
            spaced[j++] = command[i];
            spaced[j++] = ' ';
        } else {
            spaced[j++] = command[i];
        }
    }

    spaced[j] = '\0';

    token = strtok_r(spaced, " \t\n", &saveptr);

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok_r(NULL, " \t\n", &saveptr);

            if (token == NULL) {
                fprintf(stderr, "Missing input file\n");
                return;
            }

            input_file = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok_r(NULL, " \t\n", &saveptr);

            if (token == NULL) {
                fprintf(stderr, "Missing output file\n");
                return;
            }

            output_file = token;
        } else if (strcmp(token, "&") == 0) {
            background = 1;
        } else {
            if (argc >= MAXARG - 1) {
                fprintf(stderr, "Too many arguments\n");
                return;
            }

            args[argc++] = token;
        }

        token = strtok_r(NULL, " \t\n", &saveptr);
    }

    args[argc] = NULL;

    if (argc == 0) {
        return;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        int fd;

        if (input_file != NULL) {
            fd = open(input_file, O_RDONLY);

            if (fd == -1) {
                perror(input_file);
                _exit(1);
            }

            if (dup2(fd, STDIN_FILENO) == -1) {
                perror("dup2");
                close(fd);
                _exit(1);
            }

            close(fd);
        }

        if (output_file != NULL) {
            fd = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 0660);

            if (fd == -1) {
                perror(output_file);
                _exit(1);
            }

            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("dup2");
                close(fd);
                _exit(1);
            }

            close(fd);
        }

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

int main(void)
{
    char line[MAXLINE];
    char *command;
    char *saveptr;

    while (1) {
        /* Collect background children that have finished. */
        while (waitpid(-1, NULL, WNOHANG) > 0) {
        }

        printf("[shell] ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (strcmp(line, "exit\n") == 0) {
            break;
        }

        command = strtok_r(line, ";", &saveptr);

        while (command != NULL) {
            run_command(command);
            command = strtok_r(NULL, ";", &saveptr);
        }
    }

    return 0;
}
