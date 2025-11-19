// 4. Perform level-order (breadth-first) traversal of a binary tree using a queue.
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

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

int isQueueEmpty(struct Queue *queue)
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

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void levelOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    struct Queue *queue = createQueue();
    enqueue(queue, root);
    while (!isQueueEmpty(queue))
    {
        struct Node *current = dequeue(queue);
        printf("%d ", current->data);
        if (current->left)
        {
            enqueue(queue, current->left);
        }
        if (current->right)
        {
            enqueue(queue, current->right);
        }
    }
    free(queue);
}

int main()
{
    struct Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->right = createNode(6);

    printf("Level-order traversal of the binary tree: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}