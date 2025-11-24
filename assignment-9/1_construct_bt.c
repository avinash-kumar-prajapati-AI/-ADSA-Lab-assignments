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

Node *queue[100];
int front = 0, rear = 0;

void enqueue(Node *n) { queue[rear++] = n; }
Node *dequeue() { return queue[front++]; }
int isEmpty() { return front == rear; }

Node *constructTree()
{
    int data;
    printf("Enter root (-1 for no node): ");
    scanf("%d", &data);
    if (data == -1)
        return NULL;

    Node *root = newNode(data);
    enqueue(root);

    while (!isEmpty())
    {
        Node *curr = dequeue();

        printf("Left of %d: ", curr->data);
        scanf("%d", &data);
        if (data != -1)
        {
            curr->left = newNode(data);
            enqueue(curr->left);
        }

        printf("Right of %d: ", curr->data);
        scanf("%d", &data);
        if (data != -1)
        {
            curr->right = newNode(data);
            enqueue(curr->right);
        }
    }
    return root;
}

void preorder(Node *root)
{
    if (!root)
        return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(Node *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main()
{
    Node *root = constructTree();

    printf("\nPreorder: ");
    preorder(root);
    printf("\nInorder: ");
    inorder(root);
    printf("\nPostorder: ");
    postorder(root);

    return 0;
}
