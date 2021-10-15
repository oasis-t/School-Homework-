#include<iostream>
using namespace std;
#define N 10//最大可处理到N皇后问题

int num = 0;//定义全局变量用于表示解的个数
bool Place(int k, int i, int* x) {//判定两个皇后是否在同一列或同一斜线上
	for (int j = 0; j < k; j++) {
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
			return false;
	}
	return true;
}

void NQueens(int k, int n, int* x) {
	for (int i = 0; i < n; i++) {
		if (Place(k, i, x)) {
			x[k] = i;
			if (k == n - 1) {//输出一个可行解
				cout << "第"<<++num<<"个解为：(";
				for (i = 0; i < n-1; i++) {
					cout << x[i] << ",";
				}
					cout <<x[i]<<")"<< endl;
			}
			else NQueens(k + 1, n, x);//深度优先进入下一层
		}
	}
}

void NQueens(int n, int* x) {
	NQueens(0, n, x);
}

int main() {
	int q[N];
	for (int i = 0; i < N; i++)//数组初始化
		q[i] = 0;
	int n;//皇后个数
	cout << "请输入皇后个数：";
	cin >>n;
	NQueens(n, q);
	return 0;
}