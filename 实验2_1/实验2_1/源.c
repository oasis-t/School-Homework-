#include<stdio.h>
#include<malloc.h>
typedef struct btnode
{
	int element;
	struct btnode* lchild, * rchild;
}BTNode,*BinaryTree;
//���򴴽�������
BinaryTree PreCreateTree(BinaryTree T)  
{
	int m;
	scanf_s("%d", &m);
	if (m == 0)
		T = NULL;
	else
	{
		T = (BinaryTree)malloc(sizeof(BTNode));
		T->element = m;
		T->lchild = PreCreateTree(T->lchild);
		T->rchild = PreCreateTree(T->rchild);
	}
	return T;
}
//����������
void PreOrderPrint(BinaryTree T)
{
	if (!T)
		return;
	printf("%d ", T->element);
	PreOrderPrint(T->lchild);
	PreOrderPrint(T->rchild);
}
//����������
void InOrderPrint(BinaryTree T)
{
	if (!T)
		return;
	InOrderPrint(T->lchild);
	printf("%d ", T->element);
	InOrderPrint(T->rchild);
}
//����������
void PostOrderPrint(BinaryTree T)
{
	if (!T)
		return;
	PostOrderPrint(T->lchild);
	PostOrderPrint(T->rchild);
	printf("%d ", T->element);
}
int main()
{
	BinaryTree T;
	T = NULL;
	T = PreCreateTree(T);
	printf("��������������Ԫ�أ�");
	PreOrderPrint(T);
	printf("\n��������������Ԫ�أ�");
	InOrderPrint(T);
	printf("\n��������������Ԫ�أ�");
	PostOrderPrint(T);
	return 0;
}