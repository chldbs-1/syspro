#include <stdio.h>

extern char **environ;

int main(void)
{
    char **ptr;

    for (ptr = environ; *ptr != NULL; ptr++) {
        printf("%s\n", *ptr);
    }

    return 0;
}
