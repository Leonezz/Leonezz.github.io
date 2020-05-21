#include"queue.h"
Queue *createQueue(const int maxSize)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isFull(Queue *queue, const int maxSize)
{
    return ((queue->front + 1) % maxSize) == (queue->rear);
}

int isEmpty(Queue *queue)
{
    return queue->front == queue->rear;
}

void addQ(Queue *queue, ElementType item, const int maxSize)
{
    if (isFull(queue, maxSize))
    {
        return; //Error!queue is Full.
    }
    queue->rear = (queue->rear + 1) % maxSize;
    queue->data[queue->rear] = item;
}

ElementType deleteQ (Queue *queue, const int maxSize)
{
    if (isEmpty(queue))
    {
        return NULL; //Error!queue is Empty.
    }
    queue->front = (queue->front + 1) % maxSize;
    return queue->data[queue->front];
}