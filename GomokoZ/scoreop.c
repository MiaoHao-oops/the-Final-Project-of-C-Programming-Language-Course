/*
	This file includes score operations.
*/

#include "GomokoZ.h"

#define VALUE 5
#define VTAT 10000
#define VFAF 10000
#define VLF 1000000
#define VFIR 100000000

static const int x[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
static const int y[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void RenewScore(int score[][SIZE][SIZE], int tabnum, struct pos pt) /*version 1*/
{
	int i;
	score[tabnum][pt.y][pt.x] = -1;
	
	for (i = 0; i < 8; i++)
	{
		AddScore(x[i], y[i], score, tabnum, pt);
	}

	int j;
	/*for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			printf("%d ", score[0][j][i]);
		}
		printf("\t");
		for (i = 0; i < SIZE; i++)
		{
			printf("%d ", score[1][j][i]);
		}
		printf("\n");
	}*/
}

void AddScore(int x, int y, int score[][SIZE][SIZE], int tabnum, struct pos pt)
{
	int i;
	for (i = 1; 0 <= pt.x + i * x && pt.x + i * x < SIZE && i < 5 && 0 <= pt.y + i * y && pt.y + i * y < SIZE; i++)
	{
		if (score[tabnum][pt.y + i * y][pt.x + i * x] != -1)
		{
			score[tabnum][pt.y + i * y][pt.x + i * x] += VALUE - i + 1;
		}
	}
}

int Assess(struct chform Chform[])
{
	if (cPVEMode == '1')
	{
		return (VTAT * Chform[1].TAT + VFAF * Chform[1].FAF + VLF * Chform[1].LF + VALUE * Chform[1].TwoAT + VFIR * Chform[1].FIR) + (-1) * (VTAT * Chform[0].TAT + VFAF * Chform[0].FAF + VALUE * Chform[0].TwoAT + VLF * Chform[0].LF + VFIR * Chform[0].FIR);
	}
	else
	{
		return (10 * VTAT * Chform[1].TAT + VFAF * Chform[1].FAF + 10 * VLF * Chform[1].LF + 10 * VALUE * Chform[1].TwoAT + VFIR * Chform[1].FIR) + (-1) * (VTAT * Chform[0].TAT + VFAF * Chform[0].FAF + VALUE * Chform[0].TwoAT + VLF * Chform[0].LF + VFIR * Chform[0].FIR);
	}
}