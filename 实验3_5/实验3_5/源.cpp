#include <stdio.h>
#include <stdlib.h>
#define INFTY 32767    //定义无穷大

typedef struct eNode
{
	int adjVex;             //与任意顶点u相邻接的顶点
	int w;                  //边的权值
	struct eNode* nextArc;
}ENode;

typedef struct lGraph
{
	int n;                  //图的当前顶点数
	int e;                  //图的当前边数
	ENode** a;              //指向一维指针数组
}LGraph;


int Init(LGraph* lg, int nSize)   // 邻接表的初始化
{
	int i;
	lg->n = nSize;
	lg->e = 0;
	lg->a = (ENode**)malloc(nSize * sizeof(ENode*));
	if (!lg->a)
		return 0;
	else
	{
		for (i = 0; i < lg->n; i++)
			lg->a[i] = NULL;
		return 1;
	}
}

void Destroy(LGraph* lg)           //邻接表的撤销
{
	int i;
	ENode* p, * q;
	for (i = 0; i < lg->n; i++)
	{
		p = lg->a[i];                //指针p指向顶点i的单链表的第一个边结点
		q = p;
		while (p)                    //释放顶点i的单链表中所有边结点
		{
			p = p->nextArc;
			free(q);
			q = p;
		}
	}
	free(lg->a);                     //释一维指针数组a的存储空间
}

int Exist(LGraph* lg, int u, int v)   //边的搜索
{
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
	{
		printf("顶点参数输入错误");
		return 0;
	}
	p = lg->a[u];                     //指针p指向顶点i的单链表的第一个边结点
	while (p && p->adjVex != v) p = p->nextArc;
	if (!p)     return 0;        //若未找到此边，返回0
	else  return 1;                  //若找到此边，则返回1
}

int Insert(LGraph* lg, int u, int v, int w)    //边的插入
{
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
		return 0;
	if (Exist(lg, u, v))
	{
		printf("Duplicate！\n");
		return 0;
	}
	p = (ENode*)malloc(sizeof(ENode));     //为新的边结点分配存储空间
	p->adjVex = v;
	p->w = w;
	p->nextArc = lg->a[u];                    //将新的边结点插入单链表的最前面
	lg->a[u] = p;
	lg->e++;
	return 1;
}

int** trans(LGraph* lg)
{
	int i, j;
	ENode* w;
	int** a = (int**)malloc(lg->n * sizeof(int*));
	for (i = 0; i < lg->n; i++)
	{
		a[i] = (int*)malloc(lg->n * sizeof(int));
		for (j = 0; j < lg->n; j++)
			a[i][j] = 0;
		a[i][i] = 0;
	}
	for (i = 0; i < lg->n; i++)
	{
		if (lg->a[i] != NULL)                               //判断是否有空的单链表
			for (w = lg->a[i]; w->adjVex != NULL; w = w->nextArc)
			{
				a[i][w->adjVex] = w->w;                           //构造邻接矩阵
				if (w->nextArc == NULL) break;
			}
	}
	for (i = 0; i < lg->n; i++)
		for (j = 0; j < lg->n; j++)
			if (a[i][j] == 0)
				a[i][j] = INFTY;
	return a;
}

void Floyd(LGraph* lg)
{
	int i, j, k;
	int** d = (int**)malloc(lg->n * sizeof(int*));
	int** p = (int**)malloc(lg->n * sizeof(int*));
	int** x = (int**)malloc(lg->n * sizeof(int*));
	for (i = 0; i < lg->n; i++)
	{
		d[i] = (int*)malloc(lg->n * sizeof(int));
		p[i] = (int*)malloc(lg->n * sizeof(int));
		for (j = 0; j < lg->n; j++)
		{
			d[i][j] = 0;
			p[i][j] = 0;
		}
	}
	for (i = 0; i < lg->n; i++)
	{
		x[i] = (int*)malloc(lg->n * sizeof(int));
		for (j = 0; j < lg->n; j++)
			x[i][j] = 0;
		x[i][i] = 0;
	}
	x = trans(lg);
	for (i = 0; i < lg->n; i++)
		for (j = 0; j < lg->n; j++)
		{
			d[i][j] = x[i][j];
			if (i != j && x[i][j] < INFTY) p[i][j] = i;
			else p[i][j] = -1;
		}
	for (k = 0; k < lg->n; k++)
		for (i = 0; i < lg->n; i++)
			for (j = 0; j < lg->n; j++)
				if (d[i][k] + d[k][j] < d[i][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = p[k][j];
				}
	for (i = 0; i < lg->n; i++)
	{
		for (j = 0; j < lg->n; j++)
			if (d[i][j] == INFTY)
			{
				printf("∞\t");
			}
			else
			{
				printf("%d \t", d[i][j]);
			}
		printf("\n");
	}
}

int main()
{
	LGraph lg;
	int n, i, j, noe;             //n为顶点数 j用来判断是否为有向图， noe为图的边数
	int u, v, w;                  //u,v为边的两个节点，w为权值
	printf("输入图的顶点数：");
	scanf_s("%d", &n);
	Init(&lg, n);
	printf("该图是否为有向图(是的输入 1，不是输入 0)：");
	scanf_s("%d", &j);
	printf("依次输入该图的边(若为有向图，按顺序输入,若边无权值，则默认输入1)：");
	printf("输入图的边的条数：");
	scanf_s("%d", &noe);
	for (i = 0; i < noe; i++)
	{
		scanf_s("%d%d%d", &u,&v,&w);
		if (j)
			Insert(&lg, u, v, w);
		else
		{
			Insert(&lg, u, v, w);
			Insert(&lg, v, u, w);
		}
	}
	Floyd(&lg);
	Destroy(&lg);
	return 0;
}