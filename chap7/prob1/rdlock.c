#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
    int fd;
    int id;
    struct student record;
    struct flock lock;
    off_t position;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        return 1;
    }

    while (1) {
        printf("\nEnter StudentID to search: ");
        fflush(stdout);

        if (scanf("%d", &id) != 1)
            break;

        if (id < START_ID) {
            printf("Invalid student ID.\n");
            continue;
        }

        position = (off_t)(id - START_ID) * sizeof(record);

        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = position;
        lock.l_len = sizeof(record);
        lock.l_pid = 0;

        if (fcntl(fd, F_SETLKW, &lock) == -1) {
            perror(argv[1]);
            close(fd);
            return 1;
        }

        if (lseek(fd, position, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            return 1;
        }

        if (read(fd, &record, sizeof(record)) == sizeof(record)
            && record.id != 0) {
            printf("Name:%s\tStuID:%d\tScore:%d\n",
                   record.name, record.id, record.score);
        } else {
            printf("No record %d\n", id);
        }

        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror(argv[1]);
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}
