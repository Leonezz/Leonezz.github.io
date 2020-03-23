#define ElementType int
#include <malloc.h>

typedef struct stack
{
    ElementType *data;
    int top;
} Stack;

Stack *createEmpty(const int maxSize);     //生成空栈
int isFull(Stack *stack, int maxSize);     //查询是否满栈
int isEmpty(Stack *stack);                 //查询是否空栈
void push(Stack *stack, ElementType item); //在栈顶插入元素
ElementType pop(Stack *stack);             //删除并返回栈顶元素

Stack *createEmpty(const int maxSize)
{
    ElementType *data = (ElementType *)malloc(maxSize * sizeof(ElementType));
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = data;
    stack->top = -1; //means an Empty Stack
}

int isFull(Stack *stack, int maxSize)
{
    return stack->top >= maxSize;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, ElementType item, const int maxSize)
{
    if (isFull(stack, maxSize))
    {
        return; //Error!stack overflow
    }
    stack->data[stack->top++] = item;
}

ElementType pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        return NULL; //Error!stack is Empty
    }
    return stack->data[stack->top--];
}