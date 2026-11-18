#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("Parent process start\n");

    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);

        fprintf(stderr, "First command failed\n");
        exit(1);
    }

    printf("Parent process end\n");

    return 0;
}
