#include <stdio.h>
#include <stdlib.h>

struct student {
    int id;
    char name[20];
};

int main(void)
{
    struct student *ptr;
    int n, i;

    printf("How many students? ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: invalid number of students.\n");
        return 1;
    }

    ptr = malloc((size_t)n * sizeof(struct student));

    if (ptr == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    printf("Enter student ID and name for %d students.\n", n);

    for (i = 0; i < n; i++) {
        if (scanf("%d %19s", &ptr[i].id, ptr[i].name) != 2) {
            fprintf(stderr, "Error: invalid student information.\n");
            free(ptr);
            return 1;
        }
    }

    printf("\n*Student information  *\n");

    for (i = n - 1; i >= 0; i--) {
        printf("%d %s\n", ptr[i].id, ptr[i].name);
    }

    free(ptr);

    return 0;
}
