#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int n, ch;
int col[21];

FILE *inf, *outf;

int promising(int i);
void queen(int i);

void main()
{
	char file_name[30];

	printf("input file name?");

	scanf("%s", file_name);

	inf = fopen(file_name, "r");

	fscanf(inf, "%d", &n);

	queen(0);

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
			outf = fopen("output.txt", "w");
			for (j = 1; j <= n; j++)
				if (j != n) 
			fprintf(outf, "%d\n", col[j]);
				else fprintf(outf, "%d\n", col[j]);
				ch = 1;
		}
		else
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queen(i + 1);
				if (ch == 1) break;
			}
}

