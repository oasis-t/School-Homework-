#include <iostream>
using namespace std;

#define MAXN 20 // 最多皇后个数
int q[MAXN]; // 存放各皇后所在的列号
int static number = 1; // 累计解个数

void dispasolution(int n) {
	cout << "第" << number++ << "个解：";
	for (int i = 1; i <= n; i++)
		cout << "(" << q[i]-1 << ")";
	cout << endl;
}

bool place(int i) { // 测试第i行的q[i]列上能否摆放皇后
	int j = 1;
	while (j < i) {
		if ((q[i] == q[j]) || (abs(q[i] - q[j]) == abs(i - j))) // 该皇后是否与以前的皇后同列，或者是否同对角线
			return false;
		j++;
	}
	return true;
}

void Queens(int n) {
	int i = 1; // 表示放置的第一个皇后
	q[i] = 0;  // q[i]是当前列，每个新考虑的皇后的初始位置为0列
	while (i >= 1) { // 尚未回溯到头，循环
		q[i] ++; // 原位置后移一列
		while (q[i] <= n && !place(i)) // 试探一个位置
			q[i]++;
		if (q[i] <= n) { // 为第i个皇后找到了一个合适的位置(i, q[i])
			if (i == n) // 若放置了所有皇后，那么输出一个解
				dispasolution(n);
			else {
				i++; // 转向下一行，开始下一个皇后的位置
				q[i] = 0; // 每个先考虑的皇后的初始位置为0列
			}
		}
		else { // 若第i个皇后找不到合适的位置，那么回溯到上一个皇后
			i--;
		}
	}
}

int main() {
	int n; // 存放实际的皇后个数
	cin >> n;
	cout << n << "皇后问题求解如下：" << endl;
	Queens(n);

	return 0;
}