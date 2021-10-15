#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define Length 100

void OPA1(int a[], int N)
{
	int sum=0;
	for (int i = 0; i < N; i++)
	{
		if (a[i] % 5 == 0 && a[i] % 2 == 0)
			sum += a[i];
	}
	if (sum == 0)
		printf("N");
	printf("%d ", sum);
}

void OPA2(int a[],int N)
{
	int b[Length],j=0,sum=0;
	for (int i = 0; i < N; i++)
	{
		if (a[i] % 5 == 1)
		{
			b[j] = a[i];
			j++;
		}
	}
	for (int k = 0; k < j; k++)
	{
		sum = pow((-1), k) * b[k];
	}if (sum == 0)
		printf("N");
	printf("%d ", sum);
}

void OPA3(int a[], int N)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		if (a[i] % 5 == 2)
			count++;
	}
	if (count == 0)
		printf("N");
	printf("%d ", count);
}

void OPA4(int a[], int N)
{
	int sum=0, i,count=0;
	float ave;
	for (i = 0; i < N; i++)
	{
		if (a[i] % 5 == 3)
		{
			sum += a[i];
			count++;
		}
	}
	ave = sum / count;
	if (ave== 0)
		printf("N");
	printf("%.f ", ave);
}
/*
void OPA5(int a[], int N)
{
	int c[Length] = { 0 }, j = 0;
	for (int i = 0;i < N; i++)
	{
		if (a[i] % 5 == 4)
		{
			c[j] = a[i];
			j++;
		}
	}
	for (int i = 0; i < j; i++)
	{
		int temp;
		for (int a = 0; a < j; a++)
		{
			if (c[a] < c[a + 1])
			{
				temp = c[a];
				c[a] = c[a + 1];
				c[a + 1] = temp;
			}
		}
	}
	if (c[0]== 0)
		printf("N");
	printf("%d", c[0]);
}
*/
int main()
{
	int a[Length];
	int N;
	scanf_s("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf_s("%d", &a[i]);
	}
	OPA1(a, N);
	OPA2(a, N);
	OPA3(a, N);
	OPA4(a, N);
	//OPA5(a, N);
	return 0;
}