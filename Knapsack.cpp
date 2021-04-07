#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int t, n, W;
int p[1001], w[1001];
int maxprofit = 0, numbest = 0, include[1001], bestset[1001];

void knapsack(int i, int profit, int weight);
bool promising(int i, int pp, int ww);

void main()
{
	char file_name[30];
	FILE *inf, *outf;

	printf("input file name?");
	scanf("%s", &file_name);

	inf = fopen(file_name, "r");

	fscanf(inf, "%d %d", &n, &W);

	for (t = 1; t <= n; t++)
	{
		fscanf(inf, "%d %d", &p[t], &w[t]);
	}

	knapsack(0, 0, 0);

	outf = fopen("output.txt", "w");

	fprintf(outf, "%d\n", maxprofit);

	if (numbest == n) {
		for (t = 1; t < numbest; t++)
			fprintf(outf, "%d\n", bestset[t]);
		fprintf(outf, "%d", bestset[numbest]);
	}
	else {
		for (t = 1; t <= numbest; t++)
			fprintf(outf, "%d\n", bestset[t]);

		for (t = numbest + 1; t < n; t++)
			fprintf(outf, "0\n");
		fprintf(outf, "0");
	}
}

bool promising(int i, int pp, int ww)
{
	int j, k;
	int totweight;
	float bound;

	if (ww >= W)
		return false;

	else {
		j = i + 1;
		bound = pp;
		totweight = ww;

		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= n)
			bound = bound + (W - totweight)*p[k] / w[k];

		return (bound > maxprofit);
	}
}

void knapsack(int i, int profit, int weight)
{
	if (weight <= W && profit > maxprofit)
	{
		maxprofit = profit;
		numbest = i;

		for (t = 1; t <= numbest; t++)
			bestset[t] = include[t];
	}

	if (promising(i, profit, weight))
	{
		include[i + 1] = 1; 
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);

		include[i + 1] = 0; 
		knapsack(i + 1, profit, weight);
	}
}



