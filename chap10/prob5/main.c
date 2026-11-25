#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data)
{
    struct node *new_node;

    new_node = malloc(sizeof(struct node));

    if (new_node == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(1);
    }

    new_node->data = data;
    new_node->next = NULL;

    if (head->next == NULL) {
        head->next = new_node;
    } else {
        tail->next->next = new_node;
    }

    tail->next = new_node;
}

int delete(struct node *head, struct node *tail)
{
    struct node *temp;
    int data;

    if (head->next == NULL) {
        return -1;
    }

    temp = head->next;
    data = temp->data;
    head->next = temp->next;

    if (head->next == NULL) {
        tail->next = NULL;
    }

    free(temp);

    return data;
}

int main(void)
{
    struct node head;
    struct node tail;
    int number;

    head.next = NULL;
    tail.next = NULL;

    printf("Enter natural numbers. Enter a letter to finish.\n");

    while (scanf("%d", &number) == 1 && number > 0) {
        addq(&head, &tail, number);
    }

    printf("Print queue\n");

    while (head.next != NULL) {
        printf("%d\n", delete(&head, &tail));
    }

    return 0;
}
