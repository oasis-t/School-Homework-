#include<stdio.h>
#include<malloc.h>
typedef int Elemtype;
typedef int Status;
typedef struct seqlist
{
	int n;
	int maxlength;
	Elemtype* element;
}Seqlist;
Status Init(Seqlist* L, int msize)
{
	L->maxlength = msize;
	L->n = 0;
	L->element = (Elemtype*)malloc(sizeof(Elemtype)*msize); //动态生成一维数组空间
	if (!L->element)
		return 0;
	return 1;
}
Status Find(Seqlist* L, int i,Elemtype* x)
{
	if (i<0 || i>L->n - 1)  //判断下标i是否越界
		return 0;
	*x = L->element[i];//取出element[i]的值并通过x返回
	return 1;
}
Status Insert(Seqlist* L, int i, Elemtype x)
{
	int j;
	if (i<-1 || i>L->n - 1) //判断是否越界
		return 0;
	if (L->n == L->maxlength) //判断表中存储空间是否已满
		return 0;
	for (j = L->n - 1; j > i; j++)
		L->element[j + 1] = L->element[j];//从后往前逐步后移元素
	L->element[i+1] = x;        //存入新元素
	L->n++;          //表长加1
	return 1;
}
Status Delete(Seqlist* L, int i)
{
	int j;
	if (i<0 || i>L->n + 1)//判断是否越界
		return 0;
	if (!L->n)//顺序表是否为空
		return 0;
	for (j = i + 1; j< L->n; j++)
		L->element[j - 1] = L->element[j];//从后往前逐个前移元素
	L->n--;   //表长减1
	return 1;
}
Status Output(Seqlist* L)
{
	int i;
	if (L->n == 0)//判断是否为空
		return 0;
	for (i = 0; i <= L->n-1; i++)
		printf("%d ", L->element[i]);
	printf("\n");
	return 1;
}
void Destroy(Seqlist* L)
{
	L->n = 0;
	L->maxlength = 0;
	free(L->element);
}
void main()
{
	int i;
	Seqlist list;
	Init(&list, 10);
	for (i = 0; i < 10; i++)
		Insert(&list, i - 1, i);//for循环插入来构建顺序表
	printf("此顺序表中元素为：");
	Output(&list);
	Delete(&list, 0);
	printf("删除后的表中元素为：");
	Output(&list);
	Destroy(&list);
}