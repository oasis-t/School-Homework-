#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct mGraph
{
	int** a;//�ڽӾ���
	int n;  //ͼ�Ķ�����
	int e;  //ͼ�ĵ�ǰ����
	int noEdge; //��������ޱߵ�ֵ
}MGraph;

typedef struct 
{
	int front;
	int rear;
	int maxSize;    //�������
	int * element;
}Queue;
//��������
void Create(Queue* Q, int mSize) 
{
	Q->maxSize = mSize;
	Q->element = (int*)malloc(sizeof(int) * mSize);
	Q->front = Q->rear = 0;
}
//�ж��Ƿ�Ϊ��
BOOL IsEmpty(Queue* Q)
{
	return Q->front == Q->rear;
}
//�ж��Ƿ�Ϊ��
BOOL IsFULL(Queue* Q)
{
	return (Q->rear + 1) % Q->maxSize == Q->front;
}

BOOL Front(Queue* Q, int* x) 
{
	if (IsEmpty(Q))      //�ն��д���
		return 0;
	*x = Q->element[(Q->front + 1) % Q->maxSize];
	return 1;
}
//���
BOOL EnQueue(Queue* Q, int x) 
{
	if (IsFULL(Q))      //�������
		return 0;
	Q->rear = (Q->rear + 1) % Q->maxSize;
	Q->element[Q->rear] = x;
	return 1;
}
//����
BOOL DeQueue(Queue* Q)
{
	if (IsEmpty(Q))   //�ն��д���
		return 0;
	Q->front = (Q->front + 1) % Q->maxSize;
	return 1;
}
void DFS(int v, int visited[], mGraph g) 
{
	int j;
	printf("%d ", v);              //���ʶ���v
	visited[v] = 1;               //Ϊ����v���Ϸ��ʱ��       
	for (j = 0; j < g.n; j++) 
	{      //����v���ڽӵ�
		if (!visited[j] && g.a[v][j] > 0)  //��δ����������Ȩֵ
			DFS(j, visited, g);
	}
}
void DFSGraph(mGraph g)
{
	int i;
	int* visited = (int*)malloc(g.n * sizeof(int)); //��̬���ɱ������visted
	for (i = 0; i < g.n; i++) 
	{
		visited[i] = 0;          //visted�����ʼ��
	}                            //visted�����ʼ��
	for (i = 0; i < g.n; i++) 
	{     //��һ���ÿ������,��δ������,�����DFS
		if (!visited[i])
		{   //��δ����������Ȩֵ
			DFS(i, visited, g);
		}
	}
	free(visited);                       //�ͷ�visted����
}
void BFS(int v, int visited[], mGraph g)
{
	Queue q;
	Create(&q, g.n);                        //��ʼ������
	visited[v] = 1;                        //Ϊ����v���Ϸ��ʱ��
	printf("%d ", v);                       //���ʶ���v
	EnQueue(&q, v);                         //������v�������
	while (!IsEmpty(&q)) 
	{
		Front(&q, &v);
		DeQueue(&q);                       //���׶��������
		for (int i = 0; i < g.n; i++) 
		{       //����v��ÿһ��
			if (!visited[i] && g.a[v][i] > 0) 
			{       //��δ����������Ȩֵ,������ʲ��������,ע�������жϵ���g.a[v][i]��ά����
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
	int* visited = (int*)malloc(g.n * sizeof(int));  //��̬����visited����
	for (i = 0; i < g.n; i++)
	{                         //��ʼ��visited����
		visited[i] = 0;
	}
	for (i = 0; i < g.n; i++)
	{                        //��һ���ÿ������,��δ������,�����BFS
		if (!visited[i]) 
			BFS(i, visited, g);
	}
	free(visited);
}
//��ʼ��
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
//����
void Destroy(mGraph* mg)
{
	int i;
	for (i = 0; i <= mg->n; i++)
		free(mg->a[i]);
	free(mg->a);
}
//����
int Exist(mGraph* mg, int u, int v)
{
	if (u<0 || v<0 || u>mg->n - 1 || v>mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)
		return 0;
	return 1;
}
//����
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
//ɾ��
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
	int i,w, u, n, v, noe;//noeΪ�ߵ�����,nΪ�������,u��vΪ���㣬wΪuv֮��ߵ�Ȩֵ
	printf("���붥�����:");
	scanf_s("%d", &n);
	Init(&mg, n, 0);
	printf("����ߵĸ�����");
	scanf_s("%d",&noe);
	for (i = 0; i < noe; i++)
	{
		scanf_s("%d%d%d", &u, &v, &w);
		Insert(&mg,u,v,w);
	}
	printf("����Ҫɾ���ıߵĶ��㣺");
	scanf_s("%d%d",&u,&v);
	if (Exist(&mg, u, v))
	{
		printf("Present��\n");
		if (Remove(&mg, u, v))
			printf("Delete succeed!");
		else
			printf("Delete failed!");
	}
	else
		printf("Not present!");
	printf("\n������ȱ���:\n");
	DFSGraph(mg);
	printf("\n������ȱ���:\n");
	BFSGraph(mg);
	Destroy(&mg);
	return 0;
}