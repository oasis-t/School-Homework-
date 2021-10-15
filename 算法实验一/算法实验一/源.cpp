#include<iostream>
using namespace std;
char* LCS(char* left, char* right);

int main() {
    char* left, * right;
    left = new char[1024];
    right = new char[1024];
    cout << "please input the first string:";
    cin >> left;
    cout << "please input the second string:";
    cin >> right;
    cout << "最长公共子串是：";
    cout << LCS(left, right) << endl;
    return 0;
}

char* LCS(char* left, char* right) {
    int lenLeft, lenRight;
    lenLeft = strlen(left);
    lenRight = strlen(right);
    int* c = new int[lenRight];
    int start, end, len;
    end = len = 0;
    for (int i = 0; i < lenLeft; i++) {
        for (int j = lenRight - 1; j >= 0; j--) {
            if (left[i] == right[j]) {
                if (i == 0 || j == 0)
                    c[j] = 1;
                else
                    c[j] = c[j - 1] + 1;
            }
            else
                c[j] = 0;
            if (c[j] > len) {
                len = c[j];
                end = j;
            }
        }
    }
    char* p = new char[len + 1];
    start = end - len + 1;
    for (int i = start; i <= end; i++)
        p[i - start] = right[i];
    p[len] = '/0';
    return p;
}