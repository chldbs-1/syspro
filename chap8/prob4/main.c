#include <stdio.h>
#include <stdlib.h>

static void exit_handler1(void);
static void exit_handler2(void);

int main(void)
{
    if (atexit(exit_handler1) != 0) {
        fprintf(stderr, "Failed to register handler1\n");
        return 1;
    }

    if (atexit(exit_handler2) != 0) {
        fprintf(stderr, "Failed to register handler2\n");
        return 1;
    }

    printf("main end\n");

    exit(0);
}

static void exit_handler1(void)
{
    printf("first exit handler\n");
}

static void exit_handler2(void)
{
    printf("second exit handler\n");
}
