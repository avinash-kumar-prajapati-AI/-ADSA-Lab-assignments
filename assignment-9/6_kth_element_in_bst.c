// 6. Given a BST, write functions to find:
// A) k-th smallest element
// B) k-th largest element
// (Without storing traversal in an array)
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

// k-th Smallest
void kthSmallestUtil(Node *root, int k, int *c, int *res)
{
    if (!root || *c >= k)
        return;
    kthSmallestUtil(root->left, k, c, res);
    if (++(*c) == k)
        *res = root->data;
    kthSmallestUtil(root->right, k, c, res);
}

int kthSmallest(Node *root, int k)
{
    int count = 0, result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

// k-th Largest
void kthLargestUtil(Node *root, int k, int *c, int *res)
{
    if (!root || *c >= k)
        return;
    kthLargestUtil(root->right, k, c, res);
    if (++(*c) == k)
        *res = root->data;
    kthLargestUtil(root->left, k, c, res);
}

int kthLargest(Node *root, int k)
{
    int count = 0, result = -1;
    kthLargestUtil(root, k, &count, &result);
    return result;
}

int main()
{
    Node *root = NULL;
    int n, data, k;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    while (n--)
    {
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Enter k: ");
    scanf("%d", &k);

    printf("%d-th smallest: %d\n", k, kthSmallest(root, k));
    printf("%d-th largest: %d\n", k, kthLargest(root, k));

    return 0;
}
