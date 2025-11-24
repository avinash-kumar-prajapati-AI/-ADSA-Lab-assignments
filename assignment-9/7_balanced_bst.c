// 7. Given a sorted array, build a balanced BST using divide-and-conquer.
// Print level - order traversal of the new tree.
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

// Build balanced BST
Node *buildBST(int arr[], int l, int r)
{
    if (l > r)
        return NULL;
    int m = (l + r) / 2;
    Node *root = newNode(arr[m]);
    root->left = buildBST(arr, l, m - 1);
    root->right = buildBST(arr, m + 1, r);
    return root;
}

// Level order traversal
void levelOrder(Node *root)
{
    if (!root)
        return;

    Node *q[100];
    int f = 0, r = 0;
    q[r++] = root;

    while (f < r)
    {
        Node *curr = q[f++];
        printf("%d ", curr->data);
        if (curr->left)
            q[r++] = curr->left;
        if (curr->right)
            q[r++] = curr->right;
    }
}

int main()
{
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    Node *root = buildBST(arr, 0, n - 1);

    printf("Level-order traversal: ");
    levelOrder(root);
    printf("\n");

    free(arr);
    return 0;
}
