#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct seqlist
{
	int n;
	int maxlength;
	Elemtype* element;
}Seqlist;
void Init(Seqlist* L, int msize)
{
	int i,m;
	L->maxlength = msize;
	L->n = 0;
	L->element = (Elemtype*)malloc(sizeof(Elemtype) * msize);
	printf("����˳�����Ԫ�ظ�����");
	scanf_s("%d", &m);
	printf("����Ҫ���õ�Ԫ��\n");
	for (i = 0; i<m; i++)
	{
		scanf_s("%d", &L->element[i]);
		L->n++;
	}
}
void output(Seqlist *L)
{
	int i;
	for (i = 0; i < L->n; i++)
	{
		printf("%d ",L->element[i]);
	}
	printf("\n");
}
void Reverse(Seqlist* L)
{
	Elemtype* p, temp;
	p = L->element;
	for (int i = 0; i<(L->n)/2; i++)
	{
		temp = *(L->element+i);
		*(L->element + i) = *(L->element + L->n - i - 1);
		*(L->element + L->n - i - 1) = temp;
	}
}
int main()
{
	Seqlist list;
	Init(&list, 20);
	printf("����ǰ��");
	output(&list);
	Reverse(&list);
	printf("���ú�");
	output(&list);
	return 0;
}
