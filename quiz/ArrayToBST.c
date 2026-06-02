/*
 * File: array_to_bst.c
 *
 * Description:
 * This program reads integers from a file. The first integer
 * specifies how many values follow. These values are stored in
 * an array and then inserted into a Binary Search Tree (BST).
 *
 * The tree is then traversed using inorder traversal and the
 * values are printed in sorted order.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------------- Binary Tree Node ---------------- */

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

/* Create new node */
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert into BST */
Node* insert(Node* root, int value) {

    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else
        root->right = insert(root->right, value);

    return root;
}

/* Inorder traversal (Left → Root → Right) */
void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

/* Free tree memory */
void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {

    FILE* file;
    int size;

    file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("Error: cannot open file.\n");
        return 1;
    }

    /* Read number of elements */
    fscanf(file, "%d", &size);

    /* Create array */
    int* data = (int*)malloc(size * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Read values into array */
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &data[i]);
    }

    fclose(file);

    /* Build BST */
    Node* root = NULL;

    for (int i = 0; i < size; i++) {
        root = insert(root, data[i]);
    }

    /* Print inorder traversal */
    printf("Inorder Traversal (Sorted Output):\n");
    inorder(root);
    printf("\n");

    /* Cleanup */
    freeTree(root);
    free(data);

    return 0;
}