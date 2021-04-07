#define	_CRT_SECURE_NO_WARNINGS
#define min(a,b) (((a) < (b)) ? (a) : (b))

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define FN 9999999999

int N;
int M;
int D[MAX];
int W[MAX];
int EE[MAX][MAX][3];
int DD[MAX][MAX][3];
int PP[MAX][MAX][3];

void DP();
void print(int L, int R);

FILE *outf;

void main()
{
	FILE *inf;
	char name[30] = { 0 };

	printf("Input file name ? ");
	scanf("%s", name);

	inf = fopen(name, "r");

	fscanf(inf, "%d\n", &N);
	fscanf(inf, "%d\n", &M);

	M--;

	for (int i = 0; i<N; i++)
	{
		fscanf(inf, "%d %d", &D[i], &W[i]);
	}

	EE[M][M][0] = EE[M][M][1] = 0;

	for (int i = 0; i<N; i++)
	{
		DD[i][i][0] = DD[i][i][1] = PP[i][i][0] = PP[i][i][1] = 0;
		if (i == M)
			continue;
		EE[i][i][0] = EE[i][i][1] = FN;
	}

	DP();

	outf = fopen("output.txt", "w");

	fprintf(outf, "%d\n", min(EE[0][N - 1][0], EE[0][N - 1][1]));

	print(0, N - 1);

	if (EE[0][N - 1][0] < EE[0][N - 1][1])
		fprintf(outf, "1");
	else
		fprintf(outf, "%d", N);
}

void DP()
{
	int L, R;
	int line;

	for (line = N - 2; line >= 0; line--)
	{
		for (L = line, R = N - 1; L >= 0; L--, R--)
		{
			if (EE[L + 1][R][0] + (DD[L + 1][R][0] + D[L + 1] - D[L])*W[L]<EE[L + 1][R][1] + (DD[L + 1][R][1] + D[R] - D[L])*W[L])
			{
				EE[L][R][0] = EE[L + 1][R][0] + (DD[L + 1][R][0] + D[L + 1] - D[L])*W[L];
				DD[L][R][0] = DD[L + 1][R][0] + D[L + 1] - D[L];
				PP[L][R][0] = L + 1;
			}
			else
			{
				EE[L][R][0] = EE[L + 1][R][1] + (DD[L + 1][R][1] + D[R] - D[L])*W[L];
				DD[L][R][0] = DD[L + 1][R][1] + D[R] - D[L];
				PP[L][R][0] = R;
			}

			if (EE[L][R - 1][1] + (DD[L][R - 1][1] + D[R] - D[R - 1])*W[R]<EE[L][R - 1][0] + (DD[L][R - 1][0] + D[R] - D[L])*W[R])
			{
				EE[L][R][1] = EE[L][R - 1][1] + (DD[L][R - 1][1] + D[R] - D[R - 1])*W[R];
				DD[L][R][1] = DD[L][R - 1][1] + D[R] - D[R - 1];
				PP[L][R][1] = R - 1;
			}
			else
			{
				EE[L][R][1] = EE[L][R - 1][0] + (DD[L][R - 1][0] + D[R] - D[L])*W[R];
				DD[L][R][1] = DD[L][R - 1][0] + D[R] - D[L];
				PP[L][R][1] = L;
			}
		}
	}
}

void print(int L, int R)
{
	if (L == M&&R == M)
	{
	}
	else if (EE[L][R][0]<EE[L][R][1])
	{
		print(L + 1, R);
		fprintf(outf, "%d\n", PP[L][R][0] + 1);
	}
	else
	{
		print(L, R - 1);
		fprintf(outf, "%d\n", PP[L][R][1] + 1);
	}
}
