#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node *top, int data)
{
    struct node *new_node;

    new_node = malloc(sizeof(struct node));

    if (new_node == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(1);
    }

    new_node->data = data;
    new_node->next = top->next;
    top->next = new_node;
}

int pop(struct node *top)
{
    struct node *temp;
    int data;

    if (top->next == NULL) {
        return -1;
    }

    temp = top->next;
    data = temp->data;
    top->next = temp->next;

    free(temp);

    return data;
}

int main(void)
{
    struct node top;
    int number;

    top.next = NULL;

    printf("Enter natural numbers. Enter a letter to finish.\n");

    while (scanf("%d", &number) == 1 && number > 0) {
        push(&top, number);
    }

    printf("Print stack\n");

    while (top.next != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}
