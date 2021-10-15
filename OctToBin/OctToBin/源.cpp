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
	void InitStack(SqStack & S);//初始化空栈
	int StackEmpty(SqStack S);//判空
	void GetTop(SqStack S, ElemType & e);//获得栈顶元素
	void push(SqStack & S, ElemType e);//进栈
	void pop(SqStack & S, ElemType & e);//出栈
	void convert(SqStack & S, int N, int n);//十进制转N进制
	unsigned n, N;//要转换成的进制数和要转换的数
	SqStack S;
	printf("输入要转换的十进制数和要转换为的进制数:\n");
	scanf_s("%d%d", &N, &n);
	printf("%d转换为%d进制后为:\n", N, n);
	convert(S, N, n);
}

void InitStack(SqStack* S)
{
	S->base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
}//初始化空栈

int StackEmpty(SqStack* S)
{
	if (S->top == 0)
		return 1;
	else
		return 0;
}//判断栈是否为空

void GetTop(SqStack S, int& e)
{//获得栈顶元素
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
}//进栈

void Pop(SqStack* S, ElemType& e)
{
	if (S->top == S->base)
	{
		return;
	}
	S->top--;
	e = *S->top;
}//出栈
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
		if (e > 9)//十六进制
		{
			e = e + 55;
			printf("%d", e);
		}
		else
			printf("%d", e);
	}
	printf("\n");
}
