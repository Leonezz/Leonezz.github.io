#include <malloc.h>
#define ElementType int

typedef struct treeNode
{
    ElementType data;
    BinaryTree *left;
    BinaryTree *right;
} BinaryTree;

void visit(BinaryTree *tree); //访问节点

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

void preOrderTraversal(BinaryTree *tree)
{
    BinaryTree *t = tree; //make a copy
    Stack *stack = createEmpty();
    while (t || !isEmpty(stack))
    { //if t==null && stack is empty,exit
        while (t)
        { //push left nodes
            push(stack, t);
            visit(t); //visit root and left nodes first
            t = t->left;
        }
        if (!isEmpty(stack))
        {
            t = pop(stack);
            t = t->right; //turn to right
            visit(t);     //visit right node
        }
    }
}

void inOrderTraversal(BinaryTree *tree)
{
    BinaryTree *t = tree;
    Stack *stack = createEmpty();
    while (t || !isEmpty(stack))
    {
        while (t)
        {
            push(stack, t);
            t = t->left;
        }
        if (!isEmpty(stack))
        {
            t = pop(stack);
            visit(t);
            t = t->right;
        }
    }
}

void postOrderTraversal(BinaryTree *tree)
{
    BinaryTree *t = tree;
    Stack *stack = createEmpty();
    BinaryTree *tCopy = (BinaryTree *)malloc(sizeof(BinaryTree));
    while (t || !isEmpty(stack))
    {
        while (t)
        {
            push(stack, t);
            t = t->left;
        }
        if (!isEmpty(stack))
        {
            t = pop(stack);
            tCopy->data = t->data;
            t = t->right; //turn to right
            if (t)
            { 
                tCopy->left = tCopy->right = NULL;
                push(stack, tCopy); //temp will be visited after right sub tree
            }
            else
            {
                visit(t);
            }
        }
    }
    free(tCopy);
}