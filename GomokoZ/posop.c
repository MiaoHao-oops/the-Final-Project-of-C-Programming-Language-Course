/*
	This file includes functions to get the input position of the chess piece.
*/

#include "GomokoZ.h"

int GetPos() 
{
	char cInputState;

	cInputState = GetLine();
	if (cInputState == (char)255 || !(1 <= cBoard[Pos.y][Pos.x] && cBoard[Pos.y][Pos.x] <= 9)) /*illegal input*/
	{
		return 0;
	}
	else
	{
		return 1;
	}
}/*if the input is satisfactory, return 1, else return 0*/

char GetLine()
{
	char cTemp = getch();
	Pos.x = 0;
	Pos.y = 0;

	if (isdigit(cTemp)) /*begin with number*/
	{
		Pos.y = cTemp - '0';
		while (isdigit(cTemp = getch()))
		{
			Pos.y = Pos.y * 10 + (cTemp - '0');
			if (Pos.y > 15)
			{
				for (; cTemp != '\n'; cTemp = getch())
				{
					;
				}	
				return 255; /*the integer is too large!*/
			}
		}
		if (('a' <= cTemp && cTemp <= 'o') || ('A' <= cTemp && cTemp <= 'O'))
		{
			Pos.x = ('a' <= cTemp && cTemp <= 'o') ? cTemp - 'a' + 1 : cTemp - 'A' + 1; /*decide upper or lower case*/
			cTemp = getch();
			if (cTemp != '\n')
			{
				for (; cTemp != '\n'; cTemp = getch())
				{
					;
				}
				return 255;
			}
		}
		else
		{
			for (; cTemp != '\n'; cTemp = getch())
			{
				;
			}
			return 255;
		}
	}
	else if (('a' <= cTemp && cTemp <= 'o') || ('A' <= cTemp && cTemp <= 'O'))
	{
		Pos.x = ('a' <= cTemp && cTemp <= 'o') ? cTemp - 'a' + 1 : cTemp - 'A' + 1; /*decide upper or lower case*/
		if (isdigit(cTemp = getch()))
		{
			Pos.y = cTemp - '0';
			while (isdigit(cTemp = getch()))
			{
				Pos.y = Pos.y * 10 + (cTemp - '0');
				if (Pos.y > 15)
				{	
					for (; cTemp != '\n'; cTemp = getch())
					{
						;
					}
					return 255; /*the integer is too large!*/
				}
			}
			if (cTemp != '\n')
			{
				for (; cTemp != '\n'; cTemp = getch())
				{
					;
				}
				return 255;
			}
		}
		else
		{
			for (; cTemp != '\n'; cTemp = getch())
			{
				;
			}
			return 255;
		}
	}
	else
	{
		for (; cTemp != '\n'; cTemp = getch())
		{
			;
		}
		return 255;
	}

	Pos.x--;
	Pos.y = 15 - Pos.y;
	/*cBoard[Pos.y][Pos.x] is the array element which will be changed*/

	return 0;
}

#define BUFSIZE 10
static char buf[BUFSIZE];
static int bufp = 0;

char getch()
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(char c)
{
	if (bufp >= BUFSIZE)
	{
		printf("ungetch: too many characters!\n");
	}
	else
	{
		buf[bufp++] = c;
	}
}