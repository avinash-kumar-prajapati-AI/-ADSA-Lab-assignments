// 8. Given a binary tree, write a program to check whether it is height-balanced (AVL property). Also print the balance factor of each node.

#include <stdio.h>
#include <stdlib.h>

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

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int isAVLUtil(struct Node *node, int *isBalanced)
{
    if (node == NULL)
    {
        return 0;
    }

    int leftHeight = isAVLUtil(node->left, isBalanced);
    int rightHeight = isAVLUtil(node->right, isBalanced);

    int balanceFactor = leftHeight - rightHeight;
    printf("Node %d: Balance Factor = %d\n", node->data, balanceFactor);

    if (balanceFactor < -1 || balanceFactor > 1)
    {
        *isBalanced = 0;
    }

    return 1 + max(leftHeight, rightHeight);
}

int isAVL(struct Node *root)
{
    int isBalanced = 1;
    isAVLUtil(root, &isBalanced);
    return isBalanced;
}

int main()
{
    struct Node *root = createNode(30);
    root->left = createNode(20);
    root->right = createNode(40);
    root->left->left = createNode(10);
    root->left->right = createNode(25);
    root->right->right = createNode(50);

    if (isAVL(root))
    {
        printf("The tree is height-balanced (AVL).\n");
    }
    else
    {
        printf("The tree is not height-balanced (not AVL).\n");
    }

    return 0;
}