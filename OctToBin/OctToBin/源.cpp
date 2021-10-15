#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;
typedef struct
{
	ElemType* base;
	ElemType* top;
	int stacksize;
}SqStack;

void main()
{
	void InitStack(SqStack & S);//��ʼ����ջ
	int StackEmpty(SqStack S);//�п�
	void GetTop(SqStack S, ElemType & e);//���ջ��Ԫ��
	void push(SqStack & S, ElemType e);//��ջ
	void pop(SqStack & S, ElemType & e);//��ջ
	void convert(SqStack & S, int N, int n);//ʮ����תN����
	unsigned n, N;//Ҫת���ɵĽ�������Ҫת������
	SqStack S;
	printf("����Ҫת����ʮ��������Ҫת��Ϊ�Ľ�����:\n");
	scanf_s("%d%d", &N, &n);
	printf("%dת��Ϊ%d���ƺ�Ϊ:\n", N, n);
	convert(S, N, n);
}

void InitStack(SqStack* S)
{
	S->base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}//��ʼ����ջ

int StackEmpty(SqStack* S)
{
	if (S->top == 0)
		return 1;
	else
		return 0;
}//�ж�ջ�Ƿ�Ϊ��

void GetTop(SqStack S, int& e)
{//���ջ��Ԫ��
	e = *(S.top - 1);
}

void Push(SqStack* S, ElemType e)
{
	if (S->top - S->base >= S->stacksize)
	{
		S->base = (ElemType*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(ElemType));
		S->top = S->base + S->stacksize;
		S->stacksize = S->stacksize + STACKINCREMENT;
		*(S->top) = e;
		S->top++;
	}
}//��ջ

void Pop(SqStack* S, ElemType& e)
{
	if (S->top == S->base)
	{
		return;
	}
	S->top--;
	e = *S->top;
}//��ջ
void convert(SqStack& S, int N, int n)
{
	do
	{
		Push(&S, N % n);
		N /= n;
	} while (N != 0);
	ElemType e;
	while (!StackEmpty(&S))
	{
		Pop(&S, e);
		if (e > 9)//ʮ������
		{
			e = e + 55;
			printf("%d", e);
		}
		else
			printf("%d", e);
	}
	printf("\n");
}
