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
	printf("����������Ԫ�ظ�����");
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
	printf("����Ҫ���ҵ�Ԫ�أ�");
	scanf_s("%d",&x);
	m = Retrieve(head);
	if (m == n + 1)
		printf("Notpresent!");
	else
	{
		printf("��Ԫ���ڵ�%d��", m);
	}
	return 0;
}