#include<stdio.h>
#include<stdlib.h>

#define maxsize 100
typedef struct hfmTNode  //�����������
{
	char element;
	int w;             //Ȩֵ
	struct hfmTNode* lChild;
	struct hfmTNode* rChild;
	int HFMC;
}HFMTNode;
typedef struct binarytree
{
	HFMTNode* root;
}BinaryTree;
typedef struct priorityQueue  //����Ȩ���нṹ��
{
	HFMTNode** element;
	int maxSize;
	int n;
}PriorityQueue;

/*��������Ȩ����*/
PriorityQueue CreatePQ(PriorityQueue PQ, int m)
{
	PQ.element = (HFMTNode**)malloc(sizeof(HFMTNode*) * m);
	PQ.maxSize = m;
	PQ.n = 0;
	return PQ;
}
/*�������Ķ�������������Ȩ����*/
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
/*��PQ��ȡ��Ȩֵ��С�Ĵ���x*/
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
/*������������*/
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
		printf("��%d������(������Сд��ĸ): \n", i + 1);
		while (1)
		{
			scanf_s("%c", &e, sizeof(e));
			if (e > 'z' || e < 'a')
				printf("�������,���������롣\n");
			else break;
		}
		printf("��%d�����ݵ�Ȩֵ: \n", i + 1);
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
	return z;  //zΪ��������ɵĹ�������
}
void PreOrder(HFMTNode* t)
{
	if (!t)
		return;
	if (t->lChild)                      //������Ϊ0��������Ϊ1������
		t->lChild->HFMC = 0;
	if (t->rChild)
		t->rChild->HFMC = 1;

	printf("%d ", t->w); //���ʸ��ڵ�Ȩֵ
	PreOrder(t->lChild);  //����������
	PreOrder(t->rChild);  //����������
}

void PreOrderTree(BinaryTree* bt)  //������� 
{
	PreOrder(bt->root);
}

void Solve(BinaryTree* bt, int a[], int n)
{
	int i;
	HFMTNode* p;
	p = bt->root;           //�洢���ڵ��ַ
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
	int m, n, i;// mΪ����Ȩֵ������ ,nΪ����ʱ����λ��
	int a[maxsize];
	BinaryTree T;
	printf("�������������Ȩֵ������");
	scanf_s("%d", &m);
	T = CreateHFMTree(m);
	printf("��������������Ԫ�أ�");
	PreOrderTree(&T);   //������������������
	printf("\n����������λ����");
	scanf_s("%d", &n);
	printf("���������ģ�");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &a[i]);
	}
	printf("���Ľ���֮��Ϊ��");
	Solve(&T, a, n);
	return 0;
}