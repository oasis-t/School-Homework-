#include<stdio.h>
#include<malloc.h>
typedef struct node
{
	int element;
	struct node* link;
}Node;

Node *Create()
{
	int m;
	Node* p=NULL,*q,*head;
	scanf_s("%d", &m);
	head = (Node*)malloc(sizeof(Node));
	q = head;
	head->element = m;
	head->link = NULL;
	while (m != 0)
	{
		p = (Node*)malloc(sizeof(Node));
		p->element = m;
		q->link = p;
		q = q->link;
		scanf_s("%d", &m);
	}
	p->link = NULL;
	return head;
}

void Print(Node *head)
{
	Node* p=head->link;
	while (p)
	{
		printf("%d ", p->element);
		p = p->link;
	}
	printf("\n");
}
/*
void Reverse(Node* head)
{
	Node* p=head->link, * q=head;
	head -> link = NULL;
	while (p)
	{
		q = p;
		p = p->link;
		q->link = head->link;
		head->link = q;
	}
}*/

Node* Merge(Node* node1, Node* node2)
{
	Node * p1=NULL, * p2=NULL;
	if (!node1 || !node2)
		return NULL;
	if (node1->element >= node2->element)
	{
		p1 = node1;
		node1 = node1->link;
		node2 = node2->link;
	}
	else
	{
		p1 = node2;
		node2 = node2->link;
		node1 = node1->link;
	}
	p2 = p1;
	do
	{
		if (node1->element >= node2->element)
		{
			p2->link = node1;
			p2 = p2->link;
			node1 = node1->link;
		}
		else
		{
			p2->link = node2;
			p2 = p2->link;
			node2 = node2->link;
		}
	}while (node1 && node2);
	if (!node1)
		p2->link = node2;
	else
		p2->link = node1;
	Print(p1);
	return p1;
}
int main()
{
	Node *node1,*node2;
	node1 = Create();
	node2 = Create();
	Print(node1);
	//Reverse(node1);
	Print(node2);
	Merge(node1, node2);
	return 0;
}