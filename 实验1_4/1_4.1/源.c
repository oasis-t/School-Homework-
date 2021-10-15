#include<stdio.h>
#include<malloc.h>
#include<time.h>
typedef int Elemtype;
typedef int Status;

typedef struct node
{
	Elemtype element;
	struct node* link;
}Node;

typedef struct headerlist
{
	Node* head;
	int n;
}Headerlist;

Status Init(Headerlist* h)
{
	h->head = (Node*)malloc(sizeof(Node));
	if (!h->head)
		return 0;
	h->head->link = NULL;
	h->n = 0;
	return 1;
}
Status Insert(Headerlist* h, int i, Elemtype x)
{
	Node* p, * q;
	int j;
	p = h->head;
	for (j = 0; j <=i; j++)
		p = p->link;
	q = (Node*)malloc(sizeof(Node));
	q->element = x;
	q->link = p->link;
	p->link = q;
	h->n++;
	return 1;
}
Status Output(Headerlist* h)
{
	Node* p;
	if (!h->n)
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
		p = h->head->link;
		free(h->head);
		h->head = p;
	}
}
void Reverse(Headerlist* h)
{
	Node* p, * q;
	p = h->head->link;
	h->head->link = NULL;
	while (p)//只要p不为空，q指向p，p后移一位，将q和h->head互换
	{
		q = p;
		p = p->link;
		q->link = h->head->link;
		h->head->link = q;
	}
}
int length(Headerlist* h)//求链表长度，为链表排序做准备
{
	if (h->head == NULL)
		return 0;
	int count = 0;//初始化长度为0
	Node* p;
	p = h->head;
	while (p)//只要p不为空，表长加1，p指向下一个结点
	{
		count++;
		p = p->link;
	}
	return count;
}
void Sort(Headerlist* h)
{
	int i, j, temp;//用于交换两个结点中的值
	int n = length(h);//n作为表长
	Node* p;
	for (i = 0; i < n - 1; i++)//选择排序实现从小到大排序
	{
		p = h->head;
		for (j = 0; j < n-1; j++)
		{
			if (p->element > (p->link->element))
			{
				temp = p->element;
				p->element = p->link->element;
				p->link->element = temp;
			}
			p = p->link;
		}
	}
}
void main()
{
	int i,n,x;
	Headerlist list;
	Init(&list);
	printf("输入链表中元素个数：");
	scanf_s("%d",&n);
	for (i = 0; i < n; i++)
	{
		x = rand() % 20;//构建链表时给结点中元素赋0-19间的值
		Insert(&list, i-1, x);
	}
	printf("\n此链表为：");
	Output(&list);
	/*Sort(&list);
	printf("\n从小到大排序后链表为：");
	Output(&list);*/
	Reverse(&list);
	printf("\n逆置后的链表为：");
	Output(&list);
	Destroy(&list);
}