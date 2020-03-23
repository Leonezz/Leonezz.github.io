#include <malloc.h>
#define ElementType int
typedef struct queueNode
{
    ElementType data;
    QueueNode *next;
} QueueNode;

typedef struct queue_list_based
{
    QueueNode *front;
    QueueNode *rear;
} Queue;
Queue *createQueue();                     //生成队列
int isFull(Queue *queue);                 //查询队列是否为满队列
void add(Queue *queue, ElementType item); //入队
int isEmpty(Queue *queue);                //查询队列是否为空
ElementType delete (Queue *queue);        //出队

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue)
{
    return queue->front == NULL;
}

void add(Queue *queue, ElementType item)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = item;
    node->next = NULL;
    if (isEmpty(queue))
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}

ElementType delete (Queue *queue)
{
    if (isEmpty(queue))
    {
        return NULL; //Error!queue is Empty
    }
    QueueNode *frontNode = queue->front;
    if (queue->front == queue->rear)
    { //if queue has just one element,make it empty.
        queue->front = NULL;
        queue->rear = NULL;
    }
    else
    {
        queue->front = queue->front->next;
    }
    ElementType frontNodeValue = frontNode->data;
    free(frontNode);
    return frontNodeValue;
}