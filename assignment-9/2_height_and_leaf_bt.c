// 2. Given a binary tree, write functions to compute:
// a) Height of the tree
// b) Total number of leaf nodes
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

// Create node
Node *newNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

// Height of tree
int height(Node *root)
{
    if (!root)
        return 0;
    int l = height(root->left), r = height(root->right);
    return (l > r ? l : r) + 1;
}

// Count leaf nodes
int leafCount(Node *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return leafCount(root->left) + leafCount(root->right);
}

int main()
{
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Height of the tree: %d\n", height(root));
    printf("Total number of leaf nodes: %d\n", leafCount(root));

    return 0;
}
