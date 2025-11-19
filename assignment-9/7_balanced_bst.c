// 7. Given a sorted array, build a balanced BST using divide-and-conquer.
// Print level - order traversal of the new tree.
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

struct Node *sortedArrayToBST(int arr[], int start, int end)
{
    if (start > end)
    {
        return NULL;
    }
    int mid = start + (end - start) / 2;
    struct Node *node = createNode(arr[mid]);
    node->left = sortedArrayToBST(arr, start, mid - 1);
    node->right = sortedArrayToBST(arr, mid + 1, end);
    return node;
}

void levelOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    struct Node **queue = (struct Node **)malloc(100 * sizeof(struct Node *));
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        struct Node *current = queue[front++];
        printf("%d ", current->data);
        if (current->left)
        {
            queue[rear++] = current->left;
        }
        if (current->right)
        {
            queue[rear++] = current->right;
        }
    }
    free(queue);
}

int main()
{
    int n;
    printf("Enter the number of elements in the sorted array: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter the elements of the sorted array:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    struct Node *root = sortedArrayToBST(arr, 0, n - 1);
    printf("Level-order traversal of the balanced BST: ");
    levelOrderTraversal(root);
    printf("\n");
    free(arr);
    return 0;
}