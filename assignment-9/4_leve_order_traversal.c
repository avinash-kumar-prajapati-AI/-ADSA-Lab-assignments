// 4. Perform level-order (breadth-first) traversal of a binary tree using a queue.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left, *right;
} Node;

// Create node
Node *newNode(int data)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

// Simple array-based queue
Node *queue[100];
int front = 0, rear = 0;

void enqueue(Node *n) { queue[rear++] = n; }
Node *dequeue() { return queue[front++]; }
int isEmpty() { return front == rear; }

// Level-order traversal
void levelOrder(Node *root)
{
    if (!root)
        return;

    enqueue(root);
    while (!isEmpty())
    {
        Node *curr = dequeue();
        printf("%d ", curr->data);

        if (curr->left)
            enqueue(curr->left);
        if (curr->right)
            enqueue(curr->right);
    }
}

int main()
{
    Node *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Level-order traversal: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
