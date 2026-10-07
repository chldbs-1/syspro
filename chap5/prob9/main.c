#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char text[100][100];

int main(int argc, char *argv[])
{
    int fd, total = 0, col = 0, i;
    char buf;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file_name\n", argv[0]);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        exit(2);
    }
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            text[total][col] = '\0';
            total++;
            col = 0;
        } else if (col < 99) {
            text[total][col++] = buf;
        }
    }
    if (col > 0) {
        text[total][col] = '\0';
        total++;
    }
    close(fd);

    for (i = total - 1; i >= 0; i--)    
        printf("%s\n", text[i]);
    return 0;
}

