#include<stdio.h>
#include<malloc.h>
typedef struct btnode
{
	int element;
	struct btnode* lchild, * rchild;
}BTNode,*BinaryTree;
//先序创建二叉树
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
//先序遍历输出
void PreOrderPrint(BinaryTree T)
{
	if (!T)
		return;
	printf("%d ", T->element);
	PreOrderPrint(T->lchild);
	PreOrderPrint(T->rchild);
}
//中序遍历输出
void InOrderPrint(BinaryTree T)
{
	if (!T)
		return;
	InOrderPrint(T->lchild);
	printf("%d ", T->element);
	InOrderPrint(T->rchild);
}
//后序遍历输出
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
	printf("先序遍历输出树中元素：");
	PreOrderPrint(T);
	printf("\n中序遍历输出树中元素：");
	InOrderPrint(T);
	printf("\n后序遍历输出树中元素：");
	PostOrderPrint(T);
	return 0;
}