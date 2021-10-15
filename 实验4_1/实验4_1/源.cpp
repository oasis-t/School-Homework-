#include<stdio.h>
#include<windows.h>
#include<time.h>
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


//��ѡ������
int FindMin(sl sl, int startIndex)
{
    int i, minIndex = startIndex;
    for (i = startIndex + 1; i < sl.n; i++)
    {
        if (sl.D[i].key < sl.D[minIndex].key)
            minIndex = i;
    }
    return minIndex;
}
void Swap(Entry* D, int i, int j)
{
    Entry temp;
    if (i == j)return;
    temp = *(D + i);
    *(D + i) = *(D + j);
    *(D + j) = temp;
}
void SelectSort(sl* sl)
{
    int minIndex, startIndex = 0;
    while (startIndex < sl->n - 1)
    {
        minIndex = FindMin(*sl, startIndex);
        Swap(sl->D, startIndex, minIndex);
        startIndex++;
    }
}


//ֱ�Ӳ�������
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


//ð������
void BubbleSort(sl* sl)
{
    int i, j;                    //i��ʶÿ������Χ���һ��Ԫ���±�,ÿ������Ԫ���±귶Χ��0~i
    for (i = sl->n - 1; i > 0; i--) 
    {
        BOOL isSwap = FALSE;    //�̲��������,Ӧ�÷ŵ��ڶ���ѭ��ǰ
        for (j = 0; j < i; j++) 
        {
            if (sl->D[j].key > sl->D[j + 1].key) 
            {
                Swap(sl->D, j,j+1);
                isSwap = TRUE;
            }
        }
        if (!isSwap) break;     //�����������û�з���Ԫ�ؽ���,�������
    }
}


//���л��ַ���
int Partition(sl* sl, int low, int high) 
{
    int i = low, j = high + 1;
    Entry pivot = sl->D[low];                 //pivot�Ƿָ�Ԫ��
    do 
    {
        do i++;
        while (sl->D[i].key < pivot.key);      //iǰ��
        do j--;
        while (sl->D[j].key > pivot.key);      //jǰ��
        if (i < j) Swap(sl->D, i,j);
    } while (i < j);
    Swap(sl->D,low, j);
    return j;                                   //��ʱj�Ƿָ�Ԫ���±�
}
//��������
void QuickSort(sl* sl, int low, int high) 
{   //��������ĵݹ麯��
    int k;
    if (low < high)
    {                            //��ǰ�������������ٰ���2��Ԫ��
        k = Partition(sl, low, high);
        QuickSort(sl, low, k - 1);
        QuickSort(sl, k + 1, high);
    }
}
//��������
void QuickSort(sl* sl) 
{                   //���������㷨�������ú���
    QuickSort(sl, 0, sl->n - 1);
}


//������·�ϲ�������n1��n2�����������г���,low�ǵ�һ�������е�һ��Ԫ���±�
void Merge(sl* sl, Entry* temp, int low, int n1, int n2) 
{
    int i = low, j = low + n1; //i,j��ʼʱ�ֱ�ָ���������еĵ�һ��Ԫ��
    while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1) 
    {
        if (sl->D[i].key <= sl->D[j].key)
            *temp++ = sl->D[i++];
        else *temp++ = sl->D[j++];
    }
    while (i <= low + n1 - 1)
        *temp++ = sl->D[i++];  //ʣ��Ԫ��ֱ�ӿ�����temp
    while (j <= low + n1 + n2 - 1)
        *temp++ = sl->D[j++];  //ʣ��Ԫ��ֱ�ӿ�����temp
}
//��·�ϲ������㷨
void MergeSort(sl* sl)
{
    Entry temp[Maxsize];
    int low, n1, n2, i, size = 1;
    while (size < sl->n) 
    {
        low = 0;      //low��һ�Դ��ϲ������е�һ�����еĵ�һ��Ԫ���±�
        while (low + size < sl->n)
        {
            //low+size < sl->n˵�����ٴ���������������Ҫ�ϲ�
            n1 = size;
            if (low + size * 2 < sl->n)
                n2 = size;  //����ڶ������г���
            else n2 = sl->n - low - size;
            Merge(sl, temp, low, n1, n2);
            low += n1 + n2;  //ȷ����һ�Դ��ϲ������е�һ�����еĵ�һ��Ԫ���±�
        }
        for (i = 0; i < sl->n; i++) 
        {
            sl->D[i] = temp[i];  //����һ�˺ϲ�������
        }
        size *= 2;  //�����г��ȷ���
    }
}
//���µ���
void AdjustDown(Entry* heap, int current, int border)
{
    int p = current;
    int minChild;
    int temp;
    while (2 * p + 1 <= border)
    {
        if ((2 * p + 2 <= border) && (heap[2 * p + 1].key > heap[2 * p + 2].key))
            minChild = 2 * p + 2;    //�Һ��Ӵ��ڣ��ҽ�С����minChildָ��p���Һ���
        else
            minChild = 2 * p + 1;  //�Һ��Ӳ����ڻ�ϴ���minChildָ��p������
        if (heap[p].key <= heap[minChild].key)
            break;
        else
        {
            temp = heap[p].key;
            heap[p].key = heap[minChild].key;
            heap[minChild].key = temp;
            p = minChild;
        }
    }
}
//������
void HeapSort(sl* sl)                                                 
{
    int i;
    for (i = (sl->n - 2) / 2; i >= 0; i--)
        AdjustDown(sl->D, i, sl->n - 1);
    for (i = sl->n - 1; i > 0; i--)  //iָ��ǰ�ѵĶѵ�Ԫ��
    {
        Swap(sl->D, 0, i);       //�����ѵ���Ѷ�Ԫ��
        AdjustDown(sl->D, 0, i - 1);
    }
}
//���������
void randint(int n)
{
    int i, j;
    FILE* fp = NULL;
    srand(time(NULL));  //�������
    fopen_s(&fp,"C:\\Users\\ʱ��\\source\\repos.txt", "w");
    for (i = 0; i < n; i++)     //���������
    {
        j = rand() % 200000;
        fprintf(fp, "%d\t", j);
    }
    fclose(fp);
}
//���������˳���ֵ
void read(sl* sl) 
{
    int i;
    FILE* fp;
    fopen_s(&fp,"C:\\Users\\ʱ��\\source\\repos.txt", "r");
    for (i = 0; i < sl->n; i++)
    {
        fscanf_s(fp, "%d", &sl->D[i].key);
    }
    fclose(fp);
}
int main()
{
    sl sl;
    int i;
    scanf_s("%d", &sl.n);//���������Ԫ�ص�����
    randint(sl.n);
    read(&sl);
    for (i = 0; i < sl.n; i++)
    {
        sl.D[i].key = rand()%1000;//�������ɵ��������1000����
    }
    LARGE_INTEGER start_time, end_time;
    double dqFreq;
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    QueryPerformanceCounter(&start_time);

    //SelectSort(&sl);              //��ѡ������
    //InsertSort (&sl);            //ֱ�Ӳ�������
    //BubbleSort (&sl);             //ð������
    // QuickSort (&sl);           //��������
    //MergeSort (&sl);              //��·�ϲ�����
    HeapSort (&sl);              //������

    QueryPerformanceCounter(&end_time);
    double time = 1000000 * (end_time.QuadPart - start_time.QuadPart) / dqFreq;

    //printf("��ѡ�������ʱ��Ϊ��%f ΢��\n", time);
    //printf ("ֱ�Ӳ��������ʱ��Ϊ��%f ΢��\n", time);              
   // printf ("ð�������ʱ��Ϊ��%f ΢��\n", time);                
    //printf ("���������ʱ��Ϊ��%f ΢��\n", time);               
    //printf ("��·�ϲ������ʱ��Ϊ��%f ΢��\n", time);   
    printf ("�������ʱ��Ϊ��%f ΢��\n", time);        
    return 0;
}