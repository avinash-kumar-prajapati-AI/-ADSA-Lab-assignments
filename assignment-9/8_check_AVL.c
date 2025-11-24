// 8. Given a binary tree, write a program to check whether it is height-balanced (AVL property). Also print the balance factor of each node.

#include <stdio.h>
#include <stdlib.h>

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

int max(int a, int b) { return a > b ? a : b; }

int checkAVL(Node *root, int *ok)
{
    if (!root)
        return 0;

    int lh = checkAVL(root->left, ok);
    int rh = checkAVL(root->right, ok);

    int bf = lh - rh;
    printf("Node %d: Balance Factor = %d\n", root->data, bf);

    if (bf < -1 || bf > 1)
        *ok = 0;

    return 1 + max(lh, rh);
}

int isAVL(Node *root)
{
    int ok = 1;
    checkAVL(root, &ok);
    return ok;
}

int main()
{
    Node *root = newNode(30);
    root->left = newNode(20);
    root->right = newNode(40);
    root->left->left = newNode(10);
    root->left->right = newNode(25);
    root->right->right = newNode(50);

    printf("The tree is %sAVL.\n", isAVL(root) ? "" : "not ");
    return 0;
}
