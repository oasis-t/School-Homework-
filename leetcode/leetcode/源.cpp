#include<stdio.h>
bool isUgly(int n) {
	while (true) {
		if (n == 1 || n == 2 || n == 3 || n == 5)
			return true;
		if (n % 2 == 0)
			n /= 2;
		else if (n % 3 == 0)
			n /= 3;
		else if (n % 5 == 0)
			n /= 5;
		else
			return false;
	}
}
int main() {
	int number;
	scanf_s("%d", &number);
	if (isUgly(number))
		printf("读入数据是丑数");
	else
		printf("读入数据不是丑数");

}