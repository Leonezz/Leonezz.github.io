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
} MGraph;

typedef int Vertex;
typedef struct edge
{
    Vertex start;      //起点
    Vertex end;        //终点
    WeightType weight; //权重
} Edge;

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

const int infty = 65536;
int dist[MaxSize] = {infty};
int path[MaxSize];

Vertex minDistOfGraph(MGraph *graph, WeightType *dist);

WeightType prim(MGraph *mgraph, LGraph *lgraph)
{
    WeightType dist[MaxSize];
    Vertex parent[MaxSize];
    for (int i = 0; i < mgraph->vertexCount; ++i)
    {
        dist[i] = mgraph->graphMat[0][i];
        parent[i] = 0;
    }
    lgraph = createGraph(mgraph->vertexCount);
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    int vCount = 1;
    int pathWeight = 0;
    dist[0] = 0;
    parent[0] = -1;
    while (true)
    {
        Vertex vertex = minDistOfGraph(mgraph, dist);
        if (vertex == NULL)
        {
            break;
        }
        edge->start = parent[vertex];
        edge->end = vertex;
        edge->weight = dist[vertex];
        insertLEdge(lgraph, edge);
        pathWeight += dist[vertex];
        dist[vertex] = 0;
        vCount++;
        for (int i = 0; i < mgraph->vertexCount; ++i)
        {
            if (dist[i] != 0 && mgraph->graphMat[vertex][i] != infty)
            {
                if (mgraph->graphMat[vertex][i] < dist[i])
                {
                    dist[i] = mgraph->graphMat[vertex][i];
                    parent[i] = vertex;
                }
            }
        }
    }
    if (vCount < mgraph->vertexCount)
        return NULL;
    return pathWeight;
}