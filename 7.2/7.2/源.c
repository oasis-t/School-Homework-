#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct bstnode
{
	int element;
	struct bstnode* lchild, * rchild;
}BSTNode, * BSTree;

BSTree InsertTree(BSTree T, int element)
{
	if (!T)     //���Ϊ�������붯̬�ռ�
	{
		T = malloc(sizeof(BSTNode));
		T->element = element;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else if (T->element < element)
	{
		T->rchild = InsertTree(T->rchild, element);
	}
	else if (T->element > element)
	{
		T->lchild = InsertTree(T->lchild, element);
	}
	return T;
}

BSTree CreateTree(BSTree T)
{
	int element;
	printf("������0��β�Ķ�������Ԫ�أ�");
	scanf_s("%d", &element);
	while (element != 0)
	{
		T = InsertTree(T, element);
		scanf_s("%d", &element);
	}
	return T;
}

void PrintBST(BSTree T)
{
	if (!T)
		return;
	PrintBST(T->lchild);
	printf("%d ", T->element);
	PrintBST(T->rchild);
}

BSTree RecursionInsert(BSTree T, int element)  //�ݹ�������������в���Ԫ��
{
	if (!T)
		T = InsertTree(T, element);  //
	else if (element < T->element)
		T->lchild = RecursionInsert(T->lchild, element);
	else if (element > T->element)
		T->rchild = RecursionInsert(T->rchild, element);
	else if (element == T->element)
		printf("Ԫ���Ѵ��ڣ�\n");
	return T;
}
int main()
{
	int m;//��Ҫ�����Ԫ��
	BSTree T;
	T = NULL;
	T = CreateTree(T);
	printf("��������������Ԫ�أ�");
	PrintBST(T);
	printf("\n������Ҫ�����Ԫ�أ�");
	scanf_s("%d", &m);
	T = RecursionInsert(T, m);
	printf("����Ԫ�غ������Ԫ��Ϊ��");
	PrintBST(T);
	return 0;
}