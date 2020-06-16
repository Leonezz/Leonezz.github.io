#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//定义一个哈夫曼节点，它是个结构体
struct haffNode
{
    int weight;                                            //权重，就是这个字符出现的个数；如果这个节点是个父节点的话 ，就是两个子节点权重的和
    char data;                                             //这个用来存字符本身，比如字符是'c'，data='c';
    struct haffNode *leftChild = NULL, *rightChild = NULL; //定义左右子节点指针
};
char code[256][50];         //用二维数组来储存字符的哈夫曼编码，其中第一维的下标表示的是这个字符的ASCII码
haffNode left[50];          //用来储存所有的左子节点
haffNode right[50];         //用来储存所有的右子节点
unsigned char saveChar = 0; //用来保存二进制文件，因为char类型是1个字节，所以每8位储存一次 ,而且用unsigned无符号型，避免符号位干扰
unsigned char slidChar;     //定义一个字符备用，以应对可能需要的操作
//排序函数,第一个参数是哈夫曼的节点数组，第二个是数组的长度，这里用冒泡排序
void sort(haffNode *node, int length)
{
    int i, j;
    haffNode t;
    for (i = 0; i < length - 1; i++)
    {
        for (j = i + 1; j < length - i - 1; j++)
        {
            if (node[j].weight < node[j + 1].weight)
            {
                t = node[j];
                node[j] = node[j + 1];
                node[j + 1] = t;
            }
        }
    }
}
//构建哈夫曼树
void creatHaffman(haffNode *node, int length)
{
    if (length == 1)
    {
        return; //如果数组长度为1，则结束递归，下面的就不再执行
    }
    sort(node, length);                                                //将node数组按照weight从大到小排序
    haffNode parent;                                                   //生成父节点，因为我们的数组从大到小排序过了，所以数组最后面的就是最小的节点
    left[length] = node[length - 2], right[length] = node[length - 1]; //定义子字节，用来存数组最后的两个节点
    parent.weight = left[length].weight + right[length].weight;        //父节点的权重等于两个子节点的 权重
    //储存两个子节点,因为parent.leftChild是指针类型，所以赋值的时候要加&
    parent.leftChild = &left[length];
    parent.rightChild = &right[length];
    //将数组最后两个子节点剔除，换成父节点，然后递归创建接下来的部分
    node[length - 2] = parent;
    creatHaffman(node, length - 1);
}
//计算字符的哈夫曼编码 ,第一个参数是哈夫曼树根节点，第二个参数储存编码的字符数组，第三个参数是字符数组的长度，从0开始
void coding(haffNode *node, char *keepCode, int length)
{
    //如果节点没有子节点，就说明它是叶节点，将编码存在code数组里
    if (node->leftChild == NULL || node->rightChild == NULL)
    {
        keepCode[length] = '\0';                //给编码一个终止符，形成一个完整的字符串，方便拷贝，以防拷贝到之前的编码。
        strcpy(code[node->data - '0'], keepCode); //调用strcpy函数拷贝字符串，其中code的下标用节点的字符(data)-0得到
        return;
    }
    keepCode[length] = '0';
    coding(node->leftChild, keepCode, length + 1);
    keepCode[length] = '1';
    coding(node->rightChild, keepCode, length + 1);
}

void visitTreeNode(BTreeNode* node)
{
    printf("char:%c\n",node->data);
    printf("weight:%d\n",node->weight);
}

void preOrderTrav(BTreeNode* root)
{
    if(root==NULL)return;
    visitTreeNode(root);
    preOrderTrav(root->left);
    preOrderTrav(root->right);
}

void inOrder(BTreeNode* root)
{
    if(root==NULL)return;
    inOrder(root->left);
    visitTreeNode(root);
    inOrder(root->right);
}

void postOrderTraversal(BTreeNode *tree)
{
    BTreeNode *t = tree;
    Stack *stack = createEmpty();
    BTreeNode *tCopy = (BTreeNode *)malloc(sizeof(BTreeNode));
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
                visit(tCopy);
            }
        }
    }
    free(tCopy);
}

int main()
{
    int cnt[128] = {0};
    char words[1024];
    printf("input the words:");
    scanf("%s", words);
    for (; *words != '\0'; ++words)
        cnt[*words - '0']++;
    haffNode node[128];
    int nodeNum = 0;
    for (int i = 0; i < 128; ++i)
    {
        if (cnt[i] == 0)
            continue;
        node[nodeNum].data = i;
        node[nodeNum].weight = cnt[i];
        nodeNum++;
    }

    creatHaffman(node,nodeNum);
    char tempCode[50];
    coding(&node[0],tempCode,0);
    
}