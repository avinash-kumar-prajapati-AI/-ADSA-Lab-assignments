// 5. Insert nodes into a Binary Search Tree (BST) and display its inorder traversal.
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

Node *insert(Node *root, int data)
{
    if (!root)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main()
{
    Node *root = NULL;
    int n, data;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    while (n--)
    {
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}
