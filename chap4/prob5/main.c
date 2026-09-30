#include <stdio.h>
#include "student.h"

/* read student info from a text file and print */
int main(int argc, char *argv[])
{
    struct student rec;
    FILE *fp;
    int score;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s FileName\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error Open File\n");
        return 2;
    }

    printf("%-9s %-7s %-4s\n", "StudentID", "Name", "Score");
    while (fscanf(fp, "%d %19s %d", &rec.id, rec.name, &score) == 3) {
        rec.score = (short)score;
        printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    return 0;
}

