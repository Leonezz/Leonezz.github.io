#ifndef QUEUE_H
#define QUEUE_H

#include <malloc.h>
#define ElementType int
typedef struct queue_array_based
{
    ElementType *data;
    int front;
    int rear;
} Queue;

Queue *createQueue(const int maxSize);                       //生成队列
int isFull(Queue *queue, const int maxSize);                 //查询队列是否为满队列
void addQ(Queue *queue, ElementType item, const int maxSize); //入队
int isEmpty(Queue *queue);                                   //查询队列是否为空
ElementType deleteQ (Queue *queue, const int maxSize);        //出队

#endif