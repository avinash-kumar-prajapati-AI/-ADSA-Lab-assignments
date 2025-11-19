// 10. Write a program to implement AVL tree deletion, after each deletion print:
// A) Type of Rotation
// B) Height of the tree
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
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
struct Node *deleteNode(struct Node *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            struct Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    printf("Node %d: Balance Factor = %d\n", root->data, balance);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        printf("Right Rotation on %d\n", root->data);
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        printf("Left Rotation on %d and Right Rotation on %d\n", root->left->data, root->data);
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        printf("Left Rotation on %d\n", root->data);
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        printf("Right Rotation on %d and Left Rotation on %d\n", root->right->data, root->data);
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
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

    printf("Enter the number of nodes to delete: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter value for node to delete %d: ", i + 1);
        scanf("%d", &data);
        root = deleteNode(root, data);
        printf("Inorder Traversal after deletion: ");
        inorderTraversal(root);
        printf("\n");
        printf("Height of the tree after deletion: %d\n", height(root));
    }

    return 0;
}
