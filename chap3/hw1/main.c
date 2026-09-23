#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAX_STRINGS 5

int main() {
    char lines[MAX_STRINGS][MAXLINE];
    char temp[MAXLINE];
    int i, j;

    for (i = 0; i < MAX_STRINGS; i++) {
        if (fgets(lines[i], MAXLINE, stdin) == NULL) break;
        lines[i][strcspn(lines[i], "\n")] = 0;
    }

    for (i = 0; i < MAX_STRINGS - 1; i++) {
        for (j = 0; j < MAX_STRINGS - 1 - i; j++) {
            if (strlen(lines[j]) < strlen(lines[j+1])) {
                copy(lines[j], temp);
                copy(lines[j+1], lines[j]);
                copy(temp, lines[j+1]);
            }
        }
    }

    for (i = 0; i < MAX_STRINGS; i++) {
        printf("%s\n", lines[i]);
    }
    return 0;
}
