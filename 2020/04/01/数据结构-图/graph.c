#define Graph
#define Vertex
#define Edge

Graph *create();                                             //创建空图返回
Graph *insertVertex(Graph *graph, Vertex *vertex);           //将节点插入图
Graph *insertEdge(Graph *graph, Edge *edge);                 //将边插入图
void depthFirstSearch(Graph *graph, Vertex *vertex);         //从顶点vertex出发深度优先遍历
void breadthFirstSearch(Graph *graph, Vertex *vertex);       //从顶点vertex出发宽度优先遍历
void shortestPath(Graph *graph, Vertex *vertex, int dist[]); //计算从节点vertex到任意节点的最短路径
void minSpanningTree(Graph *graph);                          //计算图的最小生成树