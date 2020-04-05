#include <malloc.h>
#define MaxSize 100
typedef Vertex StackElementType;
typedef int DataType;
typedef int WeightType;
typedef struct graph
{
    int vertexCount;                       //顶点数
    int edgeCount;                         //边数
    WeightType graphMat[MaxSize][MaxSize]; //邻接矩阵，元素表示边的权重
    DataType data[MaxSize];                //节点数据
} Graph;

typedef int Vertex;
typedef struct edge
{
    Vertex start;      //起点
    Vertex end;        //终点
    WeightType weight; //权重
} Edge;

typedef struct stack
{
    StackElementType data;
    Stack *next;
} Stack;

Stack *createStack();                           //生成空栈
int isFull(Stack *stack);                       //查询是否满栈
int isEmpty(Stack *stack);                      //查询是否空栈
void push(Stack *stack, StackElementType item); //在栈顶插入元素
StackElementType pop(Stack *stack);             //删除并返回栈顶元素
typedef struct queueNode
{
    StackElementType data;
    QueueNode *next;
} QueueNode;

typedef struct queue_list_based
{
    QueueNode *front;
    QueueNode *rear;
} Queue;
Queue *createQueue();                          //生成队列
int isFull(Queue *queue);                      //查询队列是否为满队列
void add(Queue *queue, StackElementType item); //入队
int isEmpty(Queue *queue);                     //查询队列是否为空
StackElementType delete (Queue *queue);        //出队

Graph *create(int number);                                   //创建空图返回
Graph *insertVertex(Graph *graph, Vertex *vertex);           //将节点插入图
void insertEdge(Graph *graph, Edge *edge);                   //将边插入图
void depthFirstSearch(Graph *graph, Vertex *vertex);         //从顶点vertex出发深度优先遍历
void breadthFirstSearch(Graph *graph, Vertex *vertex);       //从顶点vertex出发宽度优先遍历
void shortestPath(Graph *graph, Vertex *vertex, int dist[]); //计算从节点vertex到任意节点的最短路径
void minSpanningTree(Graph *graph);                          //计算图的最小生成树
void visit(Vertex *vertex);

Graph *create(int vertexCnt)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = vertexCnt; //初始化顶点数
    graph->edgeCount = 0;           //初始化边数
    for (int i = 0; i < graph->vertexCount; ++i)
    {
        graph->data[i] = 0; //数据初始化，应该初始化为用户给定的数据
        for (int j = 0; j < graph->vertexCount; ++j)
        {
            graph->graphMat[i][j] = 0; //连接初始化
        }
    }
    return graph;
}

void insertEdge(Graph *graph, Edge *edge)
{
    if (graph == NULL)
        return NULL;
    if (edge->start >= graph->vertexCount || edge->end >= graph->vertexCount)
        return NULL;
    graph->graphMat[edge->start][edge->end] = edge->weight;
    //对于无向图，还需要下面一句
    graph->graphMat[edge->end][edge->start] = edge->weight;
}

int Visited[MaxSize] = -1;
//深度优先搜索
void depthFirstSearch(Graph *graph, Vertex *vertex)
{
    Stack *stack = createStack();
    Vertex *nextNode = vertex;
    while (!isEmpty(stack))
    {
        visit(nextNode);                                //visit vertex
        push(stack, nextNode);                          //push vertex to stack
        Visited[nextNode->id] = 1;                      //shows that this vertex was visted
        int end = 1;                                    //flag that shows if route comes to end
        for (int i = 0; i < nextNode->neighborNum; ++i) //neighbor of vertex
        {
            Vertex *neighbor = nextNode->neighbors[i];
            if (!Visited[neighbor->id]) //if not visited
            {
                nextNode = neighbor; //set nextNode neighbor not visited
                end = -1;            //shows that end is not coming
                break;
            }
        }
        if (end)
        {
            nextNode = pop(stack); //if end comes,pop a vertex from stack
        }
    }
}

typedef struct lnode
{
    int vertexPosition; //邻接点下标
    WeightType weight;  //边权重
    LVertex *next;
} LVertex;

typedef struct table
{                         //忽略顶点数据
    LVertex *firstVertex; //第一个顶点
} LTable;

typedef struct lgraph
{
    int vertexCount;            //顶点数
    int edgeCount;              //边数
    LTable graphTable[MaxSize]; //邻接表
} LGraph;

LGraph *createGraph(int vertexCount)
{
    LGraph *graph = (LGraph *)malloc(sizeof(LGraph));
    graph->edgeCount = 0;
    graph->vertexCount = vertexCount;
    for (int i = 0; i < graph->vertexCount; ++i)
    {
        graph->graphTable[i].firstVertex = NULL; //邻接表链表初始化为空
    }
    return graph;
}

void insertLEdge(LGraph *graph, Edge *edge)
{
    //建立要插入的节点
    LVertex *vertex = (LVertex *)malloc(sizeof(LVertex));
    vertex->vertexPosition = edge->end;
    vertex->weight = edge->weight;

    //插入邻接表
    vertex->next = graph->graphTable[edge->start].firstVertex;
    graph->graphTable[edge->start].firstVertex = vertex;

    //对于无向图，还需要插入边<end,start>
    LVertex *sVertex = (Vertex *)malloc(sizeof(Vertex));
    sVertex->vertexPosition = edge->start;
    vertex->weight = edge->weight;

    sVertex->next = graph->graphTable[edge->end].firstVertex;
    graph->graphTable[edge->end].firstVertex = sVertex;
}