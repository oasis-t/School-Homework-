#include<stdio.h>
#include<stdlib.h>
#include <windows.h>

//邻接表的结构体定义
typedef struct ENode
{
    int adjVex;             //任意顶点u相邻的顶点
    int w;             //边的权值
    struct ENode* nextArc;  //指向下一个边结点
}ENode;
typedef struct
{
    int n;             //图的当前顶点数
    int e;             //图的当前边数
    ENode** a;         //指向一维指针数组
}LGraph;
typedef struct
{
    int front;
    int rear;
    int maxSize;    //最大容量
    int* element;
}Queue;

void Create(Queue* Q, int mSize)
{
    Q->maxSize = mSize;
    Q->element = (int*)malloc(sizeof(int) * mSize);
    Q->front = Q->rear = 0;
}
BOOL IsEmpty(Queue* Q)
{
    return Q->front == Q->rear;
}
BOOL IsFULL(Queue* Q)
{
    return (Q->rear + 1) % Q->maxSize == Q->front;
}
BOOL Front(Queue* Q, int* x)
{
    if (IsEmpty(Q))      //空队列处理
        return 0;
    *x = Q->element[(Q->front + 1) % Q->maxSize];
    return 1;
}
BOOL EnQueue(Queue* Q, int x)
{
    if (IsFULL(Q))      //溢出处理
        return 0;
    Q->rear = (Q->rear + 1) % Q->maxSize;
    Q->element[Q->rear] = x;
    return 1;
}
BOOL DeQueue(Queue* Q)
{
    if (IsEmpty(Q))
    {   //空队列处理
        return 0;
    }
    Q->front = (Q->front + 1) % Q->maxSize;
    return 1;
}

//邻接表的初始化
int Init(LGraph* lg, int nSize)
{
    int  i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));  //动态生成长度为n的一维指针数组
    if (!lg->a) return 0;
    else
    {
        for (i = 0; i < lg->n; i++)
        {
            lg->a[i] = NULL;                        //将指针数组a置空
        }
        return 1;
    }
}
//邻接表的撤销
void Destory(LGraph* lg)
{
    int i;
    ENode* p, * q;
    for (i = 0; i < lg->n; i++)
    {
        p = lg->a[i];                 //指针p指向顶点i的单链表的第一个边结点
        q = p;
        while (p)
        {                     //释放顶点i的单链表中所有边结点
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);                     //释放一维指针数组a的存储空间
}
//邻接表的搜索边
int Exist(LGraph* lg, int u, int v)
{
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;
    p = lg->a[u];                   //指针p指向顶点u的单链表的第一个边结点
    while (p != NULL && p->adjVex != v)
    {
        p = p->nextArc;
    }
    if (!p) return 0;            //若未找到此边,则返回0
    else return 1;
}
//邻接表的插入边
int Insert(LGraph* lg, int u, int v, int w)
{
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;
    if (Exist(lg, u, v))
    {
        printf("Duplicate！");
        return 0;
    }//此边已存在,返回错误
    p = (ENode*)malloc(sizeof(ENode));   //为新的边结点分配存储空间
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];             //将新的边结点插入单链表的最前面
    lg->a[u] = p;
    lg->e++;                            //边加1
    return 1;
}
//邻接表的删除边
int Remove(LGraph* lg, int u, int v)
{
    ENode* p, * q;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;
    p = lg->a[u];
    q = NULL;
    while (p && p->adjVex != v)
    {         //查找待删除边是否存在
        q = p;
        p = p->nextArc;
    }
    if (!p)
    {
        printf("NotPresent！");
        return 0;          //p为空,待删除边不存在
    }
    if (q) q->nextArc = p->nextArc;     //从单链表删除此边
    else lg->a[u] = p->nextArc;
    free(p);
    lg->e--;
    return 1;
}
void DFS(int v, int visited[], LGraph g)
{
    ENode* w;
    printf("%d ", v);                           //访问顶点v
    visited[v] = 1;                            //为顶点v打上访问标记
    for (w = g.a[v]; w; w = w->nextArc)
    {          //遍历v的邻接点
        if (!visited[w->adjVex])
        {
            DFS(w->adjVex, visited, g);          //若w未被访问,则递归调用DFS
        }
    }
}

void DFSGraph(LGraph g)
{
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); //动态生成标记数组visted
    for (i = 0; i < g.n; i++)
        visited[i] = 0;                             //visted数组初始化
    for (i = 0; i < g.n; i++)
    {                        //逐一检查每个顶点,若未被访问,则调用DFS
        if (!visited[i])
            DFS(i, visited, g);
    }
    free(visited);                                 //释放visted数组
}
void BFS(int v, int visited[], LGraph g)
{
    ENode* w;
    Queue q;
    Create(&q, g.n);                        //初始化队列
    visited[v] = 1;                        //为顶点v打上访问标记
    printf("%d ", v);                       //访问顶点v
    EnQueue(&q, v);                         //将顶点v放入队列
    while (!IsEmpty(&q))
    {
        Front(&q, &v);
        DeQueue(&q);                       //队首顶点出队列
        for (w = g.a[v]; w; w = w->nextArc)
        {  //遍历v的所有邻接点
            if (!visited[w->adjVex])
            {       //若w未被访问,则将其访问并放入队列
                visited[w->adjVex] = 1;
                printf("%d ", w->adjVex);
                EnQueue(&q, w->adjVex);
            }
        }
    }
}
void BFSGraph(LGraph g)
{
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int));  //动态生成visited数组
    for (i = 0; i < g.n; i++)
        visited[i] = 0;
    for (i = 0; i < g.n; i++)
    {                        //逐一检查每个顶点,若未被访问,则调用BFS
        if (!visited[i])
            BFS(i, visited, g);
    }
    free(visited);
}

int main()
{
    LGraph lg;
    int i, u, v, w, n, noe;//n为顶点个数，noe为边个数,w为权值
    printf("输入顶点个数:");
    scanf_s("%d", &n);
    Init(&lg, n);
    printf("输入边的个数:");
    scanf_s("%d", &noe);
    for (i = 0; i < noe; i++)
    {
        scanf_s("%d%d%d", &u, &v, &w);
        Insert(&lg, u, v, w);
    }
    printf("输入要删除的边的顶点：");
    scanf_s("%d%d", &u, &v);
    if (Exist(&lg, u, v))
    {
        printf("Present！\n");
        if (Remove(&lg, u, v))
            printf("Delete succeed!");
        else
            printf("Delete failed!");
    }
    else
        printf("Not present!");
    printf("\nDFS:\n");
    DFSGraph(lg);
    printf("\nBFS:\n");
    BFSGraph(lg);
    return 0;
}