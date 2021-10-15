#include<stdio.h>
#include<stdlib.h>

#define maxsize 100
typedef struct hfmTNode  //哈夫曼树结点
{
	char element;
	int w;             //权值
	struct hfmTNode* lChild;
	struct hfmTNode* rChild;
	int HFMC;
}HFMTNode;
typedef struct binarytree
{
	HFMTNode* root;
}BinaryTree;
typedef struct priorityQueue  //优先权队列结构体
{
	HFMTNode** element;
	int maxSize;
	int n;
}PriorityQueue;

/*创建优先权队列*/
PriorityQueue CreatePQ(PriorityQueue PQ, int m)
{
	PQ.element = (HFMTNode**)malloc(sizeof(HFMTNode*) * m);
	PQ.maxSize = m;
	PQ.n = 0;
	return PQ;
}
/*将创建的二叉树插入优先权队列*/
PriorityQueue Append(PriorityQueue PQ, HFMTNode* x)
{
	int i, j;
	if (PQ.n == PQ.maxSize || !x) return PQ;
	else if (PQ.n == 0) PQ.element[PQ.n] = x;
	else if (x->w <= PQ.element[PQ.n - 1]->w)
		PQ.element[PQ.n] = x;
	else for (i = 0; i < PQ.n; i++)
		if (x->w > PQ.element[i]->w)
		{
			for (j = PQ.n; j > i; j--)
				PQ.element[j] = PQ.element[j - 1];
			PQ.element[i] = x;
			break;
		}
	PQ.n++;
	return PQ;
}
/*从PQ中取出权值最小的存入x*/
HFMTNode* Serve(PriorityQueue PQ, HFMTNode* x)
{
	x = (HFMTNode*)malloc(sizeof(HFMTNode));
	x = PQ.element[PQ.n - 1];
	PQ.element[PQ.n - 1] = NULL;
	return x;
}
HFMTNode* MakeTree(HFMTNode* b, int w, char element, HFMTNode* l, HFMTNode* r)
{
	b = (HFMTNode*)malloc(sizeof(HFMTNode));
	b->element = element;
	b->w = w;
	b->lChild = l;
	b->rChild = r;
	b->HFMC = 0;
	return b;
}
/*创建哈夫曼树*/
BinaryTree CreateHFMTree(int m)
{
	int i;
	PriorityQueue PQ = { NULL,0,0 }; 
	BinaryTree x = { NULL }, y = { NULL }, z = { NULL };  
	PQ = CreatePQ(PQ, m);
	for (i = 0; i < m; i++)
	{
		char e = ' ';
		int w = 0;
		getchar();
		printf("第%d个数据(请输入小写字母): \n", i + 1);
		while (1)
		{
			scanf_s("%c", &e, sizeof(e));
			if (e > 'z' || e < 'a')
				printf("输入错误,请重新输入。\n");
			else break;
		}
		printf("第%d个数据的权值: \n", i + 1);
		scanf_s("%d", &w);
		x.root = MakeTree(x.root, w, e, NULL, NULL);
		PQ = Append(PQ, x.root);
	}
	while (PQ.n > 1)
	{
		x.root = Serve(PQ, x.root);
		PQ.n--;
		y.root = Serve(PQ, y.root);
		PQ.n--;;
		if (x.root->w > y.root->w)
			z.root = MakeTree(z.root, x.root->w + y.root->w, NULL, y.root, x.root);
		else
			z.root = MakeTree(z.root, x.root->w + y.root->w, NULL, x.root, y.root);
		Append(PQ, z.root);
		PQ.n++;
	}
	return z;  //z为所创建完成的哈夫曼树
}
void PreOrder(HFMTNode* t)
{
	if (!t)
		return;
	if (t->lChild)                      //左子树为0，右子树为1。编码
		t->lChild->HFMC = 0;
	if (t->rChild)
		t->rChild->HFMC = 1;

	printf("%d ", t->w); //访问根节点权值
	PreOrder(t->lChild);  //访问左子树
	PreOrder(t->rChild);  //访问右子树
}

void PreOrderTree(BinaryTree* bt)  //先序遍历 
{
	PreOrder(bt->root);
}

void Solve(BinaryTree* bt, int a[], int n)
{
	int i;
	HFMTNode* p;
	p = bt->root;           //存储根节点地址
	for (i = 0; i < n; i++)
	{
		if (a[i] == 0)
			p = p->lChild;
		if (a[i] == 1)
			p = p->rChild;
		if (p->lChild == NULL && p->rChild == NULL)
		{
			printf("%c ", p->element);
			p = bt->root;
		}
	}
}
int main()
{
	int m, n, i;// m为输入权值的数量 ,n为解码时数组位数
	int a[maxsize];
	BinaryTree T;
	printf("请输入哈夫曼树权值数量：");
	scanf_s("%d", &m);
	T = CreateHFMTree(m);
	printf("先序遍历输出树中元素：");
	PreOrderTree(&T);   //先序遍历输出哈夫曼树
	printf("\n请输入码文位数：");
	scanf_s("%d", &n);
	printf("请输入码文：");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &a[i]);
	}
	printf("码文解码之后为：");
	Solve(&T, a, n);
	return 0;
}