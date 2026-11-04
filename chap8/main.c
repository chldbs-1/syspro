#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

static void usage(const char *program)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  %s -e [NAME]\n", program);
    fprintf(stderr, "  %s -u\n", program);
    fprintf(stderr, "  %s -g\n", program);
    fprintf(stderr, "  %s -i\n", program);
    fprintf(stderr, "  %s -p\n", program);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            char **ptr;

            for (ptr = environ; *ptr != NULL; ptr++) {
                printf("%s\n", *ptr);
            }
        } else if (argc == 3) {
            char *value = getenv(argv[2]);

            if (value == NULL) {
                fprintf(stderr,
                        "Environment variable not found: %s\n",
                        argv[2]);
                return 1;
            }

            printf("%s=%s\n", argv[2], value);
        } else {
            usage(argv[0]);
            return 1;
        }
    } else {
        if (argc != 2) {
            usage(argv[0]);
            return 1;
        }

        if (strcmp(argv[1], "-u") == 0) {
            printf("Real UID: %lu\n",
                   (unsigned long)getuid());
            printf("Effective UID: %lu\n",
                   (unsigned long)geteuid());
        } else if (strcmp(argv[1], "-g") == 0) {
            printf("Real GID: %lu\n",
                   (unsigned long)getgid());
            printf("Effective GID: %lu\n",
                   (unsigned long)getegid());
        } else if (strcmp(argv[1], "-i") == 0) {
            printf("PID: %ld\n", (long)getpid());
        } else if (strcmp(argv[1], "-p") == 0) {
            printf("PPID: %ld\n", (long)getppid());
        } else {
            usage(argv[0]);
            return 1;
        }
    }

    return 0;
}
