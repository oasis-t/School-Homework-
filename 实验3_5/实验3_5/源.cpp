#include <stdio.h>
#include <stdlib.h>
#define INFTY 32767    //���������

typedef struct eNode
{
	int adjVex;             //�����ⶥ��u���ڽӵĶ���
	int w;                  //�ߵ�Ȩֵ
	struct eNode* nextArc;
}ENode;

typedef struct lGraph
{
	int n;                  //ͼ�ĵ�ǰ������
	int e;                  //ͼ�ĵ�ǰ����
	ENode** a;              //ָ��һάָ������
}LGraph;


int Init(LGraph* lg, int nSize)   // �ڽӱ�ĳ�ʼ��
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

void Destroy(LGraph* lg)           //�ڽӱ�ĳ���
{
	int i;
	ENode* p, * q;
	for (i = 0; i < lg->n; i++)
	{
		p = lg->a[i];                //ָ��pָ�򶥵�i�ĵ�����ĵ�һ���߽��
		q = p;
		while (p)                    //�ͷŶ���i�ĵ����������б߽��
		{
			p = p->nextArc;
			free(q);
			q = p;
		}
	}
	free(lg->a);                     //��һάָ������a�Ĵ洢�ռ�
}

int Exist(LGraph* lg, int u, int v)   //�ߵ�����
{
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
	{
		printf("��������������");
		return 0;
	}
	p = lg->a[u];                     //ָ��pָ�򶥵�i�ĵ�����ĵ�һ���߽��
	while (p && p->adjVex != v) p = p->nextArc;
	if (!p)     return 0;        //��δ�ҵ��˱ߣ�����0
	else  return 1;                  //���ҵ��˱ߣ��򷵻�1
}

int Insert(LGraph* lg, int u, int v, int w)    //�ߵĲ���
{
	ENode* p;
	if (u<0 || v<0 || u>lg->n - 1 || v>lg->n - 1 || u == v)
		return 0;
	if (Exist(lg, u, v))
	{
		printf("Duplicate��\n");
		return 0;
	}
	p = (ENode*)malloc(sizeof(ENode));     //Ϊ�µı߽�����洢�ռ�
	p->adjVex = v;
	p->w = w;
	p->nextArc = lg->a[u];                    //���µı߽����뵥�������ǰ��
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
		if (lg->a[i] != NULL)                               //�ж��Ƿ��пյĵ�����
			for (w = lg->a[i]; w->adjVex != NULL; w = w->nextArc)
			{
				a[i][w->adjVex] = w->w;                           //�����ڽӾ���
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
				printf("��\t");
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
	int n, i, j, noe;             //nΪ������ j�����ж��Ƿ�Ϊ����ͼ�� noeΪͼ�ı���
	int u, v, w;                  //u,vΪ�ߵ������ڵ㣬wΪȨֵ
	printf("����ͼ�Ķ�������");
	scanf_s("%d", &n);
	Init(&lg, n);
	printf("��ͼ�Ƿ�Ϊ����ͼ(�ǵ����� 1���������� 0)��");
	scanf_s("%d", &j);
	printf("���������ͼ�ı�(��Ϊ����ͼ����˳������,������Ȩֵ����Ĭ������1)��");
	printf("����ͼ�ıߵ�������");
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