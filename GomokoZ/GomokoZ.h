#include <stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>

#define DEPTH 5
#define BLACK 12
#define WHITE 13
#define BLACKtem 10
#define WHITEtem 11
#define SIZE 15
#define CLEAR "cls"

extern int cBoard[SIZE][SIZE]; /*cBoard[][] is used to record the codes of the board*/
extern int iBWBoard[SIZE][SIZE]; /*iBWBoard[][] is used to record the chess form during the searching*/
extern int iPlayer; /*iPlayer is used to repersent the present player*/
extern int iScore[2][SIZE][SIZE]; /*Score information, 0 for BLACK, 1 for WHITE*/
extern int iFIR; /*if there is five in row*/

extern char cPVEMode;

struct pos
{
	int x;
	int y;
}; /*Postems are used to record the position of last step*/
struct chform
{
	int TwoAT; /*TwoAT*/
	int TAT; /*three and three*/
	int FAF; /*four and four*/
	int LF; /*live four*/
	int LR; /*long row*/
	int FIR; /*five in row*/
}; /*chess form information*/
struct dtn
{
	int iscore[2][SIZE][SIZE];
	struct chform Chform[2];
	int alpha;
	int beta;
}; /*decision tree node*/
struct nc
{
	int top;
	struct pos pt[SIZE * SIZE];
}; /*node choices, a hash table*/

extern struct pos Pos, Postem;


/*functions in welcome.c*/
char Welcome(void);
char WelcomeStupid(void);
char PVEMode(void);

/*functions in chessboard.c*/
void Init(void);
void DisplayBoard(void);
void RenewBoard(void);

/*functions in posop.c*/
int GetPos(void);
char GetLine(void);
char getch(void);
void ungetch(char);

/*functions in rule.c*/
int isFiveInRow(int);
int isTwoAndTwo(int);
int isThreeAndThree(int);
int isFourAndFour(int);
int isLiveFour(int);
int isLongRow(int);
void RenewChform(struct chform *, int);
int isBreaker(struct chform, struct chform);
int Break(void);

/*functions in scoreop.c*/
void RenewScore(int [][SIZE][SIZE], int, struct pos);
void AddScore(int, int, int [][SIZE][SIZE], int, struct pos);
int Assess(struct chform[]);

/*functions in deepsearch.c*/
void Decision(int, int);
int DFS(struct pos, int, int, int, int);
void CopyArray(int[][SIZE][SIZE], int[][SIZE][SIZE]);
int CreateTab(int, int);
void InitTab(int);