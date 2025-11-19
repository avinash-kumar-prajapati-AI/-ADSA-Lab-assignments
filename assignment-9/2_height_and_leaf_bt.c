// 2. Given a binary tree, write functions to compute:
// a) Height of the tree
// b) Total number of leaf nodes
#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
int countLeafNodes(struct Node *node)
{
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    return countLeafNodes(node->left) + countLeafNodes(node->right);
}
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int main()
{
    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);

    int treeHeight = height(root);
    int leafCount = countLeafNodes(root);

    printf("Height of the tree: %d\n", treeHeight);
    printf("Total number of leaf nodes: %d\n", leafCount);

    return 0;
}