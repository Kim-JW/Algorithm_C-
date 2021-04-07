#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

int n, ch;
int col[1000000];

int promising(int i);
void queen(int i);
int random(int range);

void main()
{
	char file[30];
	int j;
	FILE *inf, *outf;

	printf("input file name?");
	scanf("%s", file);

	inf = fopen(file, "r");
	fscanf(inf, "%d", &n);

	srand((int)time(NULL));

	int check = 0;
	int r = n * 10 / 100;

	while (ch == 0) {
		int i = 1;
		while (i <= n - r)
		{
			col[i] = random(n);

			if (promising(i)) {
				i++;
				check = 0;
			}
			else {
				check++;
				if (check >= n)
					i = 1;
			}
		}
		queen(n - r);
	}

	outf = fopen("output.txt", "w");
	for (j = 1; j <= n; j++)
		if (j != n) fprintf(outf, "%d\n", col[j]);
		else fprintf(outf, "%d", col[j]);
}

int promising(int i)
{
	int k = 1;

	while (k<i) {
		if (col[i] == col[k] || col[i] - col[k] == i - k || col[i] - col[k] == k - i)
			return FALSE;
		k++;
	}
	return TRUE;
}


void queen(int i)
{
	int j;

	if (promising(i))
		if (i == n) {
			ch = 1;
		}
		else
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queen(i + 1);
				if (ch == 1) break;
			}
}

int random(int range)
{
	return ((rand() % range) + 1);
}


