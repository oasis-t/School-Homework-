#include<stdio.h>
#include<stdlib.h>
#define Maxsize 100000
typedef struct entry
{
    int key;
    int data;
}Entry;
typedef struct sl
{
    int n;
    Entry D[Maxsize];
}sl;
void InsertSort(sl* sl)
{
    int i, j;                                 //i标识待插入元素下标
    for (i = 1; i < sl->n; i++)
    {
        Entry insertItem = sl->D[i];     //标记每次第一位元素
        for (j = i - 1; j >= 0; j--)
        {
            //不断将有序序列中元素向后移动,为待插入元素空出一个位置
            if (insertItem.key < sl->D[j].key)
                sl->D[j + 1] = sl->D[j];
            else break;
        }
        sl->D[j + 1] = insertItem;          //待插入元素有序存放至有序序列中
    }
}
int main()
{
    sl sl;
    int i,k;
    scanf_s("%d%d", &sl.n,&k);//输入待排序元素的数量
    for (i = 0; i < sl.n; i++)
    {
        sl.D[i].key = rand() % 1000;//控制生成的随机数在1000以内
    }
    InsertSort(&sl);
    for (int j = 0; j < k; j++)
    {
        printf("%d ", sl.D[j]);
    }
}