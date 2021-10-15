#include<iostream>
#include<math.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
class SortableList
{
public:
    SortableList(int mSize)
    {
        maxSize = mSize;
        l = new int[maxSize + 1];
        n = 0;
    }
    ~SortableList()
    {
        delete[]l;
    }
    void Input();
    void Select(int k) {
        int j = 0;
        j = Select(k, 0, n - 1, 5);
        cout << "第k小元素是：" << l[j];
    }
private:
    int* l;
    int n;             //数组中已有元素个数
    int maxSize;
    void InsertSort(int left, int right);
    void Swap(int i, int j);   //交换下标为 i和 j的数组元素
    int Partition(int left, int right);//  分化操作
    int Select(int k, int left, int right, int r);

};

int SortableList::Partition(int left, int right)
{
    int i = left, j = right + 1;
    do {
        do i++; while (l[i] < l[left]);
        do j--; while (l[j] > l[left]);
        if (i < j) Swap(i, j);
    } while (i < j);
    Swap(left, j);
    return j;
}

void SortableList::InsertSort(int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int j = i;
        int temp = l[i];
        while (j > left && temp < l[j - 1])
        {
            l[j] = l[j - 1];
            j--;
        }
        l[i] = temp;
    }

}

void SortableList::Input()
{
    cout << "请输入元素" << endl;
    for (int i = 0; i < maxSize; i++)
    {
        cin >> l[i];
        n++;
    }
    l[n] = 1000;
}

void SortableList::Swap(int i, int j)
{
    int c = l[i];
    l[i] = l[j];
    l[j] = c;
}

int SortableList::Select(int k, int left, int right, int r)
{  //每个分组r个元素，寻找第k小元素
    int n = right - left + 1;
    if (n <= r)
    {
        InsertSort(left, right);
        return left + k - 1;  //返回第k小元素的下标
    }
    for (int i = 1; i <= n / r; i++)
    {
        InsertSort(left + (i - 1) * r, left + i * r - 1); //二次取中规则求每组的中间值
        Swap(left + i - 1, left + (i - 1) * r + (int)ceil((double)r / 2) - 1);  //将每组的中间值交换到子表前部集中存放
    }
    int j = Select((int)ceil((double)n / r / 2), left, left + (n / r) - 1, r); //求二次中间值，其下标为j
    Swap(left, j);  //二次中间值为枢纽元，并换至left处
    j = Partition(left, right);  //对表（子表）进行分划操作
    if (k == j - left + 1)  //返回第k小元素下标
        return j;
    else if (k < j - left + 1)  //在左子表求第k小元素
        return Select(k, left, j - 1, r);
    else
        return Select(k - (j - left + 1), j + 1, right, r);  //在右子表求第k-(j-left+1)小元素
}

int main()
{
    int num;
    cout << "请输入待排序元素个数:";
    cin >> num;
    SortableList sort(num);
    int k = 0;
    sort.Input();
    cout << "请输入你要查找的第k小元素：" << endl;
    cin >> k;
    sort.Select(k);
    return 0;
}