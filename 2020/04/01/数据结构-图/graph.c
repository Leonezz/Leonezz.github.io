#define Size 100
typedef Vertex StackElementType;

typedef struct graph
{
    Vertex graphMat[Size][Size];
} Graph;

typedef struct vertex
{
    int id;
    Vertex **neighbors;
    int neighborNum;
} Vertex;

typedef struct edge
{
    Vertex *v1;
    Vertex *v2;
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

Graph *create();                                             //创建空图返回
Graph *insertVertex(Graph *graph, Vertex *vertex);           //将节点插入图
Graph *insertEdge(Graph *graph, Edge *edge);                 //将边插入图
void depthFirstSearch(Graph *graph, Vertex *vertex);         //从顶点vertex出发深度优先遍历
void breadthFirstSearch(Graph *graph, Vertex *vertex);       //从顶点vertex出发宽度优先遍历
void shortestPath(Graph *graph, Vertex *vertex, int dist[]); //计算从节点vertex到任意节点的最短路径
void minSpanningTree(Graph *graph);                          //计算图的最小生成树
void visit(Vertex *vertex);

int Visited[Size] = -1;
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

void breadthFirstSearch(Graph *graph, Vertex *vertex)
{
    visit(vertex);           //visite vertex first
    Visited[vertex->id] = 1; //set visited true
    Queue *queue = createQueue();
    add(queue, vertex); //add to queue to find its neighbors
    while (!isEmpty(queue))
    {
        Vertex *v = delete (queue);
        for (int i = 0; i < v->neighborNum; ++i) //find all neighbors
        {
            Vertex *neighbor = v->neighbors[i];
            if (!Visited[neighbor->id]) //if not visted,visit and add to queue
            {
                visit(neighbor);
                Visited[neighbor->id] = 1;
                add(queue, neighbor);
            }
        }
    }
}
