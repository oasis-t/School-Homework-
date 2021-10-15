#include <iostream>
using namespace std;

void MatrixMultiply(int n, int* size, int** m, int** s)
{
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;           
    for (int l = 2; l <= n; l++) 
    {
        int j;
        for (int i = 1; i <= n + 1 - l; i++)
        {
            j = l + i - 1;
            m[i][j] = m[i][i] + m[i + 1][j] + size[i - 1] * size[i] * size[j];
            s[i][j] = i;
            int tmp;
            for (int k = i + 1; k < j; k++)
            {
                tmp = m[i][k] + m[k + 1][j] + size[i - 1] * size[k] * size[j];
                if (tmp < m[i][j])
                {
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        }
    }
}

void Function(int i, int j, int** s)
{
    if (i == j)
        cout << 'A' << i;
    else
    {
        cout << '(';
        Function(i, s[i][j], s);
        Function(s[i][j] + 1, j, s);
        cout << ')';
    }
}

int main()
{
    int size[] = {4,7,10,5,3,15};//4，7，10表示4行7列与7行10列矩阵，以此类推
    int n = sizeof(size) / sizeof(*size) - 1;
    int** m = new int* [n + 1];
    int** s = new int* [n + 1];
    for (int i = 1; i <= n; i++)
    {
        m[i] = new int[n + 1];
        s[i] = new int[n + 1];
    }
     MatrixMultiply(n, size, m, s);
    Function(1, n, s);
    return 0;
}