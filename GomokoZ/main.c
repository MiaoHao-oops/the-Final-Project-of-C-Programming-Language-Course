#include "GomokoZ.h"

int cBoard[SIZE][SIZE]; /*cBoard[][] is used to record the codes of the board*/
int iBWBoard[SIZE][SIZE]; /*iBWBoard[][] is used to record the chess form during the searching*/
int iPlayer; /*iPlayer is used to repersent the present player*/
int iScore[2][SIZE][SIZE]; /*Score information, 0 for BLACK, 1 for WHITE*/
int iFIR; /*if there is five in row*/

char cPVEMode; /*Who gose first, computer or human*/

static const int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
static const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

struct pos Pos, Postem;

static char (*Wel)(void);

int main()
{
	srand((unsigned)time(NULL));

	char cGameModeCode;
	int iBreak;

	Wel = Welcome;
	Init();

	while (1)
	{
		cGameModeCode = (*Wel)();
		if (cGameModeCode == '1') /*PVP*/
		{
			DisplayBoard();

			struct chform  Chform[2], ChfTemp;

			ChfTemp.FAF = ChfTemp.LF = ChfTemp.LR = ChfTemp.TAT = 0;

			while (1)
			{
				if (GetPos()) /*if the input is legal*/
				{
					RenewBoard();

					iFIR = isFiveInRow(iPlayer);
					if (iFIR)
					{
						DisplayBoard();
						printf("%s wins!\n", (iPlayer == BLACK) ? "BLACK" : "WHITE");
						break;
					}

					RenewChform(&Chform[iPlayer - BLACK], iPlayer);
					iPlayer = 25 - iPlayer;
					RenewChform(&Chform[iPlayer - BLACK], iPlayer);
					iPlayer = 25 - iPlayer;

					if (iPlayer == BLACK && isBreaker(Chform[0], ChfTemp))
					{
						while ((iBreak = Break()) == -1)
						{
							DisplayBoard();
							printf("Wrong input, please retry:\n");
						}
						if (iBreak == 1)
						{
							printf("WHITE wins!\n");
							break;
						}
						else if (iBreak == 0)
						{
							DisplayBoard();
							RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
							Postem.x = Pos.x;
							Postem.y = Pos.y;

							/*printf("%d %d %d %d\n", Chform[0].TAT, Chform[0].FAF, Chform[0].LF, Chform[0].LR);
							printf("%d %d %d %d\n", Chform[1].TAT, Chform[1].FAF, Chform[1].LF, Chform[1].LR);
							printf("%d %d %d\n", ChfTemp.TAT, ChfTemp.FAF, ChfTemp.LR);*/

							ChfTemp = Chform[0];

							iPlayer = 25 - iPlayer;
						}
					}
					else
					{
						DisplayBoard();
						RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
						Postem.x = Pos.x;
						Postem.y = Pos.y;

						/*printf("%d %d %d %d\n", Chform[0].TAT, Chform[0].FAF, Chform[0].LF, Chform[0].LR);
						printf("%d %d %d %d\n", Chform[1].TAT, Chform[1].FAF, Chform[1].LF, Chform[1].LR);
						printf("%d %d %d\n", ChfTemp.TAT, ChfTemp.FAF, ChfTemp.LR);*/

						if (iPlayer == BLACK)
						{
							ChfTemp = Chform[0];
						}

						iPlayer = 25 - iPlayer;
					}
				}
				else /*if the input is illegal*/
				{
					DisplayBoard();
					printf("Wrong input, please retry:\n");
				}
				/*printf("%d x=%d y=%d\n", temp, Postem.x, Postem.y);*/
			}
			break;
		}
		else if (cGameModeCode == '2') /*PVE*/
		{
			while ((cPVEMode = PVEMode()) == 'w')
			{
				system(CLEAR);
				printf("Wrong input, please retry:\n");
			}
			if (cPVEMode == '1')
			{
				cBoard[7][7] = BLACK;
				iBWBoard[7][7] = 1;
				Pos.x = Pos.y = 7;
				DisplayBoard();
				RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
				iPlayer = 25 - iPlayer;

				//if (GetPos()) /*if the input is legal*/
				//{
				//	RenewBoard();
				//	DisplayBoard();

				//	if (Pos.x - 7 > 1 || Pos.y - 7 > 1)
				//	{
				//		printf("BLACK wins!\n");
				//		break;
				//	}
				//	else
				//	{
				//		RenewScore(iScore, 1 - iPlayer + BLACK, Pos);

				//		Postem.x = Pos.x;
				//		Postem.y = Pos.y;

				//		iPlayer = 25 - iPlayer;
				//	}
				//}

				while (1)
				{
					if (iPlayer == WHITE)
					{
						if (GetPos()) /*if the input is legal*/
						{
							RenewBoard();

							iFIR = isFiveInRow(iPlayer);
							if (iFIR)
							{
								DisplayBoard();
								printf("WHITE wins!\n");
								break;
							}

							DisplayBoard();
							RenewScore(iScore, 1 - iPlayer + BLACK, Pos);

							Postem.x = Pos.x;
							Postem.y = Pos.y;

							iPlayer = 25 - iPlayer;							
						}
						else /*if the input is illegal*/
						{
							DisplayBoard();
							printf("Wrong input, please retry:\n");
						}
					}
					else if (iPlayer == BLACK)
					{
						/*Pos.x = rand() % 15;
						Pos.y = rand() % 15;*/

						Decision(DEPTH, 1);

						RenewBoard();

						iFIR = isFiveInRow(iPlayer);
						if (iFIR)
						{
							DisplayBoard();
							printf("BLACK wins!\n");
							break;
						}

						DisplayBoard();
						RenewScore(iScore, 1 - iPlayer + BLACK, Pos);

						/*int j, i;

						for (j = 0; j < SIZE; j++)
						{
							for (i = 0; i < SIZE; i++)
							{
								printf("%d ", iBWBoard[j][i]);
							}
							printf("\n");
						}*/
						Postem.x = Pos.x;
						Postem.y = Pos.y;

						iPlayer = 25 - iPlayer;
					}
				}
				break;
			}
			else if (cPVEMode == '2')
			{
				struct chform  Chform[2], ChfTemp;

				ChfTemp.FAF = ChfTemp.LF = ChfTemp.LR = ChfTemp.TAT = 0;

				DisplayBoard();

				if (GetPos())
				{
					RenewBoard();
					DisplayBoard();
					if (Pos.x != 7 || Pos.y != 7)
					{
						printf("WHITE wins!\n");
						break;
					}
					else
					{
						RenewScore(iScore, 1 - iPlayer + BLACK, Pos);

						Postem.x = Pos.x;
						Postem.y = Pos.y;

						iPlayer = 25 - iPlayer;
					}
				}

				int Rand = rand() % 8;

				Pos.x = Postem.x + dx[Rand];
				Pos.y = Postem.y + dy[Rand];

				cBoard[Postem.y][Postem.x] = BLACK;
				cBoard[Pos.y][Pos.x] = WHITEtem;
				iBWBoard[Pos.y][Pos.x] = 2;
				DisplayBoard();
				RenewScore(iScore, 1 - iPlayer + BLACK, Pos);

				Postem.x = Pos.x;
				Postem.y = Pos.y;

				iPlayer = 25 - iPlayer;

				while (1)
				{
					if (iPlayer == BLACK)
					{
						if (GetPos()) /*if the input is legal*/
						{
							RenewBoard();

							iFIR = isFiveInRow(iPlayer);
							if (iFIR)
							{
								DisplayBoard();
								printf("BLACK wins!\n");
								break;
							}

							RenewChform(&Chform[iPlayer - BLACK], iPlayer);
							iPlayer = 25 - iPlayer;
							RenewChform(&Chform[iPlayer - BLACK], iPlayer);
							iPlayer = 25 - iPlayer;

							if (iPlayer == BLACK && isBreaker(Chform[0], ChfTemp))
							{
								while ((iBreak = Break()) == -1)
								{
									DisplayBoard();
									printf("Wrong input, please retry:\n");
								}
								if (iBreak == 1)
								{
									printf("WHITE wins!\n");
									break;
								}
								else if (iBreak == 0)
								{
									DisplayBoard();
									RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
									Postem.x = Pos.x;
									Postem.y = Pos.y;

									/*printf("%d %d %d %d\n", Chform[0].TAT, Chform[0].FAF, Chform[0].LF, Chform[0].LR);
									printf("%d %d %d %d\n", Chform[1].TAT, Chform[1].FAF, Chform[1].LF, Chform[1].LR);
									printf("%d %d %d\n", ChfTemp.TAT, ChfTemp.FAF, ChfTemp.LR);*/

									ChfTemp = Chform[0];

									iPlayer = 25 - iPlayer;
								}
							}
							else
							{
								DisplayBoard();
								RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
								Postem.x = Pos.x;
								Postem.y = Pos.y;

								ChfTemp = Chform[0];

								iPlayer = 25 - iPlayer;
							}
						}
						else /*if the input is illegal*/
						{
							DisplayBoard();
							printf("Wrong input, please retry:\n");
						}
					}
					else if (iPlayer == WHITE)
					{
						/*Pos.x = rand() % 15;
						Pos.y = rand() % 15;*/

						Decision(DEPTH, 0);

						RenewBoard();

						iFIR = isFiveInRow(iPlayer);
						if (iFIR)
						{
							DisplayBoard();
							printf("WHITE wins!\n");
							break;
						}

						DisplayBoard();
						RenewScore(iScore, 1 - iPlayer + BLACK, Pos);

						/*int j, i;

						for (j = 0; j < SIZE; j++)
						{
							for (i = 0; i < SIZE; i++)
							{
								printf("%d ", iBWBoard[j][i]);
							}
							printf("\n");
						}*/

						Postem.x = Pos.x;
						Postem.y = Pos.y;

						iPlayer = 25 - iPlayer;
					}
				}
				break;
			}
			break;
		}
		else if (cGameModeCode == 'e')
		{
			printf("exit\n");
			break;
		}
		else if (cGameModeCode == 'd')
		{
			DisplayBoard();

			struct chform  Chform[2], ChfTemp;

			ChfTemp.FAF = ChfTemp.LF = ChfTemp.LR = ChfTemp.TAT = 0;

			while (1)
			{
				if (GetPos()) /*if the input is legal*/
				{
					//RenewBoard();
					cBoard[Pos.y][Pos.x] = BLACK;
					iBWBoard[Pos.y][Pos.x] = 1;
					RenewChform(&Chform[iPlayer - BLACK], BLACK);
					if (iPlayer == BLACK && isBreaker(Chform[0], ChfTemp))
					{
						while ((iBreak = Break()) == -1)
						{
							DisplayBoard();
							printf("Wrong input, please retry:\n");
						}
						if (iBreak == 1)
						{
							printf("WHITE wins!\n");
							break;
						}
						else if (iBreak == 0)
						{
							DisplayBoard();
							RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
							Postem.x = Pos.x;
							Postem.y = Pos.y;

							printf("%d %d %d %d\n", Chform[0].TAT, Chform[0].FAF, Chform[0].LF, Chform[0].LR);
							printf("%d %d %d\n", ChfTemp.TAT, ChfTemp.FAF, ChfTemp.LR);
							ChfTemp = Chform[0];
							iPlayer = 25 - iPlayer;
						}
					}
					else
					{
						DisplayBoard();
						RenewScore(iScore, 1 - iPlayer + BLACK, Pos);
						printf("%d %d %d %d\n", Chform[0].TAT, Chform[0].FAF, Chform[0].LF, Chform[0].LR);
						printf("%d %d %d\n", ChfTemp.TAT, ChfTemp.FAF, ChfTemp.LR);
						if (iPlayer == BLACK)
						{
							ChfTemp = Chform[0];
						}
					}
				}
				else /*if the input is illegal*/
				{
					DisplayBoard();
					printf("Wrong input, please retry:\n");
				}
				/*printf("%d x=%d y=%d\n", temp, Postem.x, Postem.y);*/
			}
			break;
		}
		else
		{
			system(CLEAR);
			Wel = WelcomeStupid;
		}
	}
}