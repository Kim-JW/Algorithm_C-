#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

FILE *outf;


int per[30];
int i, j, n;

long int mat[30][30];
int table[30][30];

#define FN 999999999

void chained(void)
{
	long int q;
	int k;
	for (i = n; i>0; i--)
	{
		for (j = i; j <= n; j++)
		{
			if (i == j)
				mat[i][j] = 0;
			else
			{
				for (k = i; k<j; k++)
				{
					q = mat[i][k] + mat[k + 1][j] + per[i - 1] * per[k] * per[j];
					if (q<mat[i][j])
					{
						mat[i][j] = q;
						table[i][j] = k;
					}
				}
			}
		}
	}
}

void print(int i, int j)
{
	if (i == j)
		fprintf(outf, " %d ", i);
	else
	{
		fprintf(outf, " ( ");
		print(i, table[i][j]);
		print(table[i][j] + 1, j);
		fprintf(outf, " ) ");
	}
}

void main()
{
	FILE *inf;

	char name[30] = { 0 };

	int k;
	printf("input file name?: ");
	scanf("%s", name);

	inf = fopen(name, "r");
	fscanf(inf, "%d", &n);

	for (i = 1; i < n; i++)
		for (j = i + 1; j <= n; j++)
		{
			mat[i][i] = 0;
			mat[i][j] = FN;
			table[i][j] = 0;
		}


	for (k = 0; k < n; k++)
	{
		fscanf(inf, "%d", &per[k]);
	}

	chained();

	i = 1, j = n - 1;
	outf = fopen("output.txt", "w");
	print(i, j);
}