#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
    int fd;
    int id;
    int new_score;
    struct student record;
    off_t position;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    while (1) {
        printf("\nEnter StudentID you want to modify: ");
        fflush(stdout);

        if (scanf("%d", &id) != 1)
            break;

        if (id < START_ID) {
            printf("Invalid student ID.\n");
            continue;
        }

        position = (off_t)(id - START_ID) * sizeof(record);

        if (lseek(fd, position, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            return 1;
        }

        if (lockf(fd, F_LOCK, sizeof(record)) == -1) {
            perror(argv[1]);
            close(fd);
            return 1;
        }

        if (read(fd, &record, sizeof(record)) == sizeof(record)
            && record.id != 0) {
            printf("Name:%s\tStuID:%d\tScore:%d\n",
                   record.name, record.id, record.score);

            printf("Enter new score: ");
            fflush(stdout);

            if (scanf("%d", &new_score) != 1) {
                close(fd);
                return 1;
            }

            record.score = new_score;

            if (lseek(fd, position, SEEK_SET) == -1 ||
                write(fd, &record, sizeof(record)) != sizeof(record)) {
                perror(argv[1]);
                close(fd);
                return 1;
            }

            printf("Score updated.\n");
        } else {
            printf("No record %d\n", id);
        }

        if (lseek(fd, position, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            return 1;
        }

        if (lockf(fd, F_ULOCK, sizeof(record)) == -1) {
            perror(argv[1]);
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}
