#include <malloc.h>
#define KeyType int
typedef struct maxheap
{
    KeyType *data; //堆的数据
    int size;      //当前元素个数
    int capacity;  //堆的最大容量
} MaxHeap;

MaxHeap *createHeap(const int maxSize);        //创建空堆，最大空间为maxSize
int isFull(MaxHeap *heap);                     //判断堆是否已满
int isEmpty(MaxHeap *heap);                    //判断堆是否为空
void insert(MaxHeap *heap, const KeyType key); //把元素key插入堆
KeyType deleteMax(MaxHeap *heap);              //删除并返回堆中的最大值

MaxHeap *createHeap(const int maxSize)
{
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->data = (KeyType *)malloc(sizeof(KeyType) * (maxSize + 1));
    heap->capacity = maxSize + 1;
    heap->size = 1;
    return heap;
}

void insert(MaxHeap *heap, KeyType key)
{
    if (heap == NULL)
        return; //if heap is NULL,do nothing
    else if (isFull(heap))
        return;                  //if heap is full,do nothing
    int position = ++heap->size; //insert position should be 1 after size
    //when break out loop,heap->data[position]>key && position is the right position
    for (; heap->data[position] < key; position /= 2)
    { //in loop,heap->data[position]>key,move data down
        heap->data[position] = heap->data[position / 2];
    }
    heap->data[position] = key; //insert key to the right pos
}

KeyType deleteMax(MaxHeap *heap)
{
    if (heap == NULL)
        return;
    else if (isEmpty(heap))
        return;
    KeyType target = heap->data[1];
    KeyType temp = heap->data[heap->size--];
    int parent = 1;
    int child = 0;
    for (; parent * 2 <= heap->size; parent = child)
    {
        child = parent * 2; //left child index,may overflow
        if (child <= heap->size && heap->data[child] < heap->data[child + 1])
        { //if right child is bigger,turn to right child
            child++;
        }
        if (heap->data[child] < temp)
            break; //if order is corrict,break
        else       //replace nodes
            heap->data[parent] = heap->data[child];
    }
    heap->data[parent] = temp; //put temp to right position
    return target;
}

KeyType deleteMax(MaxHeap *heap)
{
    if (heap == NULL)
        return;
    else if (isEmpty(heap))
        return;
    KeyType target = heap->data[1];
    heap->data[1] = heap->data[heap->size--];
    int child = 0;
    for (int i = 1; i * 2 < heap->size; i = child)
    {
        child = i * 2;
        if (heap->data[child] < heap->data[child + 1])
            child++;
        if (heap->data[i] < heap->data[child])
            swap(&heap->data[i], &heap->data[child]);
        else
            break;
    }
}