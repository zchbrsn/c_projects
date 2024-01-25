#include <stdio.h>
#include <stdlib.h>

// common tasks for nodes
    // Add a new node to the head
    // Insert at head ??
    // Find a node
    // Insert after node (using find)

// Node structure
struct node {
    int value;
    struct node * next;
};
typedef struct node node_t;

// Print each node from head to tail
void printlist(node_t *head) {
    node_t *temp = head;

    while(temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {

    node_t n1, n2, n3;
    node_t *head;

    n1.value = 10;
    n2.value = 20;
    n3.value = 30;

    // Link them with pointers to nodes
    head = &n3;
    n3.next = &n2;
    n2.next = &n1;
    n1.next = NULL;
    // Last pointer needs to be null so we know when to stop

    printlist(head);

    // Add more nodes
    node_t n4, n5, n6;
    n4.value = 40;
    n5.value = 50;
    n6.value = 60;

    // Change the ordering of nodes so that the head starts at the top, point n4 -> n3, move head -> n6
    n4.next = &n3;
    n5.next = &n4;
    n6.next = &n5;
    head = &n6;

    printlist(head);

    // Move the link further into the list
    head = head->next;

    printlist(head);
    
    return 0;
}