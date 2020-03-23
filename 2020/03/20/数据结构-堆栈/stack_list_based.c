#include <malloc.h>
#define ElementType int
#define MaxSize ;

typedef struct stack
{
    ElementType data;
    Stack *next;
} Stack;

Stack *createEmpty();                      //生成空栈
int isFull(Stack *stack);                  //查询是否满栈
int isEmpty(Stack *stack);                 //查询是否空栈
void push(Stack *stack, ElementType item); //在栈顶插入元素
ElementType pop(Stack *stack);             //删除并返回栈顶元素

Stack *createEmpty()
{
    Stack *top = (Stack *)malloc(sizeof(Stack));
    top->next = NULL;
    return top;
}

int isEmpty(Stack *stack)
{
    return stack->next == NULL;
}

void push(Stack *stack, ElementType item)
{
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    temp->data = item;
    temp->next = stack->next;
    stack->next = temp;
}

ElementType pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        return; //error!Empty stack
    }
    ElementType targetValue = stack->next->data;
    Stack *target = stack->next;
    stack->next = target->next;
    free(target);
    return targetValue;
}