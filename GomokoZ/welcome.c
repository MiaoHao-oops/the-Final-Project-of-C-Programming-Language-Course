/*
	This file includes functions used to present initial interface.
*/

#include "GomokoZ.h"

char Welcome()
{
	char cGameModeCode;

	printf("Welcome to GomokoZ!\n");
	printf("Please choose the game mode, 1 for PVP, 2 for PVE, e for exit: ");

	cGameModeCode = getch();

	if (cGameModeCode == '1' && (cGameModeCode = getch()) == '\n')
	{
		return '1'; /*PVP*/
	}
	else if (cGameModeCode == '2' && (cGameModeCode = getch()) == '\n')
	{
		return '2'; /*PVE*/
	}
	else if (cGameModeCode == 'e' && (cGameModeCode = getch()) == '\n')
	{
		return 'e';
	}
	else
	{
		for (; cGameModeCode != '\n'; cGameModeCode = getch())
		{
			;
		}
		return 'w'; /*mode input wrong input*/
	}
}/*return the game mode code*/

char WelcomeStupid()
{
	char cGameModeCode;

	printf("Welcome to GomokoZ!\n");
	printf("You have input the game mode with THE WRONG CODE, PLEASE RETRY :( \n");
	printf("1 FOR PVP, 2 FOR PVE, e FOR EXIT!\n");
	printf("1 FOR PVP, 2 FOR PVE, e FOR EXIT!\n");
	printf("1 FOR PVP, 2 FOR PVE, e FOR EXIT: ");

	cGameModeCode = getch();


	if (cGameModeCode == '1' && (cGameModeCode = getch()) == '\n')
	{
		return '1'; /*PVP*/
	}
	else if (cGameModeCode == '2' && (cGameModeCode = getch()) == '\n')
	{
		return '2'; /*PVE*/
	}
	else if (cGameModeCode == 'e' && (cGameModeCode = getch()) == '\n')
	{
		return 'e';
	}
	else
	{
		for (; cGameModeCode != '\n'; cGameModeCode = getch())
		{
			;
		}
		return 'w'; /*mode input wrong input*/
	}
}/*return the game mode code*/

char PVEMode()
{
	char cFirstHand;
	printf("Please choose the first hand player, 1 for computer, 2 for human: ");

	cFirstHand = getch();

	if (cFirstHand == '1' && (cFirstHand = getch()) == '\n') /*computer goes first*/
	{
		return '1'; /*PVP*/
	}
	else if (cFirstHand == '2' && (cFirstHand = getch()) == '\n') /*human goes first*/
	{
		return '2'; /*PVE*/
	}
	else
	{
		for (; cFirstHand != '\n'; cFirstHand = getch())
		{
			;
		}
		return 'w'; /*mode input wrong input*/
	}
}