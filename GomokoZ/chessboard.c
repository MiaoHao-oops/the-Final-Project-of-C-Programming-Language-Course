/*
	This file includes functions to init, display or edit the chessboard.
*/

#include "GomokoZ.h"

const char* cTabAndChess[] = {
	'\0',
	"┏",
	"┓",
	"┛",
	"┗",
	"┣",
	"┳",
	"┫",
	"┻",
	"╋",
	"△",
	"▲",
	"○",
	"●"
};

void Init()
{
	int i, j;

	cBoard[0][0] = 1;
	cBoard[0][SIZE - 1] = 2;
	cBoard[SIZE - 1][SIZE - 1] = 3;
	cBoard[SIZE - 1][0] = 4;

	iScore[0][0][0] = 0;
	iScore[0][0][SIZE - 1] = 0;
	iScore[0][SIZE - 1][SIZE - 1] = 0;
	iScore[0][SIZE - 1][0] = 0;

	iScore[1][0][0] = 0;
	iScore[1][0][SIZE - 1] = 0;
	iScore[1][SIZE - 1][SIZE - 1] = 0;
	iScore[1][SIZE - 1][0] = 0;

	for (i = 1; i <= SIZE - 2; i++) //encode the tab chars with 0~9
	{
		cBoard[i][0] = 5;
		iScore[0][i][0] = 0;
		iScore[1][i][0] = 0;
	}

	for (j = 1; j <= SIZE - 2; j++)
	{
		cBoard[0][j] = 6;
		iScore[0][j][0] = 0;
		iScore[1][j][0] = 0;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		cBoard[i][SIZE - 1] = 7;
		iScore[0][i][SIZE - 1] = 0;
		iScore[1][i][SIZE - 1] = 0;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		cBoard[SIZE - 1][i] = 8;
		iScore[0][SIZE - 1][i] = 0;
		iScore[1][SIZE - 1][i] = 0;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		for (j = 1; j <= SIZE - 2; j++)
		{
			cBoard[i][j] = 9;
			iScore[0][i][j] = 0;
			iScore[1][i][j] = 0;
		}
	}

	iPlayer = BLACK; /*BLACK goes first*/
	Postem.x = Postem.y = 16;
}

void DisplayBoard()
{
	int i, j;
	char y;

	system(CLEAR);

	for (i = 0; i < SIZE; i++)
	{
		printf("%2d", 15 - i);
		for (j = 0; j < SIZE; j++)
		{
			/*switch (cBoard[i][j])
			{
			case 1:
				printf("��");
				break;

			case 2:
				printf("��");
				break;

			case 3:
				printf("��");
				break;

			case 4:
				printf("��");
				break;

			case 5:
				printf("��");
				break;

			case 6:
				printf("��");
				break;

			case 7:
				printf("��");
				break;

			case 8:
				printf("��");
				break;

			case 9:
				printf("��");
				break;

			case BLACKtem:
				printf("��");
				break;

			case WHITEtem:
				printf("��");
				break;

			case BLACK:
				printf("��");
				break;

			case WHITE:
				printf("��");
				break;
			}
			*/
			printf("%s", cTabAndChess[cBoard[i][j]]);
		}
		printf("%c", '\n');
	}

	printf("%s", "  ");

	for (y = 'A'; y < 'A' + SIZE; y++)
	{
		printf("%c ", y);
	}
	
	printf("%c", '\n');

	/*for (j = 0; j < SIZE; j++)
	{
		for (i = 0; i < SIZE; i++)
		{
			printf("%2d ", iBWBoard[j][i]);
		}
		printf("%c", '\n');
	}*/
}

void RenewBoard()
{
	cBoard[Pos.y][Pos.x] = (iPlayer == BLACK) ? BLACKtem : WHITEtem;
	iBWBoard[Pos.y][Pos.x] = iPlayer - BLACK + 1;
	if (Postem.x != 16 && Postem.y != 16)
	{
		cBoard[Postem.y][Postem.x] = (iPlayer == WHITE) ? BLACK : WHITE;
	}
}