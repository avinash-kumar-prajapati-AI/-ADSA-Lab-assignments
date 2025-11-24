// 10. Write a program to implement AVL tree deletion, after each deletion print:
// A) Type of Rotation
// B) Height of the tree
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data, height;
    struct Node *left, *right;
} Node;

int max(int a, int b) { return a > b ? a : b; }
int height(Node *n) { return n ? n->height : 0; }

Node *newNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

int balance(Node *n)
{
    return n ? height(n->left) - height(n->right) : 0;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left, *t = x->right;
    x->right = y;
    y->left = t;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right, *t = y->left;
    y->left = x;
    x->right = t;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

/* AVL INSERT (needed for building tree) */
Node *insert(Node *root, int data)
{
    if (!root)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance(root);

    if (bf > 1 && data < root->left->data)
        return rightRotate(root);
    if (bf < -1 && data > root->right->data)
        return leftRotate(root);
    if (bf > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node *minNode(Node *n)
{
    while (n->left)
        n = n->left;
    return n;
}

/* AVL DELETE */
Node *deleteNode(Node *root, int data)
{
    if (!root)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        Node *temp = minNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int bf = balance(root);
    printf("Node %d: Balance Factor = %d\n", root->data, bf);

    if (bf > 1 && balance(root->left) >= 0)
    {
        printf("Right Rotation on %d\n", root->data);
        return rightRotate(root);
    }
    if (bf > 1 && balance(root->left) < 0)
    {
        printf("Left Rotation on %d and Right Rotation on %d\n",
               root->left->data, root->data);
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && balance(root->right) <= 0)
    {
        printf("Left Rotation on %d\n", root->data);
        return leftRotate(root);
    }
    if (bf < -1 && balance(root->right) > 0)
    {
        printf("Right Rotation on %d and Left Rotation on %d\n",
               root->right->data, root->data);
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
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

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Nodes to delete: ");
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &data);
        root = deleteNode(root, data);
        printf("Inorder: ");
        inorder(root);
        printf("\nTree Height: %d\n", height(root));
    }
    return 0;
}
