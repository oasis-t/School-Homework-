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
    int i, j;                                 //i��ʶ������Ԫ���±�
    for (i = 1; i < sl->n; i++)
    {
        Entry insertItem = sl->D[i];     //���ÿ�ε�һλԪ��
        for (j = i - 1; j >= 0; j--)
        {
            //���Ͻ�����������Ԫ������ƶ�,Ϊ������Ԫ�ؿճ�һ��λ��
            if (insertItem.key < sl->D[j].key)
                sl->D[j + 1] = sl->D[j];
            else break;
        }
        sl->D[j + 1] = insertItem;          //������Ԫ��������������������
    }
}
int main()
{
    sl sl;
    int i,k;
    scanf_s("%d%d", &sl.n,&k);//���������Ԫ�ص�����
    for (i = 0; i < sl.n; i++)
    {
        sl.D[i].key = rand() % 1000;//�������ɵ��������1000����
    }
    InsertSort(&sl);
    for (int j = 0; j < k; j++)
    {
        printf("%d ", sl.D[j]);
    }
}