/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;

    if (*head == NULL) {    // empty list
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    Node *node = make_node(val, *head);
    *head = node;

    //*head = make_node(val, *head);
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    Node *current = *head;
    Node *previous = NULL;
    int cnt = 0;

    while (current != NULL) {
        if (current->val == val) {
            if (previous != NULL) {
                previous->next = current->next;
                free(current);
            }
            else {  // previous == NULL, means current is head
                pop(head);
            }
            ++cnt;
            break;  // remove the first element only as stated
        }
        previous = current;
        current = current->next;
    }
    return cnt;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    Node *current = NULL;
    Node *previous = NULL;

    if (*head == NULL) {
        return;
    }

    current = (*head)->next;
    previous = (*head);

    while (current != NULL) {
        Node *next = current->next;


        previous = current;
        current = current->next;
    }
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);

    int retval = pop(&test_list);
    push(&test_list, retval+10);

    remove_by_value(&test_list, 3);
    remove_by_value(&test_list, 7);

    reverse(&test_list);

    print_list(test_list);
}
