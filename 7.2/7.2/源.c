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
	if (!T)     //结点为空则申请动态空间
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
	printf("输入以0结尾的二叉树中元素：");
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

BSTree RecursionInsert(BSTree T, int element)  //递归向二叉搜索树中插入元素
{
	if (!T)
		T = InsertTree(T, element);  //
	else if (element < T->element)
		T->lchild = RecursionInsert(T->lchild, element);
	else if (element > T->element)
		T->rchild = RecursionInsert(T->rchild, element);
	else if (element == T->element)
		printf("元素已存在！\n");
	return T;
}
int main()
{
	int m;//需要插入的元素
	BSTree T;
	T = NULL;
	T = CreateTree(T);
	printf("中序遍历输出树中元素：");
	PrintBST(T);
	printf("\n输入需要插入的元素：");
	scanf_s("%d", &m);
	T = RecursionInsert(T, m);
	printf("插入元素后的树中元素为：");
	PrintBST(T);
	return 0;
}