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
        cout << "��kСԪ���ǣ�" << l[j];
    }
private:
    int* l;
    int n;             //����������Ԫ�ظ���
    int maxSize;
    void InsertSort(int left, int right);
    void Swap(int i, int j);   //�����±�Ϊ i�� j������Ԫ��
    int Partition(int left, int right);//  �ֻ�����
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
    cout << "������Ԫ��" << endl;
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
{  //ÿ������r��Ԫ�أ�Ѱ�ҵ�kСԪ��
    int n = right - left + 1;
    if (n <= r)
    {
        InsertSort(left, right);
        return left + k - 1;  //���ص�kСԪ�ص��±�
    }
    for (int i = 1; i <= n / r; i++)
    {
        InsertSort(left + (i - 1) * r, left + i * r - 1); //����ȡ�й�����ÿ����м�ֵ
        Swap(left + i - 1, left + (i - 1) * r + (int)ceil((double)r / 2) - 1);  //��ÿ����м�ֵ�������ӱ�ǰ�����д��
    }
    int j = Select((int)ceil((double)n / r / 2), left, left + (n / r) - 1, r); //������м�ֵ�����±�Ϊj
    Swap(left, j);  //�����м�ֵΪ��ŦԪ��������left��
    j = Partition(left, right);  //�Ա��ӱ����зֻ�����
    if (k == j - left + 1)  //���ص�kСԪ���±�
        return j;
    else if (k < j - left + 1)  //�����ӱ����kСԪ��
        return Select(k, left, j - 1, r);
    else
        return Select(k - (j - left + 1), j + 1, right, r);  //�����ӱ����k-(j-left+1)СԪ��
}

int main()
{
    int num;
    cout << "�����������Ԫ�ظ���:";
    cin >> num;
    SortableList sort(num);
    int k = 0;
    sort.Input();
    cout << "��������Ҫ���ҵĵ�kСԪ�أ�" << endl;
    cin >> k;
    sort.Select(k);
    return 0;
}