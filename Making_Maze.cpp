#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MAX 2000

int size;
int x_t[4] = { -1,1,0,0 }, y_t[4] = { 0,0,-1,1 };

char maze[MAX][MAX];
int length[MAX][MAX];
char trail[MAX][MAX];

void find();
void print(int x, int y);

FILE *outf;

void main()
{
	char name[30] = { 0 };

	FILE *inf;

	printf("Input file name?");
	scanf("%s", name);

	inf = fopen(name, "r");

	fscanf(inf, "%d\n", &size);

	for (int i = 0; i<size + 2; i++)
	{
		for (int j = 0; j<size + 2; j++)
		{
			maze[i][j] = '0';
			length[i][j] = 0;
			trail[i][j] = '0';
		}
	}

	for (int i = 1; i < size + 1; i++)
	{
		for (int j = 1; j < size + 1; j++)
		{
			length[i][j] = 2000000000;
			fscanf(inf, "%c ", &maze[i][j]);
			if (maze[i][j] == '0')
				maze[i][j] = '1';
			else
				maze[i][j] = '0';
		}
	}

	length[1][1] = 0;
	trail[1][1] = '0';

	outf = fopen("output.txt", "w");

	find();
	print(size, size);

	fprintf(outf, "%d %d", size, size);
}

void find()
{
	int x, y, xx, yy, min;
	int i, j;

	do
	{
		x = 0; y = 0;
		min = 2000000000;

		for (i = 1; i <= size; i++)
		{
			for (j = 1; j <= size; j++)
			{
				if (min > length[i][j] && length[i][j] >= 0)
				{
					min = length[i][j];
					x = i; y = j;
				}
			}
		}
		for (i = 0; i < 4; i++)
		{
			xx = x + x_t[i]; yy = y + y_t[i];
			if (maze[xx][yy] == '1')
				min = length[x][y] + 1;
			else
				min = length[x][y];
			if (min < length[xx][yy])
			{
				length[xx][yy] = min;
				switch (i)
				{
				case 0:
					trail[xx][yy] = 'D';
					break;
				case 1:
					trail[xx][yy] = 'U';
					break;
				case 2:
					trail[xx][yy] = 'R';
					break;
				case 3:
					trail[xx][yy] = 'L';
					break;
				}
			}
		}
		length[x][y] = -1;

	} while (length[size][size] >= 2000000000);

	fprintf(outf, "%d\n", length[size][size]);
}

void print(int x, int y)
{
	if (x == 1 && y == 1) {}
	else {
		if (trail[x][y] == 'U')
		{
			print(x - 1, y);
			fprintf(outf, "%d %d \n", x - 1, y);
		}
		else if (trail[x][y] == 'L')
		{
			print(x, y - 1);
			fprintf(outf, "%d %d \n", x, y - 1);
		}
		else if (trail[x][y] == 'R')
		{
			print(x, y + 1);
			fprintf(outf, "%d %d \n", x, y + 1);
		}
		else
		{
			print(x + 1, y);
			fprintf(outf, "%d %d \n", x + 1, y);
		}
	}
}