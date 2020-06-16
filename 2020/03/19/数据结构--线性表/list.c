#include <malloc.h>
#define ElementType int

List *makeEmptyList();                                         //创建空表
List *findKth(const int K, List *list);                        //找到第K个元素
int find(const ElementType ele, List *list);                   //找到元素ele第一次出现的位置
List *insert(ElementType ele, const int position, List *list); //把元素ele插入position位置的前面
List *delete (const int position, List *list);                 //删除位置position处的元素
int length(List *list);                                        //返回线性表的长度

typedef struct list
{
    ElementType val;
    List *next;
} List;

List *makeEmptyList()
{
    List *list = (List *)malloc(sizeof(List));
    return list;
}

List *findKth(const int K, List *list)
{
    List *listCopy = list; //make a copy
    int i = 0;
    while (listCopy && i < K)
    {
        i++;
        listCopy = listCopy->next;
    }
    return listCopy;
}

int find(const ElementType ele, List *list)
{
    List *listCopy = list;
    while (listCopy && listCopy->val != ele)
    {
        listCopy = listCopy->next;
    }
    return listCopy;
}

List *insert(ElementType ele, const int position, List *list)
{
    if (position == 1)
    {
        List *n = makeEmptyList();
        n->val = ele;
        n->next = list;
        return n;
    }
    List *target = findKth(position - 1, list);
    if (target == NULL)
    {
        return NULL; //error
    }
    List *n = makeEmptyList();
    n->val = ele;
    n->next = target->next;
    target->next = n;
    return list;
}

List *delete (const int position, List *list)
{
    if (position == 1)
    {
        if (list == NULL)
            return NULL;
        else
        {
            List *copy = list;
            list = list->next;
            free(copy);
            return list;
        }
    }
    List *target = findKth(position - 1, list);
    List *lastNode = target;
    if (target == NULL)
    {
        return;
    }
    else if (target->next == NULL)
    {
        return;
    }

    target = target->next;
    lastNode->next = target->next;
    free(target);
    return list;
}

int length(List *list)
{
    int i = 0;
    List *listCopy = list;
    while (listCopy)
    {
        listCopy = listCopy->next;
        i++;
    }
    return i;
}