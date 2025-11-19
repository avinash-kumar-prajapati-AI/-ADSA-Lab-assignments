// 1. Write a program to construct a binary tree using user input (level-order insertion).
// Perform preorder, inorder, and postorder traversals.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

struct QueueNode
{
    struct Node *treeNode;
    struct QueueNode *next;
};

struct Queue
{
    struct QueueNode *front;
    struct QueueNode *rear;
};
struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
bool isQueueEmpty(struct Queue *queue)
{
    return queue->front == NULL;
}
void enqueue(struct Queue *queue, struct Node *treeNode)
{
    struct QueueNode *newQueueNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;
    if (queue->rear)
    {
        queue->rear->next = newQueueNode;
    }
    queue->rear = newQueueNode;
    if (!queue->front)
    {
        queue->front = newQueueNode;
    }
}
struct Node *dequeue(struct Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        return NULL;
    }
    struct QueueNode *temp = queue->front;
    struct Node *treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (!queue->front)
    {
        queue->rear = NULL;
    }
    free(temp);
    return treeNode;
}
struct Node *constructBinaryTree()
{
    int data;
    printf("Enter root node data (-1 for no node): ");
    scanf("%d", &data);
    if (data == -1)
    {
        return NULL;
    }
    struct Node *root = createNode(data);
    struct Queue *queue = createQueue();
    enqueue(queue, root);
    while (!isQueueEmpty(queue))
    {
        struct Node *current = dequeue(queue);
        printf("Enter left child of %d (-1 for no node): ", current->data);
        scanf("%d", &data);
        if (data != -1)
        {
            current->left = createNode(data);
            enqueue(queue, current->left);
        }
        printf("Enter right child of %d (-1 for no node): ", current->data);
        scanf("%d", &data);
        if (data != -1)
        {
            current->right = createNode(data);
            enqueue(queue, current->right);
        }
    }
    free(queue);
    return root;
}
void preorderTraversal(struct Node *root)
{
    if (root)
    {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
void inorderTraversal(struct Node *root)
{
    if (root)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
void postorderTraversal(struct Node *root)
{
    if (root)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}
int main()
{
    struct Node *root = constructBinaryTree();
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\nInorder Traversal: ");
    inorderTraversal(root);
    printf("\nPostorder Traversal: ");
    postorderTraversal(root);
    printf("\n");
    return 0;
}