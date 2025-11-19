// 6. Given a BST, write functions to find:
// A) k-th smallest element
// B) k-th largest element
// (Without storing traversal in an array)
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

struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }
    return root;
}

void kthSmallestUtil(struct Node *root, int k, int *count, int *result)
{
    if (root == NULL || *count >= k)
    {
        return;
    }
    kthSmallestUtil(root->left, k, count, result);
    (*count)++;
    if (*count == k)
    {
        *result = root->data;
        return;
    }
    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(struct Node *root, int k)
{
    int count = 0;
    int result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

void kthLargestUtil(struct Node *root, int k, int *count, int *result)
{
    if (root == NULL || *count >= k)
    {
        return;
    }
    kthLargestUtil(root->right, k, count, result);
    (*count)++;
    if (*count == k)
    {
        *result = root->data;
        return;
    }
    kthLargestUtil(root->left, k, count, result);
}

int kthLargest(struct Node *root, int k)
{
    int count = 0;
    int result = -1;
    kthLargestUtil(root, k, &count, &result);
    return result;
}

int main()
{
    struct Node *root = NULL;
    int n, data, k;

    printf("Enter the number of nodes to insert: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    int kth_smallest = kthSmallest(root, k);
    if (kth_smallest != -1)
        printf("The %d-th smallest element is: %d\n", k, kth_smallest);
    else
        printf("The tree has less than %d elements.\n", k);

    int kth_largest = kthLargest(root, k);
    if (kth_largest != -1)
        printf("The %d-th largest element is: %d\n", k, kth_largest);
    else
        printf("The tree has less than %d elements.\n", k);

    return 0;
}