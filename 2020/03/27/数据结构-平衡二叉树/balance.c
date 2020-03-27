#include <malloc.h>
#define KeyType int
#define NULL (void *)0
typedef struct AVLTreeNode
{
    KeyType key;
    AVLTree *left;
    AVLTree *right;
    int height;
} AVLTree;

int maxOfTwo(int one, int theother)
{
    return one > theother ? one : theother;
}

AVLTree *singleRightRotation(AVLTree *tree)
{                                    //tree is the finder
    AVLTree *replacer = tree->right; //right child of finder
    tree->right = replacer->left;    //right child's left child to finder's right child
    replacer->left = tree;           //finder to right child's left child
    //update heights of changed nodes
    replacer->height = maxOfTwo(replacer->left->height, replacer->right->height) + 1;
    tree->height = maxOfTwo(tree->left->height, tree->right->height) + 1;
    return replacer;
}

AVLTree *singleLeftRotation(AVLTree *tree)
{
    AVLTree *replacer = tree->left;
    tree->left = replacer->right;
    replacer->right = tree;
    //update heights of changed nodes
    replacer->height = maxOfTwo(replacer->left->height, replacer->right->height) + 1;
    tree->height = maxOfTwo(tree->left->height, tree->right->height) + 1;
    return replacer;
}

AVLTree *rightLeftRotation(AVLTree *tree)
{
    tree->right = singleRightRotation(tree->right);
    return singleLeftRotation(tree);
}

AVLTree *leftRightRotation(AVLTree *tree)
{
    tree->left = singleLeftRotation(tree->left);
    return singleRightRotation(tree);
}

int getHeight(AVLTree *tree)
{
    if (tree = NULL)
        return 0;
    return maxOfTwo(getHeight(tree->left), getHeight(tree->right)) + 1;
}

AVLTree *insert(AVLTree *tree, KeyType key)
{
    if (tree == NULL)
    {
        tree = (AVLTree *)malloc(sizeof(AVLTree));
        tree->key = key;
        tree->left = tree->right = NULL;
    }
    else if (key < tree->key)
    { //insert left sub tree
        tree->left = insert(tree->left, key);
        if (getHeight(tree->left) - getHeight(tree->right) == 2)
        { //balance broken
            if (key < tree->key)
            { //single left rotation
                tree = singleLeftRotation(tree);
            }
            else
            { //signle left right rotation
                tree = leftRightRotation(tree);
            }
        }
        else if (key > tree->key)
        {
            tree->right = insert(tree->right, key);
            if (getHeight(tree->right) - getHeight(tree->left) == 2)
            { //balance broken
                if (key > tree->key)
                { //single right rotation
                    tree = singleRightRotation(tree);
                }
                else
                { //right left rotation
                    tree = rightLeftRotation(tree);
                }
            }
        }
    }
    tree->height = maxOfTwo(getHeight(tree->left), getHeight(tree->right)) + 1; //update height
    return tree;
}