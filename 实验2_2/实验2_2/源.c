#include<stdio.h>
#include<malloc.h>
typedef struct btnode
{
	int element;
	struct btnode* lchild, * rchild;
}BTNode, * BinaryTree;
int countofleaf=0;
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
//遍历二叉树求结点个数
int TotalCount(BinaryTree T)
{
	if (!T)
		return 0;
	int lc=TotalCount(T->lchild);
	int rc=TotalCount(T->rchild);
	return 1 + lc + rc;
}
//递归求叶结点个数
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
//求树的高度
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
//交换二叉树所有左右子树
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
int main()//测试数据：第一组5 3 1 0 0 0 4 0 0第二组：2 4 6 0 0 3 0 0 7 0 1 0 0
{
	int non=0,height=0;//non对应结点个数，height对应树的高度
	BinaryTree T;
	T = NULL;
	T = PreCreateTree(T);//先序创建二叉树
	printf("先序遍历输出树中元素：");
	PreOrderPrint(T);
	printf("\n中序遍历输出树中元素：");
	InOrderPrint(T);
	printf("\n后序遍历输出树中元素：");
	PostOrderPrint(T);
	non = TotalCount(T);
	printf("\n此二叉树中结点个数为：%d",non);
	LeafCount(T);
	printf("\n此二叉树中叶结点个数为：%d",countofleaf);
	height = Height(T);
	printf("\n此二叉树的高度为：%d", height);
	T = Exchange(T);
	printf("\n中序遍历输出交换二叉树所有子树后的元素：");
	InOrderPrint(T);
	printf("\n");
	return 0;
}