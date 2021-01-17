#include "GomokoZ.h"
#define INF 2047483647
#define MAXSCORE 216 /*82 = (3 * 3 - 1) + (4 * 4 - 1) + (5 * 5 - 1) + (6 * 6 - 1)*/
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

static struct nc NodeChoice[DEPTH + 1][MAXSCORE];
static struct dtn Node[DEPTH + 1];

/*
	if cPVEMode == '1', search for maximun
	else if cPVEMode == '2', search for minimum
*/

void Decision(int depth, int maxmin)
{

	struct pos pt = Pos;

	CopyArray(Node[DEPTH].iscore, iScore);

	DFS(Pos, depth, maxmin, (-1) * INF, INF);

	iBWBoard[pt.y][pt.x] = (maxmin == 1) ? 2 : 1;
}

int DFS(struct pos pt, int depth, int maxmin, int alpha, int beta)
{
	int MaxScore;
	int i, j;

	CopyArray(Node[depth - 1].iscore, Node[depth].iscore);
	RenewChform(&Node[depth - 1].Chform[1], BLACK);

	if (maxmin && isBreaker(Node[depth - 1].Chform[1], Node[depth].Chform[1]))
	{
		iBWBoard[pt.y][pt.x] = 0;
		return (-1) * INF;
	}

	RenewChform(&Node[depth - 1].Chform[0], WHITE);

	if (depth == 1 || Node[depth - 1].Chform[0].FIR || Node[depth - 1].Chform[1].FIR)
	{
		iBWBoard[pt.y][pt.x] = 0;
		return Assess(Node[depth - 1].Chform);
	}

	RenewScore(Node[depth - 1].iscore, 1 - maxmin, pt);
	MaxScore = CreateTab(depth - 1, maxmin);

	if (maxmin == 1)
	{
		for (i = MaxScore; i > 0; i--) /*Traversal of the node table*/
		{
			j = 0;
			while (j < NodeChoice[depth - 1][i].top)
			{
				iBWBoard[NodeChoice[depth - 1][i].pt[j].y][NodeChoice[depth - 1][i].pt[j].x] = (maxmin) ? 1 : 2;
				if (depth == DEPTH && isFiveInRow((maxmin) ? BLACK : WHITE))
				{
					Pos = NodeChoice[depth - 1][i].pt[j];
					return 0;
				}
				int iTemp = DFS(NodeChoice[depth - 1][i].pt[j], depth - 1, 1 - maxmin, alpha, beta);
				if (iTemp > alpha && depth == DEPTH)
				{
					Pos = NodeChoice[depth - 1][i].pt[j];
				}
				alpha = max(iTemp, alpha);
				if (alpha >= beta)
				{
					iBWBoard[pt.y][pt.x] = 0;
					return alpha;
				}
				j++;
			}
		}
		iBWBoard[pt.y][pt.x] = 0;
		return alpha;
	}
	else
	{
		for (i = MaxScore; i > 0; i--) /*Traversal of the node table*/
		{
			j = 0;
			while (j < NodeChoice[depth - 1][i].top)
			{
				iBWBoard[NodeChoice[depth - 1][i].pt[j].y][NodeChoice[depth - 1][i].pt[j].x] = (maxmin) ? 1 : 2;
				int iTemp = DFS(NodeChoice[depth - 1][i].pt[j], depth - 1, 1 - maxmin, alpha, beta);
				if (iTemp < beta && depth == DEPTH)
				{
					Pos = NodeChoice[depth - 1][i].pt[j];
				}
				beta = min(iTemp, beta);
				if (alpha >= beta)
				{
					iBWBoard[pt.y][pt.x] = 0;
					return beta;
				}
				j++;
			}
		}
		iBWBoard[pt.y][pt.x] = 0;
		return beta;
	}	
}

void CopyArray(int a[][SIZE][SIZE], int b[][SIZE][SIZE])
{
	int j, i;
	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			a[0][j][i] = b[0][j][i];
			a[1][j][i] = b[1][j][i];
		}
	}
}

int CreateTab(int depth, int maxmin)
{
	int j, i, iMaxScore = 0;

	InitTab(depth);

	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			int index = Node[depth].iscore[maxmin][j][i];
			if (index > 0 && !iBWBoard[j][i])
			{
				NodeChoice[depth][index].pt[NodeChoice[depth][index].top].x = i;
				NodeChoice[depth][index].pt[(NodeChoice[depth][index].top)++].y = j;
			}

			iMaxScore = max(iMaxScore, index);
		}
	}

	return iMaxScore;
}

void InitTab(int depth)
{
	int i;
	for (i = 0; i < MAXSCORE; i++)
	{
		NodeChoice[depth][i].top = 0;
	}
}