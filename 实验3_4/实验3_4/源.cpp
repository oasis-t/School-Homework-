#include<stdio.h>
#include<stdlib.h>
#include <windows.h>

//�ڽӱ�Ľṹ�嶨��
typedef struct ENode
{
    int adjVex;             //���ⶥ��u���ڵĶ���
    int w;             //�ߵ�Ȩֵ
    struct ENode* nextArc;  //ָ����һ���߽��
}ENode;
typedef struct
{
    int n;             //ͼ�ĵ�ǰ������
    int e;             //ͼ�ĵ�ǰ����
    ENode** a;         //ָ��һάָ������
}LGraph;
typedef struct
{
    int front;
    int rear;
    int maxSize;    //�������
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
    if (IsEmpty(Q))      //�ն��д���
        return 0;
    *x = Q->element[(Q->front + 1) % Q->maxSize];
    return 1;
}
BOOL EnQueue(Queue* Q, int x)
{
    if (IsFULL(Q))      //�������
        return 0;
    Q->rear = (Q->rear + 1) % Q->maxSize;
    Q->element[Q->rear] = x;
    return 1;
}
BOOL DeQueue(Queue* Q)
{
    if (IsEmpty(Q))
    {   //�ն��д���
        return 0;
    }
    Q->front = (Q->front + 1) % Q->maxSize;
    return 1;
}

//�ڽӱ�ĳ�ʼ��
int Init(LGraph* lg, int nSize)
{
    int  i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));  //��̬���ɳ���Ϊn��һάָ������
    if (!lg->a) return 0;
    else
    {
        for (i = 0; i < lg->n; i++)
        {
            lg->a[i] = NULL;                        //��ָ������a�ÿ�
        }
        return 1;
    }
}
//�ڽӱ�ĳ���
void Destory(LGraph* lg)
{
    int i;
    ENode* p, * q;
    for (i = 0; i < lg->n; i++)
    {
        p = lg->a[i];                 //ָ��pָ�򶥵�i�ĵ�����ĵ�һ���߽��
        q = p;
        while (p)
        {                     //�ͷŶ���i�ĵ����������б߽��
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);                     //�ͷ�һάָ������a�Ĵ洢�ռ�
}
//�ڽӱ��������
int Exist(LGraph* lg, int u, int v)
{
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;
    p = lg->a[u];                   //ָ��pָ�򶥵�u�ĵ�����ĵ�һ���߽��
    while (p != NULL && p->adjVex != v)
    {
        p = p->nextArc;
    }
    if (!p) return 0;            //��δ�ҵ��˱�,�򷵻�0
    else return 1;
}
//�ڽӱ�Ĳ����
int Insert(LGraph* lg, int u, int v, int w)
{
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;
    if (Exist(lg, u, v))
    {
        printf("Duplicate��");
        return 0;
    }//�˱��Ѵ���,���ش���
    p = (ENode*)malloc(sizeof(ENode));   //Ϊ�µı߽�����洢�ռ�
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];             //���µı߽����뵥�������ǰ��
    lg->a[u] = p;
    lg->e++;                            //�߼�1
    return 1;
}
//�ڽӱ��ɾ����
int Remove(LGraph* lg, int u, int v)
{
    ENode* p, * q;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return 0;
    p = lg->a[u];
    q = NULL;
    while (p && p->adjVex != v)
    {         //���Ҵ�ɾ�����Ƿ����
        q = p;
        p = p->nextArc;
    }
    if (!p)
    {
        printf("NotPresent��");
        return 0;          //pΪ��,��ɾ���߲�����
    }
    if (q) q->nextArc = p->nextArc;     //�ӵ�����ɾ���˱�
    else lg->a[u] = p->nextArc;
    free(p);
    lg->e--;
    return 1;
}
void DFS(int v, int visited[], LGraph g)
{
    ENode* w;
    printf("%d ", v);                           //���ʶ���v
    visited[v] = 1;                            //Ϊ����v���Ϸ��ʱ��
    for (w = g.a[v]; w; w = w->nextArc)
    {          //����v���ڽӵ�
        if (!visited[w->adjVex])
        {
            DFS(w->adjVex, visited, g);          //��wδ������,��ݹ����DFS
        }
    }
}

void DFSGraph(LGraph g)
{
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); //��̬���ɱ������visted
    for (i = 0; i < g.n; i++)
        visited[i] = 0;                             //visted�����ʼ��
    for (i = 0; i < g.n; i++)
    {                        //��һ���ÿ������,��δ������,�����DFS
        if (!visited[i])
            DFS(i, visited, g);
    }
    free(visited);                                 //�ͷ�visted����
}
void BFS(int v, int visited[], LGraph g)
{
    ENode* w;
    Queue q;
    Create(&q, g.n);                        //��ʼ������
    visited[v] = 1;                        //Ϊ����v���Ϸ��ʱ��
    printf("%d ", v);                       //���ʶ���v
    EnQueue(&q, v);                         //������v�������
    while (!IsEmpty(&q))
    {
        Front(&q, &v);
        DeQueue(&q);                       //���׶��������
        for (w = g.a[v]; w; w = w->nextArc)
        {  //����v�������ڽӵ�
            if (!visited[w->adjVex])
            {       //��wδ������,������ʲ��������
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
    int* visited = (int*)malloc(g.n * sizeof(int));  //��̬����visited����
    for (i = 0; i < g.n; i++)
        visited[i] = 0;
    for (i = 0; i < g.n; i++)
    {                        //��һ���ÿ������,��δ������,�����BFS
        if (!visited[i])
            BFS(i, visited, g);
    }
    free(visited);
}

int main()
{
    LGraph lg;
    int i, u, v, w, n, noe;//nΪ���������noeΪ�߸���,wΪȨֵ
    printf("���붥�����:");
    scanf_s("%d", &n);
    Init(&lg, n);
    printf("����ߵĸ���:");
    scanf_s("%d", &noe);
    for (i = 0; i < noe; i++)
    {
        scanf_s("%d%d%d", &u, &v, &w);
        Insert(&lg, u, v, w);
    }
    printf("����Ҫɾ���ıߵĶ��㣺");
    scanf_s("%d%d", &u, &v);
    if (Exist(&lg, u, v))
    {
        printf("Present��\n");
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