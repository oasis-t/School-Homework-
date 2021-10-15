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


//简单选择排序
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


//直接插入排序
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


//冒泡排序
void BubbleSort(sl* sl)
{
    int i, j;                    //i标识每趟排序范围最后一个元素下标,每趟排序元素下标范围是0~i
    for (i = sl->n - 1; i > 0; i--) 
    {
        BOOL isSwap = FALSE;    //教材这里错了,应该放到第二层循环前
        for (j = 0; j < i; j++) 
        {
            if (sl->D[j].key > sl->D[j + 1].key) 
            {
                Swap(sl->D, j,j+1);
                isSwap = TRUE;
            }
        }
        if (!isSwap) break;     //如果本趟排序没有发生元素交换,排序完成
    }
}


//序列划分方法
int Partition(sl* sl, int low, int high) 
{
    int i = low, j = high + 1;
    Entry pivot = sl->D[low];                 //pivot是分割元素
    do 
    {
        do i++;
        while (sl->D[i].key < pivot.key);      //i前进
        do j--;
        while (sl->D[j].key > pivot.key);      //j前进
        if (i < j) Swap(sl->D, i,j);
    } while (i < j);
    Swap(sl->D,low, j);
    return j;                                   //此时j是分割元素下标
}
//快速排序
void QuickSort(sl* sl, int low, int high) 
{   //快速排序的递归函数
    int k;
    if (low < high)
    {                            //当前待排序序列至少包含2个元素
        k = Partition(sl, low, high);
        QuickSort(sl, low, k - 1);
        QuickSort(sl, k + 1, high);
    }
}
//函数重载
void QuickSort(sl* sl) 
{                   //快速排序算法的主调用函数
    QuickSort(sl, 0, sl->n - 1);
}


//序列两路合并方法，n1和n2是两个子序列长度,low是第一个子序列第一个元素下标
void Merge(sl* sl, Entry* temp, int low, int n1, int n2) 
{
    int i = low, j = low + n1; //i,j初始时分别指向两个序列的第一个元素
    while (i <= low + n1 - 1 && j <= low + n1 + n2 - 1) 
    {
        if (sl->D[i].key <= sl->D[j].key)
            *temp++ = sl->D[i++];
        else *temp++ = sl->D[j++];
    }
    while (i <= low + n1 - 1)
        *temp++ = sl->D[i++];  //剩余元素直接拷贝至temp
    while (j <= low + n1 + n2 - 1)
        *temp++ = sl->D[j++];  //剩余元素直接拷贝至temp
}
//两路合并排序算法
void MergeSort(sl* sl)
{
    Entry temp[Maxsize];
    int low, n1, n2, i, size = 1;
    while (size < sl->n) 
    {
        low = 0;      //low是一对待合并序列中第一个序列的第一个元素下标
        while (low + size < sl->n)
        {
            //low+size < sl->n说明至少存在两个子序列需要合并
            n1 = size;
            if (low + size * 2 < sl->n)
                n2 = size;  //计算第二个序列长度
            else n2 = sl->n - low - size;
            Merge(sl, temp, low, n1, n2);
            low += n1 + n2;  //确定下一对待合并序列中第一个序列的第一个元素下标
        }
        for (i = 0; i < sl->n; i++) 
        {
            sl->D[i] = temp[i];  //复制一趟合并排序结果
        }
        size *= 2;  //子序列长度翻倍
    }
}
//向下调整
void AdjustDown(Entry* heap, int current, int border)
{
    int p = current;
    int minChild;
    int temp;
    while (2 * p + 1 <= border)
    {
        if ((2 * p + 2 <= border) && (heap[2 * p + 1].key > heap[2 * p + 2].key))
            minChild = 2 * p + 2;    //右孩子存在，且较小，则minChild指向p的右孩子
        else
            minChild = 2 * p + 1;  //右孩子不存在或较大，则minChild指向p的左孩子
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
//堆排序
void HeapSort(sl* sl)                                                 
{
    int i;
    for (i = (sl->n - 2) / 2; i >= 0; i--)
        AdjustDown(sl->D, i, sl->n - 1);
    for (i = sl->n - 1; i > 0; i--)  //i指向当前堆的堆底元素
    {
        Swap(sl->D, 0, i);       //交换堆底与堆顶元素
        AdjustDown(sl->D, 0, i - 1);
    }
}
//生成随机数
void randint(int n)
{
    int i, j;
    FILE* fp = NULL;
    srand(time(NULL));  //随机种子
    fopen_s(&fp,"C:\\Users\\时生\\source\\repos.txt", "w");
    for (i = 0; i < n; i++)     //产生随机数
    {
        j = rand() % 200000;
        fprintf(fp, "%d\t", j);
    }
    fclose(fp);
}
//给待排序的顺序表赋值
void read(sl* sl) 
{
    int i;
    FILE* fp;
    fopen_s(&fp,"C:\\Users\\时生\\source\\repos.txt", "r");
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
    scanf_s("%d", &sl.n);//输入待排序元素的数量
    randint(sl.n);
    read(&sl);
    for (i = 0; i < sl.n; i++)
    {
        sl.D[i].key = rand()%1000;//控制生成的随机数在1000以内
    }
    LARGE_INTEGER start_time, end_time;
    double dqFreq;
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    dqFreq = (double)f.QuadPart;

    QueryPerformanceCounter(&start_time);

    //SelectSort(&sl);              //简单选择排序
    //InsertSort (&sl);            //直接插入排序
    //BubbleSort (&sl);             //冒泡排序
    // QuickSort (&sl);           //快速排序
    //MergeSort (&sl);              //两路合并排序
    HeapSort (&sl);              //堆排序

    QueryPerformanceCounter(&end_time);
    double time = 1000000 * (end_time.QuadPart - start_time.QuadPart) / dqFreq;

    //printf("简单选择排序的时间为：%f 微秒\n", time);
    //printf ("直接插入排序的时间为：%f 微秒\n", time);              
   // printf ("冒泡排序的时间为：%f 微秒\n", time);                
    //printf ("快速排序的时间为：%f 微秒\n", time);               
    //printf ("两路合并排序的时间为：%f 微秒\n", time);   
    printf ("堆排序的时间为：%f 微秒\n", time);        
    return 0;
}