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
	while (p)//ֻҪp��Ϊ�գ�qָ��p��p����һλ����q��h->head����
	{
		q = p;
		p = p->link;
		q->link = h->head->link;
		h->head->link = q;
	}
}
int length(Headerlist* h)//�������ȣ�Ϊ����������׼��
{
	if (h->head == NULL)
		return 0;
	int count = 0;//��ʼ������Ϊ0
	Node* p;
	p = h->head;
	while (p)//ֻҪp��Ϊ�գ�����1��pָ����һ�����
	{
		count++;
		p = p->link;
	}
	return count;
}
void Sort(Headerlist* h)
{
	int i, j, temp;//���ڽ�����������е�ֵ
	int n = length(h);//n��Ϊ��
	Node* p;
	for (i = 0; i < n - 1; i++)//ѡ������ʵ�ִ�С��������
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
	printf("����������Ԫ�ظ�����");
	scanf_s("%d",&n);
	for (i = 0; i < n; i++)
	{
		x = rand() % 20;//��������ʱ�������Ԫ�ظ�0-19���ֵ
		Insert(&list, i-1, x);
	}
	printf("\n������Ϊ��");
	Output(&list);
	/*Sort(&list);
	printf("\n��С�������������Ϊ��");
	Output(&list);*/
	Reverse(&list);
	printf("\n���ú������Ϊ��");
	Output(&list);
	Destroy(&list);
}