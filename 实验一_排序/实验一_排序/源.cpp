#include <iostream>
using namespace std;

void Swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

template <class T>
class SortableList
{
public:
	SortableList(int m)
	{
		n = m;
	}
	void MergeSort();
	void Merge(int left, int mid, int right);
	void QuickSort();
	void Input();
	void Output();
private:
	int Partition(int left, int right);
	void MergeSort(int left, int right);
	void QuickSort(int left, int right);
	T a[1000];//实际排序对象
	int n;
};


template<class T>
void SortableList<T>::Input()
{
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

template<class T>
void SortableList<T>::Output()
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl << endl;
}

//两路合并排序
template<class T>
void SortableList<T>::MergeSort() {
	MergeSort(0, n - 1);
}
template<class T>
void SortableList<T>::MergeSort(int left, int right)
{
	if (left < right) //控制  当调用至序列只剩一个元素结束函数向上层递归执行 
	{
		int mid = (left + right) / 2;
		MergeSort(left, mid);    //二分左边序列 
		MergeSort(mid + 1, right);//二分右边序列 
		Merge(left, mid, right);  //排序 
	}
}
template <class T>
void SortableList<T>::Merge(int left, int mid, int right)
{                                      //a数组为待排序的数组 
	T* temp = new T[right - left + 1]; //temp数组用来暂时保存排序好的数组 
	int i = left, j = mid + 1, k = 0; //left 至mid为左半数组 ，mid+1至right为右半数组 
	while ((i <= mid) && (j <= right))  //对应第一步 当左半数组和右半数组都不为空时 
		if (a[i] <= a[j])             //输出两个数组中的较小者 
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	while (i <= mid)                  //当一数组为空时，输出另一数组的剩余元素 
		temp[k++] = a[i++];
	while (j <= right)                //当一数组为空时，输出另一数组的剩余元素 
		temp[k++] = a[j++];
	for (i = 0, k = left; k <= right;) //将temp数组赋值给原数组 
		a[k++] = temp[i++];
}

template <class T>
int SortableList<T>::Partition(int left, int right)
{
	//前置条件; left ≤ right
	int i = left, j = right + 1;
	do
	{
		do i++; while (a[i] < a[left]);
		do j--; while (a[j] > a[left]);
		if (i < j) Swap(a[i], a[j]);       //交换两个元素了a[i]和a[j]
	} while (i < j);
	Swap(a[left], a[j]);
	return j;
}

template <class T>
void SortableList<T>::QuickSort() 
{
	QuickSort(0, n - 1);
}

template<class T>
void SortableList<T>::QuickSort(int left, int right)
{
	if (left < right) {
		int j = Partition(left, right);
		QuickSort(left, j - 1);               //对左子序列实施快排
		QuickSort(j + 1, right);             //对右子序列实施快排
	}
}

int main()
{
	int m;
	cout << "请输入数组长度n: ";
	cin >> m;
	SortableList<int> List(m);
	cout << "请输入" << m << "个待排序数字:" << endl;
	List.Input();
	List.MergeSort();
	cout << "两路合并排序后：" << endl;
	List.Output();
	cout << "请输入" << m << "个待排序数字:" << endl;
	List.Input();
	List.QuickSort();
	cout << "快速排序后：" << endl;
	List.Output();
	return 0;
}
