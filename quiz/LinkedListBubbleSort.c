/*
 * File: linked_list_bubble_sort.c
 *
 * Description:
 * This program creates a singly linked list of 100 randomly
 * generated integers. It then sorts the list using bubble sort
 * by comparing and swapping adjacent node values.
 *
 * Finally, the sorted list is printed in rows of 5.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Linked List Node ---------- */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* Create a new node */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

/* Insert at end */
void insert(Node** head, int value) {
    Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

/* Print list in rows of 5 */
void printList(Node* head) {
    int count = 0;

    while (head != NULL) {
        printf("%5d ", head->data);
        count++;

        if (count % 5 == 0)
            printf("\n");

        head = head->next;
    }

    printf("\n");
}

/* Bubble sort on linked list (swap data only) */
void bubbleSort(Node* head) {

    if (head == NULL) return;

    int swapped;
    Node* ptr;
    Node* last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {

            if (ptr->data > ptr->next->data) {

                /* swap values */
                int temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;

                swapped = 1;
            }

            ptr = ptr->next;
        }

        last = ptr;

    } while (swapped);
}

/* Free memory */
void freeList(Node* head) {
    Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* ---------- Main ---------- */
int main() {

    Node* head = NULL;

    srand(time(NULL));

    /* Generate 100 random integers */
    for (int i = 0; i < 100; i++) {
        int value = rand() % 1000;  /* range 0–999 */
        insert(&head, value);
    }

    printf("Original List:\n");
    printList(head);

    /* Sort the list */
    bubbleSort(head);

    printf("\nSorted List:\n");
    printList(head);

    freeList(head);

    return 0;
}