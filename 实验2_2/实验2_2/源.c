#include<stdio.h>
#include<malloc.h>
typedef struct btnode
{
	int element;
	struct btnode* lchild, * rchild;
}BTNode, * BinaryTree;
int countofleaf=0;
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
//�����������������
int TotalCount(BinaryTree T)
{
	if (!T)
		return 0;
	int lc=TotalCount(T->lchild);
	int rc=TotalCount(T->rchild);
	return 1 + lc + rc;
}
//�ݹ���Ҷ������
void LeafCount(BinaryTree T)
{
	if (T == NULL)
		return;
	if (T->lchild == NULL && T->rchild == NULL)
		countofleaf++;
	LeafCount(T->lchild);
	LeafCount(T->rchild);
	return;
}
//�����ĸ߶�
static int a = 0;
int Height(BinaryTree T)
{
	if (!T)
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		a++;
	int LH = Height(T->lchild);
	int RH = Height(T->rchild);
	if (LH >= RH)
		return 1+LH;
	return 1+RH;
}
//����������������������
BinaryTree Exchange(BinaryTree T)
{
	if (!T)return NULL;
	Exchange(T->lchild);
	Exchange(T->rchild);
	BinaryTree* p=T->lchild, * q=T->rchild;
	T->lchild = q;
	T->rchild = p;
	return T;
}
int main()//�������ݣ���һ��5 3 1 0 0 0 4 0 0�ڶ��飺2 4 6 0 0 3 0 0 7 0 1 0 0
{
	int non=0,height=0;//non��Ӧ��������height��Ӧ���ĸ߶�
	BinaryTree T;
	T = NULL;
	T = PreCreateTree(T);//���򴴽�������
	printf("��������������Ԫ�أ�");
	PreOrderPrint(T);
	printf("\n��������������Ԫ�أ�");
	InOrderPrint(T);
	printf("\n��������������Ԫ�أ�");
	PostOrderPrint(T);
	non = TotalCount(T);
	printf("\n�˶������н�����Ϊ��%d",non);
	LeafCount(T);
	printf("\n�˶�������Ҷ������Ϊ��%d",countofleaf);
	height = Height(T);
	printf("\n�˶������ĸ߶�Ϊ��%d", height);
	T = Exchange(T);
	printf("\n�������������������������������Ԫ�أ�");
	InOrderPrint(T);
	printf("\n");
	return 0;
}