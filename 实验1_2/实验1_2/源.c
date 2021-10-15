#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int Elemtype;
typedef int Status;
typedef struct node
{
	Elemtype element;//数据域
	struct node* link;//指针域
}Node;
typedef struct headerlist
{
	Node* head;
	int n;
}Headerlist;
Status Init(Headerlist* h)
{
	h->head = (Node*)malloc(sizeof(Node));//生成表头结点
	if (!h->head)
		return 0;
	h->head->link = NULL;//设置单链表为空
	h->n = 0;
	return 1;
}
Status Insert(Headerlist* h, int i, Elemtype x)
{
	Node* p, * q;
	int j;
	if (i<-1 || i>h->n - 1)//判断是否越界
		return 0;
	p = h->head;
	for (j = 0; j <= i; j++)
		p = p->link;
	q = (Node*)malloc(sizeof(Node));
	q->element = x;
	q->link = p->link;
	p->link = q;
	h->n++;
	return 1;
}
Status Delete(Headerlist* h, int i)
{
	int j;
	Node* q, * p;
	if (!h->n)//判断是否为空
		return 0;
	if (i<0 || i>h->n - 1)//判断是否越界
		return 0;
	q = h->head;
	for (j = 0; j < i; j++)
		q = q->link;
	p = q->link;
	q->link = p->link;//从单链表中删除p所指结点
	free(p);      //释放p所指结点的空间
	h->n--;
	return 1;
}
Status Find(Headerlist* h,int i,Elemtype*x)
{
	Node* p;
	int j;
	if (i<0 || i>h->n-1)//判断是否越界
		return 0;
	p = h->head;
	for (j = 0; j < i; j++)
		p = p->link;//从头结点开始查找
	*x = p->element;//通过x返回值
	return 1;
}
Status Output(Headerlist* h)
{
	Node* p;
	if (!h->n)//判断是否为空
		return 0;
	p = h->head->link;
	while (p)
	{
		printf("%d ", p->element);
		p = p->link;
	}
	return 1;
}
void Destroy(Headerlist* h)
{
	Node* p;
	while (h->head)
	{
		p = h->head->link;//保留后继结点地址防止断链
		free(h->head);//释放头结点所指空间
		h->head = p;
	}
}
void main()
{
	int i, x;
	Headerlist list;
	Init(&list);
	for (i = 0; i < 9; i++)
		Insert(&list, i-1, i);
	printf("此链表为：");
	Output(&list);
	Delete(&list,0);
	printf("\n删除后链表为：");
	Output(&list);
	Find(&list, 2, &x);
	printf("查找的值为：");
	printf("%d", x);
	Destroy(&list);
}