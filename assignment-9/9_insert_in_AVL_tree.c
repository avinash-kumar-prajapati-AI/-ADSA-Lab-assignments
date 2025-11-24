// 9. Implement AVL Tree insertion, after each insertion display:
// A) Balance Factor
// B) Rotation Performed

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

Node *insert(Node *node, int data)
{
    if (!node)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int bf = balance(node);

    printf("Node %d: Balance Factor = %d\n", node->data, bf);

    if (bf > 1 && data < node->left->data)
    {
        printf("Right Rotation on %d\n", node->data);
        return rightRotate(node);
    }
    if (bf < -1 && data > node->right->data)
    {
        printf("Left Rotation on %d\n", node->data);
        return leftRotate(node);
    }
    if (bf > 1 && data > node->left->data)
    {
        printf("Left Rotation on %d, Right Rotation on %d\n", node->left->data, node->data);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && data < node->right->data)
    {
        printf("Right Rotation on %d, Left Rotation on %d\n", node->right->data, node->data);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
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
