#include<iostream>
using namespace std;
#define N 10//���ɴ���N�ʺ�����

int num = 0;//����ȫ�ֱ������ڱ�ʾ��ĸ���
bool Place(int k, int i, int* x) {//�ж������ʺ��Ƿ���ͬһ�л�ͬһб����
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
			if (k == n - 1) {//���һ�����н�
				cout << "��"<<++num<<"����Ϊ��(";
				for (i = 0; i < n-1; i++) {
					cout << x[i] << ",";
				}
					cout <<x[i]<<")"<< endl;
			}
			else NQueens(k + 1, n, x);//������Ƚ�����һ��
		}
	}
}

void NQueens(int n, int* x) {
	NQueens(0, n, x);
}

int main() {
	int q[N];
	for (int i = 0; i < N; i++)//�����ʼ��
		q[i] = 0;
	int n;//�ʺ����
	cout << "������ʺ������";
	cin >>n;
	NQueens(n, q);
	return 0;
}