#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char str[32] = "Do you like Linux?";
    char *ptr;
    char *p;

    ptr = malloc(32);

    if (ptr == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    memcpy(ptr, str, strlen(str) + 1);
    puts(ptr);

    memset(ptr + 12, 'l', 1);
    puts(ptr);

    p = memchr(ptr, 'l', strlen(ptr));

    if (p != NULL) {
        puts(p);
    }

    memmove(str + 12, str + 7, 10);
    puts(str);

    free(ptr);

    return 0;
}
