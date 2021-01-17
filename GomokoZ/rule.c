/*
	This file includes rule functions in Gomoko game.
*/

#include "GomokoZ.h"

static const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
static const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
/*dx[] and dy[] are directions*/

int isFiveInRow(int player) /*return the winner, if no one wins, return 0*/
{
	int j, i, k, l;

	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			for (k = 2; k < 6; k++) /*four directions*/
			{
				if (0 <= i + 4 * dx[k] && i + 4 * dx[k] < SIZE && 0 <= j + 4 * dy[k] && j + 4 * dy[k] < SIZE)
				{
					for (l = 0; l < 5; l++)
					{
						if (iBWBoard[j + l * dy[k]][i + l * dx[k]] != player - BLACK + 1)
						{
							break;
						}
					}
					if (l == 5)
					{
						return player;
					}
				}
			}
		}
	}
	return 0;
}

//int isThreeAndThree(int x, int y)
//{
//	int iNum1 = 0, iNum2 = 0;
//	int j, i, k;
//	for (j = 0; j < 8; j++)
//	{
//		for (i = 1; i <= 3; i++)
//		{
//			for (k = 1; k <= 3 && 0 <= x + k * dx[j] && x + k * dx[j] < SIZE && 0 <= y + k * dy[j] && y + k * dy[j] < SIZE; k++)
//			{
//				if (k == i)
//				{
//					if (!(1 <= cBoard[y + k * dy[j]][x + k * dx[j]] && cBoard[y + k * dy[j]][x + k * dx[j]] <= 9))
//					{
//						break;
//					}
//				}
//				else if (!(cBoard[y + k * dy[j]][x + k * dx[j]] == player || cBoard[y + k * dy[j]][x + k * dx[j]] == (player - 2)))
//				{
//					break;
//				}
//			}
//			if (k == 4)
//			{
//				iNum1++;
//			}
//		}
//
//		if (0 <= x + 2 * dx[j] && x + 2 * dx[j] < SIZE && 0 <= y + 2 * dy[j] && y + 2 * dy[j] < SIZE && 0 <= x - 1 * dx[j] && x - 1 * dx[j] < SIZE && 0 <= y - 1 * dy[j] && y - 1 * dy[j] < SIZE)
//		{
//			if ((cBoard[y + 1 * dy[j]][x + 1 * dx[j]] == player || cBoard[y + 1 * dy[j]][x + 1 * dx[j]] == (player - 2)) && (cBoard[y - 1 * dy[j]][x - 1 * dx[j]] == player || cBoard[y - 1 * dy[j]][x - 1 * dx[j]] == (player - 2)) && (1 <= cBoard[y + 2 * dy[j]][x + 2 * dx[j]] && cBoard[y + 2 * dy[j]][x + 2 * dx[j]] <= 9))
//			{
//				iNum2++;
//			}
//		}
//
//		/*if (0 <= x + 2 * dx[j] && x + 2 * dx[j] < SIZE && 0 <= y + 2 * dy[j] && y + 2 * dy[j] < SIZE && 0 <= x - 1 * dx[j] && x - 1 * dx[j] < SIZE && 0 <= y - 1 * dy[j] && y - 1 * dy[j] < SIZE)
//		{
//			if (cBoard[y + 2 * dy[j]][x + 2 * dx[j]] == BLACK && cBoard[y - 1 * dy[j]][x - 1 * dx[j]] == BLACK && (1 <= cBoard[y + 1 * dy[j]][x + 1 * dx[j]] && cBoard[y + 1 * dy[j]][x + 1 * dx[j]] <= 9))
//			{
//				iNum++;
//			}
//		}*/
//
//		if (0 <= x + 1 * dx[j] && x + 1 * dx[j] < SIZE && 0 <= y + 1 * dy[j] && y + 1 * dy[j] < SIZE && 0 <= x - 2 * dx[j] && x - 2 * dx[j] < SIZE && 0 <= y - 2 * dy[j] && y - 2 * dy[j] < SIZE)
//		{
//			if ((cBoard[y + 1 * dy[j]][x + 1 * dx[j]] == player || cBoard[y + 1 * dy[j]][x + 1 * dx[j]] == (player - 2)) && (cBoard[y - 2 * dy[j]][x - 2 * dx[j]] == player || cBoard[y - 2 * dy[j]][x - 2 * dx[j]] == (player - 2)) && (1 <= cBoard[y - 1 * dy[j]][x - 1 * dx[j]] && cBoard[y - 1 * dy[j]][x - 1 * dx[j]] <= 9))
//			{
//				iNum1++;
//			}
//		}
//	}
//	return iNum1 + iNum2 / 2;
//}

int isTwoAndTwo(int player)
{
	/*
		*PP*
		*PP
	*/
	int j, i, k;
	int iNum = 0;
	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			for (k = 2; k < 6; k++)
			{
				if (0 <= i + 3 * dx[k] && i + 3 * dx[k] < SIZE && 0 <= j + 3 * dy[k] && j + 3 * dy[k] < SIZE)
				{
					if (iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == 0
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == 0
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
					}
				}
				else if (0 <= i + 2 * dx[k] && i + 2 * dx[k] < SIZE && 0 <= j + 2 * dy[k] && j + 2 * dy[k] < SIZE)
				{
					if (iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == 0
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
					}
				}
				if (0 <= i + 4 * dx[k] && i + 4 * dx[k] < SIZE && 0 <= j + 4 * dy[k] && j + 4 * dy[k] < SIZE)
				{
					if (iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == 0
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == 0
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == 0
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1))
					{
						iNum += 10;
					}
				}
			}
		}
	}
	return iNum;
}

int isThreeAndThree(int player) /*return the number of three and three*/
{
	/* 
		**PPP*	iS1
		*PPP**	iS2
		*PP*P*
		*P*PP*
		P PIECE
		* must have no piece
		# at least one in two must have no piece
	*/

	int j, i, k;
	int iNum = 0;

	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			for (k = 2; k < 6; k++)
			{
				int iS1 = 0, iS2 = 0;
				if (0 <= i + (-3) * dx[k] && i + (-3) * dx[k] < SIZE
					&& 0 <= i + 2 * dx[k] && i + 2 * dx[k] < SIZE
					&& 0 <= j + (-3) * dy[k] && j + (-3) * dy[k] < SIZE
					&& 0 <= j + 2 * dy[k] && j + 2 * dy[k] < SIZE)
				{
					if (iBWBoard[j + (-3) * dy[k]][i + (-3) * dx[k]] == 0
						&& iBWBoard[j + (-2) * dy[k]][i + (-2) * dx[k]] == 0
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == 0
						&& iBWBoard[j + (-1) * dy[k]][i + (-1) * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						iS1 = 1;
						/*printf("%d %d %d\n", j, i, k);*/
					}
					
				}
				if (0 <= i + (-2) * dx[k] && i + (-2) * dx[k] < SIZE
					&& 0 <= i + 3 * dx[k] && i + 3 * dx[k] < SIZE
					&& 0 <= j + (-2) * dy[k] && j + (-2) * dy[k] < SIZE
					&& 0 <= j + 3 * dy[k] && j + 3 * dy[k] < SIZE)
				{
					if (iBWBoard[j + (-2) * dy[k]][i + (-2) * dx[k]] == 0
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == 0
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == 0
						&& iBWBoard[j + (-1) * dy[k]][i + (-1) * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						iS2 = 1;
						/*printf("%d %d %d\n", j, i, k);*/
					}
				}
				if (0 <= i + 5 * dx[k] && i + 5 * dx[k] < SIZE
					&& 0 <= j + 5 * dy[k] && j + 5 * dy[k] < SIZE)
				{
					if (iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == 0
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == 0
						&& iBWBoard[j + 5 * dy[k]][i + 5 * dx[k]] == 0
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						/*printf("%d %d %d\n", j, i, k);*/
					}
					else if (iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == 0
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == 0
						&& iBWBoard[j + 5 * dy[k]][i + 5 * dx[k]] == 0
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						/*printf("%d %d %d\n", j, i, k);*/
					}
				}
				if (iS1 && iS2)
				{
					iNum--;
				}
			}
		}
	}

	return iNum;
}

int isFourAndFour(int player)
{
	/*
		PPPP*	iS1
		PPP*P
		PP*PP
		P*PPP
		*PPPP	iS2
		P PIECE
		* must have no piece
		# at least one in two must have no piece
	*/

	int j, i, k;
	int iNum = 0;

	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			for (k = 2; k < 6; k++)
			{
				int iS1 = 0, iS2 = 0;
				if (0 <= i + 4 * dx[k] && i + 4 * dx[k] < SIZE
					&& 0 <= j + 4 * dy[k] && j + 4 * dy[k] < SIZE)
				{
					if (iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == 0
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						iS1 = 1;
						/*printf("%d %d %d\n", j, i, k);*/
					}
					else if (iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == 0
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						/*printf("%d %d %d\n", j, i, k);*/
					}
					else if (iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == 0
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						/*printf("%d %d %d\n", j, i, k);*/
					}
					else if (iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == 0
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						/*printf("%d %d %d\n", j, i, k);*/
					}
				}
				if (0 <= i + (-1) * dx[k] && i + (-1) * dx[k] < SIZE
					&& 0 <= i + 3 * dx[k] && i + 3 * dx[k] < SIZE
					&& 0 <= j + (-1) * dy[k] && j + (-1) * dy[k] < SIZE
					&& 0 <= j + 3 * dy[k] && j + 3 * dy[k] < SIZE)
				{
					if (iBWBoard[j + (-1) * dy[k]][i + (-1) * dx[k]] == 0
						&& iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						iS2 = 1;
						/*printf("%d %d %d\n", j, i, k);*/
					}
				}
				if (iS1 && iS2)
				{
					iNum--;
				}
			}
		}
	}
	
	return iNum;
}

int isLiveFour(int player)
{
	/*
		*PPPP*
	*/
	int j, i, k;
	int iNum = 0;

	for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			for (k = 2; k < 6; k++)
			{
				if (0 <= i + 5 * dx[k] && i + 5 * dx[k] < SIZE
					&& 0 <= j + 5 * dy[k] && j + 5 * dy[k] < SIZE)
				{
					if (iBWBoard[j + 0 * dy[k]][i + 0 * dx[k]] == 0
						&& iBWBoard[j + 5 * dy[k]][i + 5 * dx[k]] == 0
						&& iBWBoard[j + 1 * dy[k]][i + 1 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 2 * dy[k]][i + 2 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 3 * dy[k]][i + 3 * dx[k]] == (player - BLACK + 1)
						&& iBWBoard[j + 4 * dy[k]][i + 4 * dx[k]] == (player - BLACK + 1))
					{
						iNum++;
						/*printf("%d %d %d\n", j, i, k);*/
					}
				}
			}
		}
	}

	return iNum;
}

int isLongRow(int player)
{
	//int j, i;
	//int iNum = 0;
	//for (j = 0; j < SIZE; j++)
	//{
	//	int iTemp1 = 0, iTemp2 = 0;
	//	for (i = 0; i < SIZE; i++)
	//	{
	//		if (cBoard[j][i] == player || cBoard[j][i] == (player - 2))
	//		{
	//			iTemp1++;
	//		}
	//		if (cBoard[i][j] == player || cBoard[i][j] == (player - 2))
	//		{
	//			iTemp2++;
	//		}
	//	}
	//	if (iTemp1 >= 6)
	//	{
	//		iNum++;
	//	}
	//	if (iTemp2 >= 6)
	//	{
	//		iNum++;
	//	}
	//}
	///*
	//	8 
	//	9
	//	10	 *
	//	11	 *	 *
	//	12	 *	 *	 *
	//	13	 *	 *	 *	 *
	//	14	 *	 *	 *	 *	 *
	//*/
	//for (j = 0; j < 9; j++)
	//{
	//	int iTemp = 0;
	//	for (i = 0; 0 <= j + i * dy[3] && j + i * dy[3] < SIZE && i < SIZE; i++)
	//	{
	//		if (cBoard[j + i * dy[3]][i] == player || cBoard[j + i * dy[3]][i] == (player - 2))
	//		{
	//			iTemp++;
	//			if (iTemp == 6)
	//			{
	//				iNum++;
	//				break;
	//			}
	//		}
	//	}
	//}
	//for (i = 1; i < 9; i++)
	//{
	//	int iTemp = 0;
	//	for (j = 0; 0 <= i + j * dx[3] && i + j * dx[3] < SIZE && j < SIZE; j++)
	//	{
	//		if (cBoard[j][i + j * dx[3]] == player || cBoard[j][i + j * dx[3]] == (player - 2))
	//		{
	//			iTemp++;
	//			if (iTemp >= 6)
	//			{
	//				iNum++;
	//				break;
	//			}
	//		}
	//	}
	//	
	//}
	///****************************************/
	//for (j = 0; j < 9; j++)
	//{
	//	int iTemp = 0;
	//	for (i = SIZE - 1; 0 <= j + (SIZE - 1 - i) * dy[1] && j + (SIZE - 1 - i) * dy[1] < SIZE && 0 <= i; i--)
	//	{
	//		if (cBoard[j + (SIZE - 1 - i) * dy[1]][i] == player || cBoard[j + (SIZE - 1 - i) * dy[1]][i] == (player - 2))
	//		{
	//			iTemp++;
	//			if (iTemp >= 6)
	//			{
	//				iNum++;
	//			}
	//		}
	//	}		
	//}
	//for (i = SIZE - 1; i > 5; i--)
	//{
	//	int iTemp = 0;
	//	for (j = 0; 0 <= i + j * dy[1] && i + j * dy[1] < SIZE && j < SIZE; j++)
	//	{
	//		if (cBoard[j][i + j * dy[1]] == player || cBoard[j][i + j * dy[1]] == (player - 2))
	//		{
	//			iTemp++;
	//			if (iTemp >= 6)
	//			{
	//				iNum++;
	//			}
	//		}
	//	}
	//}

	//return iNum;
	return 0;
}

void RenewChform(struct chform *cf, int player)
{
	cf->TwoAT = isTwoAndTwo(player);
	cf->TAT = isThreeAndThree(player);
	cf->FAF = isFourAndFour(player);
	cf->LF = isLiveFour(player);
	cf->LR = isLongRow(player);
	cf->FIR = isFiveInRow(player);
}

int isBreaker(struct chform Chform, struct chform ChfTemp) /*if is breaker, return 1, else return 0*/
{
	return (Chform.TAT - ChfTemp.TAT) >= 2 || (Chform.FAF - ChfTemp.FAF) >= 2 || (Chform.LR - ChfTemp.LR) >= 2;
}

int Break() /*if input 'n', return 1; else if input 'Y', return 0; else if have input error, return -1*/
{
	char c;
	printf("BLACK plays a breaker, do you want to continue?(Y/n)\n");
	c = getch();
	if (c == 'n' && (c = getch()) == '\n')
	{
		return 1;
	}
	else if (c == 'Y' && (c = getch()) == '\n')
	{
		return 0;
	}
	else
	{
		for (; c != '\n'; c = getch())
		{
			;
		}
		return -1;
	}
}