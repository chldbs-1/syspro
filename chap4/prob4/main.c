#include <stdio.h>
#include "student.h"

int main(int argc, char *argv[])
{
    struct student rec;
    FILE *fp;
    int score;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s FileName\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "w");
	printf("%s %s %s\n", "Student ID","Name","Score");

   
    while (scanf("%d %19s %d", &rec.id, rec.name, &score) == 3) {
        rec.score = (short)score;
        fprintf(fp, "%d %s %d\n", rec.id, rec.name, rec.score);
    }

    fclose(fp);
    return 0;
}

