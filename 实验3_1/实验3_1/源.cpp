#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct mGraph
{
	int** a;//邻接矩阵
	int n;  //图的顶点数
	int e;  //图的当前边数
	int noEdge; //两顶点间无边的值
}MGraph;

typedef struct 
{
	int front;
	int rear;
	int maxSize;    //最大容量
	int * element;
}Queue;
//创建队列
void Create(Queue* Q, int mSize) 
{
	Q->maxSize = mSize;
	Q->element = (int*)malloc(sizeof(int) * mSize);
	Q->front = Q->rear = 0;
}
//判断是否为空
BOOL IsEmpty(Queue* Q)
{
	return Q->front == Q->rear;
}
//判断是否为满
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
//入队
BOOL EnQueue(Queue* Q, int x) 
{
	if (IsFULL(Q))      //溢出处理
		return 0;
	Q->rear = (Q->rear + 1) % Q->maxSize;
	Q->element[Q->rear] = x;
	return 1;
}
//出队
BOOL DeQueue(Queue* Q)
{
	if (IsEmpty(Q))   //空队列处理
		return 0;
	Q->front = (Q->front + 1) % Q->maxSize;
	return 1;
}
void DFS(int v, int visited[], mGraph g) 
{
	int j;
	printf("%d ", v);              //访问顶点v
	visited[v] = 1;               //为顶点v打上访问标记       
	for (j = 0; j < g.n; j++) 
	{      //遍历v的邻接点
		if (!visited[j] && g.a[v][j] > 0)  //当未被访问且有权值
			DFS(j, visited, g);
	}
}
void DFSGraph(mGraph g)
{
	int i;
	int* visited = (int*)malloc(g.n * sizeof(int)); //动态生成标记数组visted
	for (i = 0; i < g.n; i++) 
	{
		visited[i] = 0;          //visted数组初始化
	}                            //visted数组初始化
	for (i = 0; i < g.n; i++) 
	{     //逐一检查每个顶点,若未被访问,则调用DFS
		if (!visited[i])
		{   //当未被访问且有权值
			DFS(i, visited, g);
		}
	}
	free(visited);                       //释放visted数组
}
void BFS(int v, int visited[], mGraph g)
{
	Queue q;
	Create(&q, g.n);                        //初始化队列
	visited[v] = 1;                        //为顶点v打上访问标记
	printf("%d ", v);                       //访问顶点v
	EnQueue(&q, v);                         //将顶点v放入队列
	while (!IsEmpty(&q)) 
	{
		Front(&q, &v);
		DeQueue(&q);                       //队首顶点出队列
		for (int i = 0; i < g.n; i++) 
		{       //遍历v的每一项
			if (!visited[i] && g.a[v][i] > 0) 
			{       //若未被访问且有权值,则将其访问并放入队列,注意这里判断的是g.a[v][i]二维数组
				visited[i] = 1;
				printf("%d ", i);
				EnQueue(&q, i);
			}
		}
	}
}
void BFSGraph(mGraph g) 
{
	int i;
	int* visited = (int*)malloc(g.n * sizeof(int));  //动态生成visited数组
	for (i = 0; i < g.n; i++)
	{                         //初始化visited数组
		visited[i] = 0;
	}
	for (i = 0; i < g.n; i++)
	{                        //逐一检查每个顶点,若未被访问,则调用BFS
		if (!visited[i]) 
			BFS(i, visited, g);
	}
	free(visited);
}
//初始化
int Init(mGraph* mg, int nsize, int noEdgeValue)
{
	int i, j;
	mg->n = nsize;
	mg->e = 0;
	mg->noEdge = noEdgeValue;
	mg->a = (int**)malloc(nsize * sizeof(int*));
	if (!mg->a)
		return 0;
	for (i = 0; i < mg->n; i++)
	{
		mg->a[i] = (int*)malloc(nsize * sizeof(int));
		for (j = 0; j < mg->n; j++)
			mg->a[i][j] = mg->noEdge;
		mg->a[i][j] = 0;
	}
	return 1;
}
//撤销
void Destroy(mGraph* mg)
{
	int i;
	for (i = 0; i <= mg->n; i++)
		free(mg->a[i]);
	free(mg->a);
}
//搜索
int Exist(mGraph* mg, int u, int v)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)
		return 0;
	return 1;
}
//插入
int Insert(mGraph* mg, int u, int v, int w)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v)
		return 0;
	if (mg->a[u][v] != mg->noEdge)
		return 0;
	mg->a[u][v] = w;
	mg->e++;
	return 1;
}
//删除
int Remove(mGraph* mg, int u, int v)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)
		return 0;
	mg->a[u][v] = mg->noEdge;
	mg->e--;
	return 1;
}
int main()
{
	MGraph mg;
	int i,w, u, n, v, noe;//noe为边的条数,n为顶点个数,u，v为顶点，w为uv之间边的权值
	printf("输入顶点个数:");
	scanf_s("%d", &n);
	Init(&mg, n, 0);
	printf("输入边的个数：");
	scanf_s("%d",&noe);
	for (i = 0; i < noe; i++)
	{
		scanf_s("%d%d%d", &u, &v, &w);
		Insert(&mg,u,v,w);
	}
	printf("输入要删除的边的顶点：");
	scanf_s("%d%d",&u,&v);
	if (Exist(&mg, u, v))
	{
		printf("Present！\n");
		if (Remove(&mg, u, v))
			printf("Delete succeed!");
		else
			printf("Delete failed!");
	}
	else
		printf("Not present!");
	printf("\n深度优先遍历:\n");
	DFSGraph(mg);
	printf("\n宽度优先遍历:\n");
	BFSGraph(mg);
	Destroy(&mg);
	return 0;
}