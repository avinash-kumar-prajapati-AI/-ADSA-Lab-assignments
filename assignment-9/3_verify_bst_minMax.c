// 3. Given any binary tree, write a program to verify whether it satisfies BST properties using the min–max recursive method.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

Node *newNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

int isBSTUtil(Node *root, int min, int max)
{
    if (!root)
        return 1;
    if (root->data < min || root->data > max)
        return 0;
    return isBSTUtil(root->left, min, root->data - 1) &&
           isBSTUtil(root->right, root->data + 1, max);
}

int isBST(Node *root)
{
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

int main()
{
    Node *root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->right = newNode(18);

    printf("The binary tree is %sa BST.\n", isBST(root) ? "" : "not ");
    return 0;
}
