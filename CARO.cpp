#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define point	10
#define TOP	1
#define BOT	TOP+2*SIZE
#define LEFT	3
#define RIGHT	LEFT+4*SIZE
#define SIZE	20
#define ai	(A.y-TOP-1)/2
#define aj	(A.x-LEFT-2)/4

struct PLAYER{
	int x, y, value, score;
};

void veBanCo();
void game();
void endGame(PLAYER A, PLAYER B);
void init(PLAYER &A, int x, int y, int value);
void player(int board[][SIZE], PLAYER &A);
void ghiDiem(int board[][SIZE], PLAYER &A);
int row(int board[][SIZE], PLAYER A);
int col(int board[][SIZE], PLAYER A);
int cheoChinh(int board[][SIZE], PLAYER A);
int cheoPhu(int board[][SIZE], PLAYER A);

void resizeConsole(int width, int height);
void textColor(int value);
void gotoXY(int x, int y);

int main(){
	resizeConsole(980,1200);
	game();
	return 0;
}

void game(){
	int board[SIZE][SIZE]={0}, x=LEFT+2*SIZE-2, y=TOP+SIZE+1;
	veBanCo();
	PLAYER A,B;
	init(A,x,y,3);	init(B,x,y+2,4);	A.score=0;	B.score=0;
	while (A.score<point && B.score<point){
		player(board,A);	ghiDiem(board,A);
		if (A.score<point){
			player(board,B);	ghiDiem(board,B);
		}
	}
	endGame(A,B);
}

void endGame(PLAYER A, PLAYER B){
	PLAYER WIN;
	if (A.score>B.score)	WIN=A; else WIN=B;	//Khong xay ra truong hop A==B
	int x=5*SIZE, y=TOP+SIZE;
	gotoXY(x,y);		textColor(WIN.value);	printf("WINNER");
	gotoXY(x-6,y+2);	textColor(5);		printf("Press ENTER to REPLAY!");
	gotoXY(x-5,y+4);	textColor(7);		printf("Press ESC to EXIT!");
	char key;
	while (1){
		if (kbhit()){
			key=getch();
			switch (key){
				case 13:{
					system("cls");	game();	break;
				}
				case 27:{
					system("cls");	return;
				}
			}
		}
	}
}

void ghiDiem(int board[][SIZE], PLAYER &A){
	int dk1=row(board,A), dk2=col(board,A), dk3=cheoChinh(board,A), dk4=cheoPhu(board,A);
	if (dk1+dk2+dk3+dk4!=0)
		A.score+=(dk1+dk2+dk3+dk4)*point;
}

int col(int board[][SIZE], PLAYER A){
	int i=ai, j=ai, col=aj;
	while (board[i][col]==A.value && i>=0)		i--;
	while (board[j][col]==A.value && j<=SIZE)	j++;
	if (j-i-1>=5)	return 1;
	return 0;
}

int row(int board[][SIZE], PLAYER A){
	int i=aj, j=aj, row=ai;
	while (board[row][i]==A.value && i>=0)		i--;
	while (board[row][j]==A.value && j<=SIZE)	j++;
	if (j-i-1>=5)	return 1;
	return 0;
}

int cheoChinh(int board[][SIZE], PLAYER A){
	int ix=ai, iy=aj;
	while (board[ix][iy]==A.value && ix>=0 && iy>=0)
	{	ix--;		iy--;	}
	int jx=ai, jy=aj;
	while (board[jx][jy]==A.value && jx<=SIZE && jy<=SIZE)
	{	jx++;	jy++;	}
	int sqr_distance=(jx-ix-1)*(jx-ix-1)+(jy-iy-1)*(jy-iy-1);
	if (sqr_distance>=50)	return 1;
	return 0;
}

int cheoPhu(int board[][SIZE], PLAYER A){
	int ix=ai, iy=aj;
	while (board[ix][iy]==A.value && ix<=SIZE && iy>=0)
	{	ix--;	iy++;	}
	int jx=ai, jy=aj;
	while (board[jx][jy]==A.value && jx>=0 && jy<=SIZE)
	{	jx++;	jy--;	}
	int sqr_distance=(jx-ix-1)*(jx-ix-1)+(jy-iy+1)*(jy-iy+1);
	if (sqr_distance>=50)	return 1;
	return 0;
}

void init(PLAYER &A, int x, int y, int value){
	A.x=x;	A.y=y;	A.value=value;
}

void player(int board[][SIZE], PLAYER &A){
	char key;
	while (1){
		gotoXY(A.x,A.y);
		if (kbhit()){
			key=getch();
			switch ((int)key){
				case 13:{
					if (board[ai][aj]==0){
						board[ai][aj]=A.value;
						textColor(A.value);
						if (A.value%2)	printf("X");else	printf("O");
						return;
					}
					else break;
				}
				case 72:{
					if (A.y-2<TOP+1)	A.y=BOT-1;	else	A.y-=2;		break;
				}
				case 75:{
					if (A.x-4<LEFT+2)	A.x=RIGHT-2;else	A.x-=4;		break;
				}
				case 77:{
					if (A.x+4>RIGHT)	A.x=LEFT+2;	else	A.x+=4;		break;
				}
				case 80:{
					if (A.y+2>BOT)		A.y=TOP+1;	else	A.y+=2;		break;
				}
			}
		}
	}
}

void veBanCo(){
	int i,j;
	gotoXY(LEFT+1,TOP);					//TOP
	for (i=0;i<(2*SIZE);i++)
		if (i%2)	printf("%c",194);	else	printf("%c%c%c",196,196,196);
	gotoXY(LEFT+1,BOT);					//BOT
	for (i=0;i<2*SIZE;i++)
		if (i%2)	printf("%c",193);	else	printf("%c%c%c",196,196,196);
	for (i=0;i<2*SIZE;i++){
		gotoXY(LEFT,TOP+i);	
		if (i%2)	printf("%c",179);	else	printf("%c",195);
		gotoXY(RIGHT,TOP+i);
		if (i%2)	printf("%c",179);	else	printf("%c",180);
	}
	char S0[200], S1[200];
	for (int j=0;j<4*SIZE-1;j++)
		if (j%4==0)		S0[j]=179;	else S0[j]=' ';
	for (int j=0;j<4*SIZE-1;j++)
		if ((j+1)%4==0)	S1[j]=197;		else S1[j]=196;
	S1[4*SIZE-1]='\0';	S0[4*SIZE-1]='\0';
	i=1;
	while (i<2*SIZE-1){
		gotoXY(LEFT,TOP+i++);	printf("%s",S0);
		gotoXY(LEFT+1,TOP+i++);	printf("%s",S1);
	}
	gotoXY(LEFT,TOP+i);	printf("%s",S0);
	gotoXY(LEFT,TOP);	printf("%c",218);
	gotoXY(RIGHT,TOP);	printf("%c",191);
	gotoXY(LEFT,BOT);	printf("%c",192);
	gotoXY(RIGHT,BOT);	printf("%c",217);
}

void resizeConsole(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void textColor (int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}

void gotoXY(int x, int y){
	static HANDLE h=NULL;
	if (!h)	h=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c={x,y};
	SetConsoleCursorPosition(h,c);
}
