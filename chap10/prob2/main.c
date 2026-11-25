#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int id;
    char name[20];
    struct student *next;
};

int main(void)
{
    int count = 0;
    int id;
    char name[20];
    struct student *p;
    struct student *head = NULL;

    printf("Enter student ID and name.\n");
    printf("Enter a letter to finish.\n");

    while (scanf("%d %19s", &id, name) == 2) {
        p = malloc(sizeof(struct student));

        if (p == NULL) {
            fprintf(stderr, "Error: memory allocation failed.\n");

            while (head != NULL) {
                p = head;
                head = head->next;
                free(p);
            }

            return 1;
        }

        p->id = id;
        strcpy(p->name, name);

        p->next = head;
        head = p;
    }

    printf("\n* Student information (reverse order) *\n");

    p = head;

    while (p != NULL) {
        printf("ID: %d  Name: %s\n", p->id, p->name);
        count++;
        p = p->next;
    }

    printf("Total: %d students\n", count);

    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }

    return 0;
}
