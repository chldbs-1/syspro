#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char savedText[10][100];

int main(int argc, char *argv[])
{
    int fd, row = 0, col = 0, i, n, m;
    char buf, input[100], *tok;

    if (argc < 2) {
        fprintf(stderr, "How to use: %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

  
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[row][col] = '\0';
            row++;
            col = 0;
        } else
            savedText[row][col++] = buf;
    }
    if (col > 0) {
        savedText[row][col] = '\0';
        row++;
    }
    close(fd);

    printf("File read success\n");
    printf("Total Line : %d\n", row);
    printf("You can choose 1 ~ %d Line\n", row);
    printf("Pls 'Enter' the line to select : ");
    scanf("%s", input);

    if (input[0] == '*') {                         
        for (i = 0; i < row; i++)
            printf("%d %s\n", i + 1, savedText[i]);
    } else if (strchr(input, '-') != NULL) {       
        sscanf(input, "%d-%d", &n, &m);
        for (i = n; i <= m && i <= row; i++)
            printf("%d %s\n", i, savedText[i - 1]);
    } else {                                        
		tok = strtok(input, ",");
        while (tok != NULL) {
            n = atoi(tok);
            if (n >= 1 && n <= row)
                printf("%d %s\n", n, savedText[n - 1]);
            tok = strtok(NULL, ",");
        }
    }
    exit(0);
}

