#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int element;
	struct node* link;
}Node;
static int a = 0;
int x = 0;
int Retrieve(Node* p)
{
	
	if (p == NULL)
		return a;
	if (p->element == x)
		return a;
	else
	{
		p = p->link;
		a++;
		Retrieve(p);
	}
}
int main()
{
	int n,i,m=0;
	Node* p,*head, * q;
	printf("输入链表中元素个数：");
	scanf_s("%d", &n);
	p = (Node*)malloc(sizeof(Node));
	head = p;
	q = p;
	for (i = 0; i < n ; i++)
	{
		p = (Node*)malloc(sizeof(Node));
		scanf_s("%d", &p->element);
		q->link = p;
		q = p;
	}
	p->link = NULL;
	printf("输入要查找的元素：");
	scanf_s("%d",&x);
	m = Retrieve(head);
	if (m == n + 1)
		printf("Notpresent!");
	else
	{
		printf("此元素在第%d个", m);
	}
	return 0;
}