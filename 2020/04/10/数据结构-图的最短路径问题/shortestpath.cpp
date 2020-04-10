typedef int Queue;
typedef int Vertex;

void enqueue(Queue *queue, Vertex vertex);
Vertex dequeue(Queue *queue);
bool isEmpty(Queue *queue);

const int MaxSize = 100;
const int infty = 65536;
int dist[MaxSize] = {infty};
int path[MaxSize];

void shortestPath(Vertex vertex)
{
    Queue *queue = new Queue();
    enqueue(queue, vertex);
    while (!isEmpty(queue))
    {
        Vertex v = dequeue(queue);
        for (;;)
        {
            Vertex n;
            if (dist[n] == -1)
            {
                dist[n] = dist[v] + 1;
                path[n] = v;
                enqueue(queue, n);
            }
        }
    }
}
int weight(Vertex v_1, Vertex v_2);
bool collected[MaxSize] = {false};
void dijkstra(Vertex vertex)
{
    while (true)
    {
        Vertex v;
        if (!v)
            break;           //跳出循环
        collected[v] = true; //收录顶点
        for (;;)
        {
            Vertex w;
            if (!collected[w])
            {
                if (dist[v] + weight(v, w) < dist[w])
                { //注意到这个条件要求dist[w]>=dist[v]+weight(v,w)时下面的更新路径长度代码才会运行
                    //因此dist的初始值应该是正无穷，否则其初始值可能无法被更新
                    dist[w] = dist[v] + weight(v, w);
                    path[w] = v;
                }
            }
        }
    }
}

int Dist[MaxSize][MaxSize];
int Path[MaxSize][MaxSize];
void floyd(Vertex **map, int mapSize)
{
    //初始化
    for (int i = 0; i < mapSize; ++i)
    {
        for (int j = 0; j < mapSize; ++j)
        {
            Dist[i][j] = map[i][j];
            Path[i][j] = -1;
        }
    }
    for (int k = 0; k < mapSize; ++k)
    {
        for (int i = 0; i < mapSize; ++i)
        {
            for (int j = 0; j < mapSize; ++j)
            {
                if (Dist[i][k] + Dist[k][j] < Dist[i][j])
                { //这里判断k是否影响最短路径
                    //若无连接的两点未被初始化为无穷大，会影响这里的判断
                    Dist[i][j] = Dist[i][k] + Dist[k][j]; //更新最短路径长度
                    Path[i][j] = k;
                }
            }
        }
    }
}
typedef int Stack;

void push(Stack *stack, Vertex vertex)
{
    stack[]
}
Vertex getPath(Stack *stack, Vertex **path, Vertex start, Vertex end)
{
    push(stack, end);
    if (path[start][end] != -1)
    {
        push(stack, getPath(stack, path, path[start][end], end));
        push(stack, getPath(stack, path, start, path[start][end]));
    }
}