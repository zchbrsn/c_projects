/*
First need a struct for node.  Each struct needs a data type value and a node pointer next
    datatype value;
    struct node *next;
    Node needs to be a pointer

Create - is a pointer -- take in a value
    1. A new node to allocate memory sizeof node
    2. Set the node->value to the passed argument
    3. Set the node->next to NULL (add it later)
Add - is a pointer -- take in the **head and a *node
    1. Set the arg passed node to the *head node
    2. Set the *head node to the arg passed node
    3. Return the node
Remove - 
Destroy - take in the **head and value to delete
    1. Two cases -- if destroying the head or any other node
    2. Destroying the head node
        If the head is not null, but contains the value
        Create a temp node to be deleted and set equal to *head
        Move the head to the next node *head = (*head)->next
        Free temp node
    3. Destroying other nodes - need to traverse the linked list
        Create a current *node = *head to start at the top of the list
        While current is not NULL and current->next is not NULL
        If the current->next->value == value
            Create a temp node and set it to the next node; temp = current->next
            Set the current->next to the current->next->next to bring the links back together
            free the temp node
        Otherwise, continue iterating through the list; current = current->next
Print - takes in the *head
    Create a temp node to hold the current value and set it to the head of the list
    While the the temp node is not NULL
        Print temp->value
        temp = temp->next
*/

#include <stdlib.h>
#include <stdio.h>

struct node {

    char *value;
    struct node *next;

}; typedef struct node node_t;

node_t *createNode(char *value) {
    node_t *temp = malloc(sizeof(node_t));
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void *addNode(node_t **head, node_t *node) {
    node->next = *head;
    *head = node;
    return node;
}

void destroyNode(node_t **head, char *value) {
    if (*head != NULL && (*head)->value == value) {
        node_t *temp = *head;

        *head = (*head)->next;
        free(temp);
    }
    
    node_t *currentNode = *head;
    while (currentNode != NULL && currentNode->next != NULL) {
        if (currentNode->next->value == value) {
            node_t *temp = currentNode->next;
            currentNode->next = currentNode->next->next;
            free(temp);
        }
        else {
            currentNode = currentNode->next;
        }
    }
}

void printNodes(node_t *head) {
    node_t *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->value);
        temp = temp->next;
    }
}

int main(void) {

    node_t *ll;
    node_t *head = NULL;
    node_t *tail;

    ll = createNode("This is a test");
    addNode(&head, ll);
    //printf("%s\n", temp->value);
    ll = createNode("This is my second node");
    addNode(&head, ll);
    //printf("%s\n", temp->value);
    ll = createNode("Third element");
    addNode(&head, ll);
    ll = createNode("Fourth element");
    addNode(&head, ll);

    printNodes(head);

    destroyNode(&head, "This is a test");

    printNodes(head);




}