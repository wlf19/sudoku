#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include<string.h>
using namespace std;
int grid[9][9];
bool generateall(int m, int n)
{
	if (m > 8 || n> 8)//��ʱ���������
		return true;
	int i, j, k;
	for (k = 1; k <= 9; k++)
	{
		bool flag = true;//flag���k�ܷ���Է��ڴ�λ��
		for (i = 0; i<m; i++)
		{		//��ѯ�����Ƿ�����ͬ����
			if (grid[i][n] == k)
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			for (j = 0; j <n; j++)
			{//��ѯ�����Ƿ�����ͬ����
				if (grid[m][j] == k)
				{
					flag = false;
					break;
				}

			}
		}
		if (flag)
		{
			//��ѯ���ھŹ����Ƿ�����ͬ����
			int p, q, p1, q1;
			p = m - m % 3; p1 = p + 3; //���ھŹ������������
			q = n - n % 3; q1 = q + 3;//���ھŹ������������
			for (i = p; i <p1; i++)
			{
				for (j = q; j <q1; j++)
				{
					if (grid[i][j] == k)
					{
						flag = false;
						break;
					}
				}
			}
		}
		if (flag)
		{
			grid[m][n] = k;
			if (n < 8)
			{
				if (generateall(m, n + 1)) return true;//��ͬ�е���һ��

			}
			else
			{
				if (m < 8)
				{
					if (generateall(m + 1, 0))//����һ�еĵ�һ��
						return true;

				}
				else return true;//��ʱ���������
			}
			grid[m][n] = 0;//������1��9������ʧ��ʱ���ָ�ԭֵ
		}

	}

	return false;
}

void generate(int num)
{
	int index = 0, sum = 35, i, j;

	srand(num);//��������
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
		{
			grid[i][j] = 0;//��ʼ������
		}
	grid[0][0] = 1;
	for (int i = 1; i < 8; ++i)//���������һ��
	{
		index = rand() % 9;//���������
		while (grid[0][index] != 0)
		{
			index = rand() % 9;
		}
		grid[0][index] = i + 1;
		sum -= index;
	}
	grid[0][sum] = 9;

}


void show()
{
	int i, j;//�����������
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}

	FILE *f; //����������д���ļ�
	f = fopen("shuduku.txt", "ab+");
	if (f == NULL)
	{
		printf("�ļ���ʧ��!\n");
		return;
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				fprintf(f, "%d", grid[i][j]);
			}
			fprintf(f, "\r\n");
		}
		fprintf(f, "\r\n");
	}
	fclose(f);


}

void main()
{
	char  a[11] = { 0 };
	int flag = true, i, k = 0;
	scanf("%s", &a);

	for (i = 0; a[i] != 0; i++)
	{

		if (a[i]< 48 || a[i] > 57)
		{
			printf("�����д���"); flag = false; break;
		}
		else {
			k = k * 10 + (a[i] - 48);
		}
	}

	if (flag)
	{
		while (k)
		{
			printf("\n");
			generate(k);
			generateall(1, 0);
			show();
			k--;
		}

	}

	system("pause");
}