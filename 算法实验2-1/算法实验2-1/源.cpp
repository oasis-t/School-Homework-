#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

string str1 = "xzyzzyx";
string str2 = "zxyyzxz";
vector<vector<int>> table; // ��̬�滮��
set<string> setOfLCS;      // set�������е�LCS
int max(int a, int b)
{
	return (a > b) ? a : b;
}
/* ���ַ�������������� */
string Reverse(string str)
{
	int low = 0;
	int high = str.length() - 1;
	while (low < high)
	{
		char temp = str[low];
		str[low] = str[high];
		str[high] = temp;
		++low;
		--high;
	}
	return str;
}
/* ͬ������Ӵ���ͬ����������г���*/
int lcs(int m, int n)
{
	// ��Ĵ�СΪ(m+1)*(n+1)
	table = vector<vector<int>>(m + 1, vector<int>(n + 1));
	for (int i = 0; i < m + 1; ++i)
	{
		for (int j = 0; j < n + 1; ++j)
		{
			// ��һ�к͵�һ����0
			if (i == 0 || j == 0)
				table[i][j] = 0;
			else if (str1[i - 1] == str2[j - 1])
				table[i][j] = table[i - 1][j - 1] + 1;
			else
				table[i][j] = max(table[i - 1][j], table[i][j - 1]);
		}
	}
	return table[m][n];
}
/*������е�����������У�������set�� */
void traceBack(int i, int j, string lcs_str)
{
	while (i > 0 && j > 0)
	{
		if (str1[i - 1] == str2[j - 1])
		{
			lcs_str.push_back(str1[i - 1]);
			--i;
			--j;
		}
		else
		{
			if (table[i - 1][j] > table[i][j - 1])
				--i;
			else if (table[i - 1][j] < table[i][j - 1])
				--j;
			else   // ��ȵ����
			{
				traceBack(i - 1, j, lcs_str);
				traceBack(i, j - 1, lcs_str);
				return;
			}
		}
	}
	setOfLCS.insert(Reverse(lcs_str));
}
int main()
{
	int m = str1.length();
	int n = str2.length();
	int length = lcs(m, n);
	cout << "The length of LCS is " << length << endl;
	string str;
	traceBack(m, n, str);
	set<string>::iterator beg = setOfLCS.begin();
	for (; beg != setOfLCS.end(); ++beg)
		cout << *beg << endl;
	getchar();
	return 0;
}