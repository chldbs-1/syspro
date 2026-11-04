#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("PID: %ld\n", (long)getpid());
    printf("PPID: %ld\n", (long)getppid());

    return 0;
}
