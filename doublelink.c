#include <stdio.h>
#include <stdlib.h>

// Node Structure
typedef struct node {
    int value;
    struct node *next;
} node_t;

// Allocate and add nodes in ascending sorted order
node_t *create(node_t **head, int value) {
    node_t *node = malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;

    if (*head == NULL || value < (*head)->value) {
        node->next = *head;
        *head = node;
        return node;
    }

    node_t *current = *head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
    return node;
}

// Print all the nodes in a list
void print(node_t *head) {
    if (head == NULL) {
        printf("Empty list\n");
        return;
    }

    node_t *temp = head;

    while(temp != NULL) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

// Reverse order of nodes in list
void reverse(node_t **head) {
    node_t *prev = NULL;
    node_t *current = *head;
    node_t *next = NULL;

    while(current != NULL) {
        next = current->next;       // Point next to current->next
        current->next = prev;       // Current points to previous
        prev = current;             // Previous moves to next node in list
        current = next;             // Current moves to next node in list
    }
    *head = prev;
}

// Find a value in the list
node_t *find(node_t **head, int value) {
    node_t *current = *head;

    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Find and remove a node
void removeNode(node_t **head, int value) {
    if (*head != NULL && (*head)->value == value) {
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    node_t *current = *head;

    while (current->next != NULL && current->value != value) {
        if (current->next->value == value) {
            printf("Removing %d\n", current->next->value);
            node_t *temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else {
            current = current->next;
        }
    }
}

// Destroy the entire list
void destroy(node_t **head) {
    while (*head != NULL) {
        printf("Removing %d\n", (*head)->value);
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main(void) {

    node_t *head = NULL;
    node_t *node = NULL;

    reverse(&head);
    
    node = create(&head, 42);
    node = create(&head, 17);
    node = create(&head, 3);
    node = create(&head, 57);
    node = create(&head, 91);
    node = create(&head, 1);
    node = create(&head, 29);
    node = create(&head, 13);

    print(head);
    reverse(&head);
    print(head);

    node_t *found = find(&head, 57);
    printf("Found %d\n", found->value);

    removeNode(&head, 29);

    print(head);

    destroy(&head);

    print(head);

}