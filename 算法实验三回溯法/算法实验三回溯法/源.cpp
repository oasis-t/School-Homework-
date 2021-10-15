#include <iostream>
using namespace std;

#define MAXN 20 // ���ʺ����
int q[MAXN]; // ��Ÿ��ʺ����ڵ��к�
int static number = 1; // �ۼƽ����

void dispasolution(int n) {
	cout << "��" << number++ << "���⣺";
	for (int i = 1; i <= n; i++)
		cout << "(" << q[i]-1 << ")";
	cout << endl;
}

bool place(int i) { // ���Ե�i�е�q[i]�����ܷ�ڷŻʺ�
	int j = 1;
	while (j < i) {
		if ((q[i] == q[j]) || (abs(q[i] - q[j]) == abs(i - j))) // �ûʺ��Ƿ�����ǰ�Ļʺ�ͬ�У������Ƿ�ͬ�Խ���
			return false;
		j++;
	}
	return true;
}

void Queens(int n) {
	int i = 1; // ��ʾ���õĵ�һ���ʺ�
	q[i] = 0;  // q[i]�ǵ�ǰ�У�ÿ���¿��ǵĻʺ�ĳ�ʼλ��Ϊ0��
	while (i >= 1) { // ��δ���ݵ�ͷ��ѭ��
		q[i] ++; // ԭλ�ú���һ��
		while (q[i] <= n && !place(i)) // ��̽һ��λ��
			q[i]++;
		if (q[i] <= n) { // Ϊ��i���ʺ��ҵ���һ�����ʵ�λ��(i, q[i])
			if (i == n) // �����������лʺ���ô���һ����
				dispasolution(n);
			else {
				i++; // ת����һ�У���ʼ��һ���ʺ��λ��
				q[i] = 0; // ÿ���ȿ��ǵĻʺ�ĳ�ʼλ��Ϊ0��
			}
		}
		else { // ����i���ʺ��Ҳ������ʵ�λ�ã���ô���ݵ���һ���ʺ�
			i--;
		}
	}
}

int main() {
	int n; // ���ʵ�ʵĻʺ����
	cin >> n;
	cout << n << "�ʺ�����������£�" << endl;
	Queens(n);

	return 0;
}