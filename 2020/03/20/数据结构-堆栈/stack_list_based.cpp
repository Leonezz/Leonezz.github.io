#include <malloc.h>
#include <iostream>
#define ElementType int
#define MaxSize ;

struct Stack
{
    ElementType data;
    Stack *next;
};

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
        return -1; //error!Empty stack
    }
    ElementType targetValue = stack->next->data;
    Stack *target = stack->next;
    stack->next = target->next;
    free(target);
    return targetValue;
}

typedef int Vertex;

void getPath(Stack *stack, Vertex **path, Vertex start, Vertex end)
{
    Vertex v = end;
    while (v != -1)
    {
        push(stack, v);
        end = path[start][end];
        v = path[start][end];
    }
}

int main()
{
    std::cout << "sdas" << std::endl;
    Vertex **path = (Vertex **)malloc(25 * sizeof(Vertex));
    path = {};
    Stack *stack = createEmpty();
    getPath(stack, path, 1, 5);
    while (!isEmpty(stack))
    {
        std::cout << pop(stack) << std::endl;
    }
}