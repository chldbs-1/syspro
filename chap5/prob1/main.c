#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file_name\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDWR);   

    if (fd == -1) {
        printf("file open error\n");
        exit(1);
    }

    printf("file %s success : %d\n", argv[1], fd);

    close(fd);
    return 0;
}

