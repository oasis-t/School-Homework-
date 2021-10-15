#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node
{
	int element;
	struct node* link;
}Node;
typedef struct headerlist
{
	Node* head;
	int n;
}Headerlist;

int Init(Headerlist* h)
{
	h->head = (Node*)malloc(sizeof(Node));
	if (!h->head)
		return 0;
	h->head->link = NULL;
	h->n = 0;
	return 1;
}
int Insert(Headerlist* h, int i, int x)
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
int Output(Headerlist* h)
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
void SelectSort(Headerlist* h)
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
void InsertSort(Headerlist* L)
{
	Node* p, * q, * k;
	p = L->head->link;
	q = p->link;
	k = q;
	p->link = NULL;
	if (p->element <= q->element)
	{
		p->link = q;
		k = q->link;
		q->link = NULL;
		q = k;
	}
	else
	{
		L->head->link = q;
		k = q->link;
		q->link = p;
		q = k;
		p = L->head->link;
	}
	while (q != NULL)
	{
		while (1)
		{
			if (p->element > q->element && p == L->head->link)
			{
				L->head->link = q;
				k = q->link;
				q->link = p;
				p = q;
				q = k;
				break;
			}
			if (p->element < q->element && p->link == NULL)
			{
				p->link = q;
				k = q->link;
				q->link = NULL;
				p = L->head->link;
				q = k;
				break;
			}
			if (p->element < q->element && p->link->element > q->element)
			{
				k = q->link;
				q->link = p->link;
				p->link = q;
				p = L->head->link;
				q = k;
				break;
			}
			p = p->link;
		}
	}
}

int main()
{
	int i,n,x;
	Headerlist list;
	srand(time(NULL));
	Init(&list);
	printf("����������Ԫ�ظ�����");
	scanf_s("%d",&n);
	for (i = 0; i < n; i++)
	{
		x = rand() % 1000+1;//��������ʱ�������Ԫ�ظ�1-1000���ֵ
		Insert(&list, i-1, x);
	}
	printf("\n������Ϊ��");
	Output(&list);
	SelectSort(&list);
	printf("\n��ѡ�����������Ϊ��");
	Output(&list);
	/*
	InsertSort(&list);
	printf("\nֱ�Ӳ������������Ϊ��");
	Output(&list);
	*/
}