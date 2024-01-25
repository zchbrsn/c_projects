#include <stdlib.h>
#include <stdio.h>

/*
First need a struct for node.  Each struct needs a data type value and a node pointer next
    datatype value;
    struct node *next;

Create - take in a value
    1. A new node to allocate memory sizeof node
    2. Set the node->value to the passed argument
    3. Set the node->next to NULL (add it later)
Add - take in the **head and a *node  IN ORDER
    1. Set the arg passed node->next to the *head node
    2. Set the *head node to the arg passed node
    3. Return the node
Destroy List - 
Remove - take in the **head and value to delete
    1. Two cases -- if destroying the head or any other node
    2. Destroying the head node
        If the head is not null, but contains the value
        Create a temp node to be deleted and set equal to *head
        Move the head to the next node *head = (*head)->next
        Free temp node
    3. Destroying other nodes - need to traverse the linked list
        Create a current *node = *head to start at the top of the list
        While current is not NULL and not value
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
Reverse - take in **head
    Base case if head = null
    temp = head
    prev = head
    tail = head
    while temp.next != NULL
    if tail == head - tail.next = NULL
    else - next = temp.next
    tmp.next = tail
    tail = tmp

    prev = tmp
    temp = temp.next
*/

// Need to create the data structure
struct node {
    int value;
    struct node *next;
}; typedef struct node node_t;

// Create a new node (assign it to a variable)
node_t *createNode(int value) {
    // Allocate memory for the node
    node_t *node = malloc(sizeof(node_t));
    // Set the value of the node to value
    node->value = value;
    // Does not get added to the linked list yet
    node->next = NULL;
    return node;
}

void destroyNode(node_t **head, int value) {
    // Destroying a head node
    // If the head node is not null, but contains the value
    if (*head != NULL && (*head)->value == value) {

        // Creating temp node to hold the head
        node_t *tmp = *head;
        // Move the head to the next node
        *head = (*head)->next;
        // Free the tmp node, it is no longer the head and also removed
        free(tmp);
    }
    // Deleting other nodes
    // Start at the head of the linked list
    node_t *currentNode = *head;
    while (currentNode != NULL && currentNode->next != NULL) {
        
        // Check to see if the next node holds the target value
        // This ensures we are the preceding node
        if (currentNode->next->value == value) {
            
            // Set the tmp node to the next node to destroy
            node_t *tmp = currentNode->next;
            // Point the current node to the node after the destroyed node
            currentNode->next = currentNode->next->next;
            free(tmp);
        }
        else {
            // Continue iterating through the linked list
            currentNode = currentNode->next;
        }
    }
}

// destroy list
    // temp node
    // while head ! null
    // temp = head
    // head = head next
    // free temp

void *addNode(node_t **head, node_t *node) {
    // Set the current node to point to the head node
    node->next = *head;
    // Put the node to be added as the head node
    *head = node;
    return node;
}

// Finds a value in the linked list
void *findNode(node_t *head, int value) {

    // Set the tmp node to the head of the list
    node_t *tmp = head;

    // Check each value until the end of the list
    while (tmp != NULL) {
        // if the value is equal, return the node
        if (tmp->value == value) {
            return tmp;
        }
        // Continue going to the next nodes
        tmp = tmp->next;
    }
    // Return NULL if the value is not found
    return NULL;
}

// Inserts the newNode after the currentNode
void insertNode(node_t *currentNode, node_t *newNode) {

    // head, pos, value
    // prev node = temp node
    // move temp = temp->next until pos
    // increment pos
    // new node == create node
    // prev.next = new node
    // new node.next = temp.next



    // Should use findNode to first set the current node
    // Inserting a new node should use createNode as the second argument
    // The new node's next needs to point to current node's next (e.g., current = 10, new = 10)
    newNode->next = currentNode->next;

    // The current node's next now needs to point to the new node (e.g., current = 9, new = 10)
    currentNode->next = newNode;
}

void printNode(node_t *head) {
    node_t *temp = head;

    while (temp != NULL) {
        printf("%d ->", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    node_t *head = NULL;
    node_t *tmp;

    for (int i = 0; i < 25; i++) {
        tmp = createNode(i);
        addNode(&head, tmp);
    }

    node_t *val1 = findNode(head, 5);
    node_t *val2 = findNode(head, 6);
    printf("Val1 = %d\n", val1->value);
    printf("Val2 = %d\n", val2->value);

    destroyNode(&head, 5);

    printf("Val1 = %d\n", val1->value);
    printf("Val2 = %d\n", val2->value);

    printNode(tmp);

    tmp = findNode(head, 25);
    printf("%d\n", tmp);

    destroyNode(&head, 0);

    return 0;
}