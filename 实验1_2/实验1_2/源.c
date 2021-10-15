#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int Elemtype;
typedef int Status;
typedef struct node
{
	Elemtype element;//������
	struct node* link;//ָ����
}Node;
typedef struct headerlist
{
	Node* head;
	int n;
}Headerlist;
Status Init(Headerlist* h)
{
	h->head = (Node*)malloc(sizeof(Node));//���ɱ�ͷ���
	if (!h->head)
		return 0;
	h->head->link = NULL;//���õ�����Ϊ��
	h->n = 0;
	return 1;
}
Status Insert(Headerlist* h, int i, Elemtype x)
{
	Node* p, * q;
	int j;
	if (i<-1 || i>h->n - 1)//�ж��Ƿ�Խ��
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
	if (!h->n)//�ж��Ƿ�Ϊ��
		return 0;
	if (i<0 || i>h->n - 1)//�ж��Ƿ�Խ��
		return 0;
	q = h->head;
	for (j = 0; j < i; j++)
		q = q->link;
	p = q->link;
	q->link = p->link;//�ӵ�������ɾ��p��ָ���
	free(p);      //�ͷ�p��ָ���Ŀռ�
	h->n--;
	return 1;
}
Status Find(Headerlist* h,int i,Elemtype*x)
{
	Node* p;
	int j;
	if (i<0 || i>h->n-1)//�ж��Ƿ�Խ��
		return 0;
	p = h->head;
	for (j = 0; j < i; j++)
		p = p->link;//��ͷ��㿪ʼ����
	*x = p->element;//ͨ��x����ֵ
	return 1;
}
Status Output(Headerlist* h)
{
	Node* p;
	if (!h->n)//�ж��Ƿ�Ϊ��
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
		p = h->head->link;//������̽���ַ��ֹ����
		free(h->head);//�ͷ�ͷ�����ָ�ռ�
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
	printf("������Ϊ��");
	Output(&list);
	Delete(&list,0);
	printf("\nɾ��������Ϊ��");
	Output(&list);
	Find(&list, 2, &x);
	printf("���ҵ�ֵΪ��");
	printf("%d", x);
	Destroy(&list);
}