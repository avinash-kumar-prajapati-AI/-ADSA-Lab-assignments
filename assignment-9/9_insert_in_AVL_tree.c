// 9. Implement AVL Tree insertion, after each insertion display:
// A) Balance Factor
// B) Rotation Performed

#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node *insert(struct Node *node, int data)
{
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    printf("Node %d: Balance Factor = %d\n", node->data, balance);

    // Left Left Case
    if (balance > 1 && data < node->left->data)
    {
        printf("Right Rotation on %d\n", node->data);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && data > node->right->data)
    {
        printf("Left Rotation on %d\n", node->data);
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        printf("Left Rotation on %d and Right Rotation on %d\n", node->left->data, node->data);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        printf("Right Rotation on %d and Left Rotation on %d\n", node->right->data, node->data);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
int main()
{
    struct Node *root = NULL;
    int n, data;

    printf("Enter the number of nodes to insert: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Inorder Traversal of the AVL Tree: ");
    inorderTraversal(root);
    printf("\n");
    return 0;
}