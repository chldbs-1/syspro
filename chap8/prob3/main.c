#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *ptr;

    ptr = getenv("HOME");
    printf("HOME = %s\n", ptr != NULL ? ptr : "(not set)");

    ptr = getenv("SHELL");
    printf("SHELL = %s\n", ptr != NULL ? ptr : "(not set)");

    ptr = getenv("PATH");
    printf("PATH = %s\n", ptr != NULL ? ptr : "(not set)");

    return 0;
}
