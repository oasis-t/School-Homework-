#include<stdio.h>
#include<malloc.h>
typedef int Elemtype;
typedef int Status;
typedef struct seqlist
{
	int n;
	int maxlength;
	Elemtype* element;
}Seqlist;
Status Init(Seqlist* L, int msize)
{
	L->maxlength = msize;
	L->n = 0;
	L->element = (Elemtype*)malloc(sizeof(Elemtype)*msize); //��̬����һά����ռ�
	if (!L->element)
		return 0;
	return 1;
}
Status Find(Seqlist* L, int i,Elemtype* x)
{
	if (i<0 || i>L->n - 1)  //�ж��±�i�Ƿ�Խ��
		return 0;
	*x = L->element[i];//ȡ��element[i]��ֵ��ͨ��x����
	return 1;
}
Status Insert(Seqlist* L, int i, Elemtype x)
{
	int j;
	if (i<-1 || i>L->n - 1) //�ж��Ƿ�Խ��
		return 0;
	if (L->n == L->maxlength) //�жϱ��д洢�ռ��Ƿ�����
		return 0;
	for (j = L->n - 1; j > i; j++)
		L->element[j + 1] = L->element[j];//�Ӻ���ǰ�𲽺���Ԫ��
	L->element[i+1] = x;        //������Ԫ��
	L->n++;          //����1
	return 1;
}
Status Delete(Seqlist* L, int i)
{
	int j;
	if (i<0 || i>L->n + 1)//�ж��Ƿ�Խ��
		return 0;
	if (!L->n)//˳����Ƿ�Ϊ��
		return 0;
	for (j = i + 1; j< L->n; j++)
		L->element[j - 1] = L->element[j];//�Ӻ���ǰ���ǰ��Ԫ��
	L->n--;   //����1
	return 1;
}
Status Output(Seqlist* L)
{
	int i;
	if (L->n == 0)//�ж��Ƿ�Ϊ��
		return 0;
	for (i = 0; i <= L->n-1; i++)
		printf("%d ", L->element[i]);
	printf("\n");
	return 1;
}
void Destroy(Seqlist* L)
{
	L->n = 0;
	L->maxlength = 0;
	free(L->element);
}
void main()
{
	int i;
	Seqlist list;
	Init(&list, 10);
	for (i = 0; i < 10; i++)
		Insert(&list, i - 1, i);//forѭ������������˳���
	printf("��˳�����Ԫ��Ϊ��");
	Output(&list);
	Delete(&list, 0);
	printf("ɾ����ı���Ԫ��Ϊ��");
	Output(&list);
	Destroy(&list);
}