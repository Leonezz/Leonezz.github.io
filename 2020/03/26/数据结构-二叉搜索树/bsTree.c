#include <malloc.h>
#define KeyType int
#define NULL (void *)0
typedef struct bsTree
{
    KeyType key;
    BinarySearchTree *left;
    BinarySearchTree *right;
} BinarySearchTree;
//从二叉搜索树中找出键值为key的节点地址
BinarySearchTree *find(BinarySearchTree *tree, KeyType key);
//找出二叉搜索树的最小键值节点
BinarySearchTree *findMin(BinarySearchTree *tree);
//找出二叉搜索树的最大键值节点
BinarySearchTree *findMax(BinarySearchTree *tree);
//向二叉搜索树插入键值为key的节点
BinarySearchTree *insert(BinarySearchTree *tree, KeyType key);
//从二叉搜索树删除键值为key的节点
BinarySearchTree *delete (BinarySearchTree *tree, KeyType key);

BinarySearchTree *find(BinarySearchTree *tree, KeyType key)
{
    if (tree == NULL)
        return NULL;
    BinarySearchTree *temp = tree;
    while (temp)
    {
        if (key > temp->key)
            temp = temp->right;
        else if (key < temp->key)
            temp = temp->left;
        else
            return temp;
    }
}

BinarySearchTree *findMin(BinarySearchTree *tree)
{
    if (tree == NULL)
        return NULL;
    BinarySearchTree *temp = tree;
    while (temp->left)
    {
        temp = temp->left;
    }
    return temp;
}

BinarySearchTree *insert(BinarySearchTree *tree, KeyType key)
{
    BinarySearchTree *temp = tree;
    while (temp)
    {
        if (key > temp->key)
            temp = temp->right;
        else if (key < temp->key)
            temp = temp->left;
        else
            break; //if equals,I dont know what's right,lets just rewrite it.
    }
    //when break out while loop,temp must be NULL
    temp = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
    temp->key = key;
    temp->left = temp->right = NULL;
    return tree;
}

BinarySearchTree *delete (BinarySearchTree *tree, KeyType *key)
{
    BinarySearchTree *target = find(tree, key);
    if (target == NULL)
        return NULL;
    if (target->left && target->right)
    {                                              //both left child and right child are valid
        KeyType min = findMin(target->right)->key; //or findMax(target->left)
        target->key = min;
        return delete (target->right, min);
    }
    else
    {
        BinarySearchTree *temp = target; //copy target address,it need to be freed
        if (target->left != NULL)
        { //only left child
            target = target->left;
        }
        else if (target->right != NULL)
        { //only right child
            target = target->right;
        }
        //else no child,just free the node will be fine
        free(temp);
        return tree;
    }
}