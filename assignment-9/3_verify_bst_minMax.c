// 3. Given any binary tree, write a program to verify whether it satisfies BST properties using the min–max recursive method.
#include <stdio.h>
#include <stdlib.h>
int INT_MIN = -2147483648;
int INT_MAX = 2147483647;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int isBSTUtil(struct Node *node, int min, int max)
{
    if (node == NULL)
        return 1;
    if (node->data < min || node->data > max)
        return 0;
    return isBSTUtil(node->left, min, node->data - 1) &&
           isBSTUtil(node->right, node->data + 1, max);
}
int isBST(struct Node *root)
{
    return isBSTUtil(root, INT_MIN, INT_MAX);
}
int main()
{
    struct Node *root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->right = createNode(18);

    if (isBST(root))
        printf("The binary tree is a BST.\n");
    else
        printf("The binary tree is not a BST.\n");

    return 0;
}