/*
#include<stdio.h>
typedef int Elemtype;
typedef struct node
{
	Elemtype data;
	struct node* link;
}Node;
Node *create()
{
	Node* head, * p, * q;
	head = (Node*)malloc(sizeof(Node));
	head->link = NULL;
	p = head;
	q = head;
	printf("输入链表中元素，以‘#’结束：");
	char ch = getchar();
	while (ch != '#')
	{
		p = (Node*)malloc(sizeof(Node));
		p->data = ch;
		q->link = p;
		q = q->link;
		ch = getchar();
	}
	q->link = NULL;
	return head;
}
void Output(Node *m)
{
	m = m->link;
	while (m!= NULL)
	{
		printf("%c ", m->data);
		m = m->link;
	}
}
void Reverse(Node* head)
{
	Node * q, * p;
	p = head->link;
	head->link = NULL;
	while (p != NULL)
	{
		q = p; 
		p = p->link;
		q->link = head->link;
		head->link = q;
	}
}
int main()
{
	Node *node;
	node = create();
	printf("链表元素为:");
	Output(node);
	Reverse(node);
	printf("\n逆置后链表元素为：");
	Output(node);
	return 0;
}
*/


#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
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
	if (i<-1 || i>h->n - 1)
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
void Reverse(Headerlist* h)
{
	Node* p, * q;
	p = h->head->link;
	h->head->link = NULL;
	while (p)
	{
		q = p;
		p = p->link;
		q->link = h->head->link;
		h->head->link = q;
	}
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
void main()
{
	int i;
	Headerlist list;
	Init(&list);
	for (i = 0; i < 9; i++)
		Insert(&list, i - 1, i);
	printf("此链表为：");
	Output(&list);
	Reverse(&list);
	printf("\n逆置后的链表为：");
	Output(&list);
	Destroy(&list);
}