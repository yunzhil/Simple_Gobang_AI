#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLINE 15
#pragma warning(disable: 4996)//VS编译时会对scanf报错，所以加入此行代码
typedef struct MYPOINT//本想用于深层搜索，但是未能完成
{
	int x;
	int y;
	int score;
}MYPOINT;
int chessboard[MAXLINE][MAXLINE];//棋盘数组
void drawboard(int array[MAXLINE][MAXLINE]);//绘制棋盘函数
void AI(int array[MAXLINE][MAXLINE], int first);//AI主函数
void Read1(int array[MAXLINE][MAXLINE]);//读取输入棋子位置函数
int check(int array[MAXLINE][MAXLINE]);//检查是否结束棋局函数
int subscoreBlack(int array[MAXLINE][MAXLINE], int iCmp, char chess[10], int ic, int jc);//根据棋型，单点估值函数
int subscoreWhite(int array[MAXLINE][MAXLINE], int iCmp, char chess[10], int ic, int jc);//根据棋型，单点估值函数
int scoreblack(int i, int j, int array[MAXLINE][MAXLINE], int first);//对棋盘上每一点进行估值(调用subscoreBlack）
int scorewhite(int i, int j, int array[MAXLINE][MAXLINE], int first);//对棋盘上每一点进行估值(调用subscoreWhite）
int mycmp(const void *a, const void *b);//本想用于深层搜索，但是未能完成



/******************************************************************************************************************/
int main(void)//主函数
{
	int iCross, iVertical, game, first;
	game = -1;
	for (iCross = 0; iCross < MAXLINE; iCross++)
		for (iVertical = 0; iVertical < MAXLINE; iVertical++)
			chessboard[iCross][iVertical] = 0;//初始化数组

	printf("先手？");
	scanf("%d", &first);
	if (first == 1)
	{
		chessboard[7][7] = 2;
	}//先手落子

	while (1)//游戏进程
	{
		drawboard(chessboard);
		Read1(chessboard);
		if ((game = check(chessboard)) != -1)
			break;
		AI(chessboard, first);	
		if ((game = check(chessboard)) != -1)
			break;
	}
	if (game == 0)
		printf("You Win!");
	else if (game == 1)
		printf("You lose");
	else
		printf("Something Wrong");
	system("pause");
	return 0;
}
/******************************************************************************************************************/


/******************************************************************************************************************/
void drawboard(int array[MAXLINE][MAXLINE])//绘制棋盘
{
	int i, j;
	for (i = MAXLINE; i > 9; i--)
	{
		printf("%d", i);
		for (j = 0; j < 14; j++)
		{
			if (array[i-1][j] == 0)
				printf(" %c", 43);
			else if (array[i-1][j] == 1)
				printf(" %c", 1);
			else if (array[i-1][j] == 2)
				printf(" %c", 2);
			else
				printf("wrong");
		}
		if (array[i-1][14] == 0)
			printf(" %c\n", 43);
		else if (array[i-1][14] == 1)
			printf(" %c\n", 1);
		else if (array[i-1][14] == 2)
			printf(" %c\n", 2);
		else
			printf("wrong");
	}
	for (i = 8; i >= 0; i--)
	{
		printf("0%d", i+1);
		for (j = 0; j < 14; j++)
		{
			if (array[i][j] == 0)
				printf(" %c", 43);
			else if (array[i][j] == 1)
				printf(" %c", 1);
			else if (array[i][j] == 2)
				printf(" %c", 2);
			else
				printf("wrong");
		}
		if (array[i][14] == 0)
			printf(" %c\n", 43);
		else if (array[i][14] == 1)
			printf(" %c\n", 1);
		else if (array[i][14] == 2)
			printf(" %c\n", 2);
		else
			printf("wrong");
	}
	
	printf("   A B C D E F G H I J K L M N O\n");
	printf("Your turn,please describe your chessman's location like 01A\n");
}
/******************************************************************************************************************/


/******************************************************************************************************************/
void Read1(int array[MAXLINE][MAXLINE])//读取玩家落子
{
	int i, j, a_1, a_2;
	char read[4] = { 0 };
	while (1)
	{
		scanf_s("%s", read, 4);//此处用scanf_s，不同编译器可能会出问题，请老师注意！！
		j = read[2] - 'A';
		a_1 = read[0] - '0';
		a_2 = read[1] - '0';
		i = 10 * a_1 + a_2 - 1;
		if (array[i][j] == 1 || array[i][j] == 2)
		{
			printf("wrong location");
		}
		else
		{
			array[i][j] = 1;
			break;
		}
	}


}
/******************************************************************************************************************/



/******************************************************************************************************************/
int check(int array[MAXLINE][MAXLINE])//检查棋局是否结束
{
	int iCross, iVertical, i;
	i = -1;
	for (iCross = 0; iCross < MAXLINE; iCross++)//横向
		for (iVertical = 0; iVertical < 11; iVertical++)
		{
			if ((array[iCross][iVertical] == 1) && (array[iCross][iVertical + 1] == 1) && (array[iCross][iVertical + 2] == 1) && (array[iCross][iVertical + 3] == 1) && (array[iCross][iVertical + 4] == 1))
			{
				i = 0;
				break;
			}
			else if ((array[iCross][iVertical] == 2) && (array[iCross][iVertical + 1] == 2) && (array[iCross][iVertical + 2] == 2) && (array[iCross][iVertical + 3] == 2) && (array[iCross][iVertical + 4] == 2))
			{
				i = 1;
				break;
			}
		}
	for (iCross = 0; iCross < 11; iCross++)//纵向
		for (iVertical = 0; iVertical < MAXLINE; iVertical++)
		{
			if ((array[iCross][iVertical] == 1) && (array[iCross + 1][iVertical] == 1) && (array[iCross + 2][iVertical] == 1) && (array[iCross + 3][iVertical] == 1) && (array[iCross + 4][iVertical] == 1))
			{
				i = 0;
				break;
			}
			else if ((array[iCross][iVertical] == 2) && (array[iCross + 1][iVertical] == 2) && (array[iCross + 2][iVertical] == 2) && (array[iCross + 3][iVertical] == 2) && (array[iCross + 4][iVertical] == 2))
			{
				i = 1;
				break;
			}
		}
	for (iCross = 2; iCross < 13; iCross++)//右下斜
		for (iVertical = 2; iVertical < 13; iVertical++)
		{
			if ((array[iCross][iVertical] == 1) && (array[iCross + 1][iVertical + 1] == 1) && (array[iCross + 2][iVertical + 2] == 1) && (array[iCross - 1][iVertical - 1] == 1) && (array[iCross - 2][iVertical - 2] == 1))
			{
				i = 0;
				break;
			}
			else if ((array[iCross][iVertical] == 2) && (array[iCross + 1][iVertical + 1] == 2) && (array[iCross + 2][iVertical + 2] == 2) && (array[iCross - 1][iVertical - 1] == 2) && (array[iCross - 2][iVertical - 2] == 2))
			{
				i = 1;
				break;
			}

		}
	for (iCross = 2; iCross < 13; iCross++)//左下斜
		for (iVertical = 2; iVertical < 13; iVertical++)
		{
			if ((array[iCross][iVertical] == 1) && (array[iCross + 1][iVertical - 1] == 1) && (array[iCross + 2][iVertical - 2] == 1) && (array[iCross - 1][iVertical + 1] == 1) && (array[iCross - 2][iVertical + 2] == 1))
			{
				i = 0;
				break;
			}
			else if ((array[iCross][iVertical] == 2) && (array[iCross + 1][iVertical - 1] == 2) && (array[iCross + 2][iVertical - 2] == 2) && (array[iCross - 1][iVertical + 1] == 2) && (array[iCross - 2][iVertical + 2] == 2))
			{
				i = 1;
				break;
			}
		}
	return i;
}
/******************************************************************************************************************/



/******************************************************************************************************************/
void AI(int array[MAXLINE][MAXLINE], int first)
{
	int iCross, iVert;
	int i = 0;
	int j = 0;
	int isave1 = 0, isave2 = 0;
	int jsave1 = 0, jsave2 = 0;
	int maxscore1, maxscore2;
	int scoresave1[MAXLINE][MAXLINE];//用于存储每一点分数
	int scoresave2[MAXLINE][MAXLINE];//用于存储每一点分数
	for (iCross = 0; iCross < MAXLINE; iCross++)
		for (iVert = 0; iVert < MAXLINE; iVert++)
		{
			scoresave1[iCross][iVert] = scoreblack(iCross, iVert, chessboard, first);//调用scoreblack，将每一点分数存入数组

		}
	/*MYPOINT oneDscore1[225];
	for (iCross = 0; iCross < 15; iCross++)
		for (iVert = 0; iVert < 15; iVert++)
		{
			oneDscore1[15 * iCross + iVert].x = iCross;
			oneDscore1[15 * iCross + iVert].y = iVert;
			oneDscore1[15 * iCross + iVert].score = scoresave1[iCross][iVert];
		}

	qsort(oneDscore1, 225, sizeof(oneDscore1[0]), mycmp);*/ //本想用于深层搜索，未能完成
	maxscore1 = scoresave1[0][0];
	for (i = 0; i < MAXLINE; i++)
		for (j = 0; j < MAXLINE; j++)
			if (scoresave1[i][j]>maxscore1)//挑选最大点分数
			{
				isave1 = i;
				jsave1 = j;
				maxscore1 = scoresave1[i][j];
			}
	for (iCross = 0; iCross < MAXLINE; iCross++)
		for (iVert = 0; iVert < MAXLINE; iVert++)
		{
			scoresave2[iCross][iVert] = scorewhite(iCross, iVert, chessboard, first);

		}
	maxscore2 = scoresave2[0][0];
	for (i = 0; i < MAXLINE; i++)
		for (j = 0; j < MAXLINE; j++)
			if (scoresave2[i][j]>maxscore2)
			{
				isave2 = i;
				jsave2 = j;
				maxscore2 = scoresave2[i][j];
			}
	
	if (maxscore2 > maxscore1)//判断进攻还是防守
	{
		array[isave2][jsave2] = 2;
		drawboard(chessboard);
		printf("%d,%c\n", isave2+1, jsave2+'A');
	}
	else
	{
		array[isave1][jsave1] = 2;
		drawboard(chessboard);
		printf("%d,%c\n", isave1+1, jsave1+'A' );
	}


}
/******************************************************************************************************************/



/******************************************************************************************************************/
int scoreblack(int i, int j, int array[MAXLINE][MAXLINE], int first)//采用字符串比较的方式，来比较棋型库与棋盘上棋型，从而得出分数
{
	int score1, score2, score3, score4;//四个方向分数
	int countD4=0;//用于双四判断
	int score;//返回值
	int length;//字符串长度
	int iblack;
	if (array[i][j] != 0)
		return -100000;
	if (i < 4)
	{
		score1 = 0;
		array[i][j] = 2;
		length = i + 4 + 1;
		char black[10];
		for (iblack = 0; iblack < length; iblack++)
		{
			black[iblack] = array[iblack][j] + '0';//读取字符串
		}
		black[iblack] = '\0';
		score1 = subscoreBlack(chessboard, i, black, i, j);
		array[i][j] = 0;

	}
	else if (i > 11)
	{
		score1 = 0;
		array[i][j] = 2;
		length = 14 - i + 4 + 1;
		char black[10];
		int m = i - 4;
		for (iblack = 0; iblack < length; iblack++, m++)
		{
			black[iblack] = array[m][j] + '0';
		}
		black[iblack] = '\0';
		score1 = subscoreBlack(chessboard, 4, black, i, j);
		array[i][j] = 0;
	}
	else
	{
		score1 = 0;
		array[i][j] = 2;
		length = 9;
		char black[10];
		int m = i - 4;
		for (iblack = 0; iblack < length; iblack++, m++)
		{
			black[iblack] = array[m][j] + '0';
		}
		black[iblack] = '\0';
		score1 = subscoreBlack(chessboard, 4, black, i, j);
		array[i][j] = 0;
	}

	if (j < 4)
	{
		score2 = 0;
		array[i][j] = 2;
		length = j + 4 + 1;
		char black[10];
		for (iblack = 0; iblack < length; iblack++)
		{
			black[iblack] = array[i][iblack] + '0';
		}
		black[iblack] = '\0';
		score2 = subscoreBlack(chessboard, j, black, i, j);
		array[i][j] = 0;
	}
	else if (j > 11)
	{
		score2 = 0;
		array[i][j] = 2;
		length = 14 - j + 4 + 1;
		char black[10];
		int m = j - 4;
		for (iblack = 0; iblack < length; iblack++, m++)
		{
			black[iblack] = array[i][m] + '0';
		}
		black[iblack] = '\0';
		score2 = subscoreBlack(chessboard, 4, black, i, j);
		array[i][j] = 0;
	}
	else
	{
		score2 = 0;
		array[i][j] = 2;
		length = 9;
		char black[10];
		int m = j - 4;
		for (iblack = 0; iblack < length; iblack++, m++)
		{
			black[iblack] = array[i][m] + '0';
		}
		black[iblack] = '\0';
		score2 = subscoreBlack(chessboard, 4, black, i, j);
		array[i][j] = 0;
	}

	if ((i < 4) && (j < 4))
	{
		score3 = 0;
		array[i][j] = 2;
		if (i < j)
		{
			length = i + 4 + 1;
			char black[10];
			int j_count = j - i;
			for (iblack = 0; iblack < length; iblack++, j_count++)
			{
				black[iblack] = array[iblack][j_count] + '0';
			}
			black[iblack] = '\0';
			score3 = subscoreBlack(chessboard, i, black, i, j);
			array[i][j] = 0;
		}
		else
		{
			score3 = 0;
			length = j + 4 + 1;
			char black[10];
			int i_count = i - j;
			for (iblack = 0; iblack < length; iblack++, i_count++)
			{
				black[iblack] = array[i_count][iblack] + '0';
			}
			black[iblack] = '\0';
			score3 = subscoreBlack(chessboard, j, black, i, j);
			array[i][j] = 0;
		}
	}
	else if ((i < 4) && (j>11))
	{
		score3 = 0;
		array[i][j] = 2;
		length = i + 1 + 14 - j;
		char black[10];
		int iv, ic;
		iv = j - i;
		for (ic = 0; ic < length; ic++, iv++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, length - 4, black, i, j);
		array[i][j] = 0;

	}
	else if ((j < 4) && (i>11))
	{
		array[i][j] = 2;
		score3 = 0;
		length = j + 1 + 14 - i;
		char black[10];
		int iv, ic;
		ic = i - j;
		for (iv = 0; iv < length; ic++, iv++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, length - 4, black, i, j);
		array[i][j] = 0;
	}
	else if ((j > 11) && (i > 11))
	{
		score3 = 0;
		array[i][j] = 2;
		if (i < j)

		{
			length = 19 - j;
			char black[10];
			int iv, ic;
			ic = i - 4;
			iv = j - 4;
			for (iblack = 0; iblack < length; ic++, iv++, iblack++)
			{
				black[iblack] = array[ic][iv] + '0';
			}
			black[iblack] = '\0';
			score3 = subscoreBlack(chessboard, 14 - j + 1, black, i, j);
			array[i][j] = 0;
		}

		else
		{
			length = 19 - i;
			char black[10];
			int iv, ic;
			ic = i - 4;
			iv = j - 4;
			for (iblack = 0; iblack < length; ic++, iblack++, iv++)
			{
				black[iblack] = array[ic][iv] + '0';
			}
			black[iblack] = '\0';
			score3 = subscoreBlack(chessboard, 14 - i + 1, black, i, j);
			array[i][j] = 0;
		}
	}
	else if ((i < 4) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 2;
		length = i + 4 + 1;
		char black[10];
		int j_count = j - i;
		for (iblack = 0; iblack < length; iblack++, j_count++)
		{
			black[iblack] = array[iblack][j_count] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, i, black, i, j);
		array[i][j] = 0;
	}
	else if ((i > 11) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 2;
		length = 19 - i;
		char black[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic++, iblack++, iv++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, 14 - i + 1, black, i, j);
		array[i][j] = 0;
	}
	else if ((j < 4) && (i >= 4) && (i <= 11))
	{
		array[i][j] = 2;
		score3 = 0;
		length = j + 4 + 1;
		char black[10];
		int i_count = i - j;
		for (iblack = 0; iblack < length; iblack++, i_count++)
		{
			black[iblack] = array[i_count][iblack] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, j, black, i, j);
		array[i][j] = 0;
	}
	else if ((j >11) && (i >= 4) && (i <= 11))
	{
		array[i][j] = 2;
		length = 19 - j;
		char black[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic++, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, 14 - j + 1, black, i, j);
		array[i][j] = 0;
	}
	else
	{
		array[i][j] = 2;
		score3 = 0;
		length = 9;
		char black[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic++, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, 4, black, i, j);
		array[i][j] = 0;
	}
	if ((i <= 4) && (j <= 4))
	{
		array[i][j] = 2;
		score4 = 0;
		length = i + j + 1;
		char black[10];
		int iv, ic;
		ic = i + j;
		iv = 0;
		for (iblack = 0; iblack < length; ic--, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score4 = subscoreBlack(chessboard, length - 4, black, i, j);
		array[i][j] = 0;
	}
	else if ((i >= 11) && (j >= 11))
	{
		array[i][j] = 2;
		score4 = 0;
		length = 29 - i - j;
		char black[10];
		int iv, ic;
		ic = 14;
		iv = i + j - 14;
		for (iblack = 0; iblack < length; ic--, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score4 = subscoreBlack(chessboard, length - 4, black, i, j);
		array[i][j] = 0;
	}
	else if ((i<4) && (j>11))
	{
		array[i][j] = 2;
		score4 = 0;
		if (i + j <= 14)
		{
			length = 5 + i;
			char black[10];
			int iv, ic;
			ic = i + 4;
			iv = j - 4;
			for (iblack = 0; iblack < length; ic--, iv++, iblack++)
			{
				black[iblack] = array[ic][iv] + '0';
			}
			black[iblack] = '\0';
			score4 = subscoreBlack(chessboard, i + 1, black, i, j);
			array[i][j] = 0;
		}
		else
		{
			length = 19 - j;
			char black[10];
			int iv, ic;
			ic = i + 4;
			iv = j - 4;
			for (iblack = 0; iblack < length; ic--, iv++, iblack++)
			{
				black[iblack] = array[ic][iv] + '0';
			}
			black[iblack] = '\0';
			score4 = subscoreBlack(chessboard, 15 - j, black, i, j);

			array[i][j] = 0;
		}
	}
	else if ((i > 11) && (j < 4))
	{
		array[i][j] = 2;
		score4 = 0;
		if (i + j <= 14)
		{
			length = 5 + j;
			char black[10];
			int iv, ic;
			ic = i + j;
			iv = 0;
			for (iblack = 0; iblack < length; ic--, iv++, iblack++)
			{
				black[iblack] = array[ic][iv] + '0';
			}
			black[iblack] = '\0';
			score4 = subscoreBlack(chessboard, j + 1, black, i, j);
			array[i][j] = 0;
		}
		else
		{
			length = 19 - i;
			char black[10];
			int iv, ic;
			ic = 14;
			iv = j + i - 14;
			for (iblack = 0; iblack < length; ic--, iv++, iblack++)
			{
				black[iblack] = array[ic][iv] + '0';
			}
			black[iblack] = '\0';
			score4 = subscoreBlack(chessboard, 15 - i, black, i, j);
			array[i][j] = 0;
		}
	}
	else if ((j < 4) && (i <= 11) && (i >= 4))
	{
		array[i][j] = 2;
		length = 5 + j;
		char black[10];
		int iv, ic;
		iv = 0;
		ic = i + j;
		for (iblack = 0; iblack < length; ic--, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score4 = subscoreBlack(chessboard, 15 - i, black, i, j);
		array[i][j] = 0;

	}
	else if ((j > 11) && (i <= 11) && (i >= 4))
	{
		array[i][j] = 2;
		length = 19 - j;
		char black[10];
		int iv, ic;
		ic = i + 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic--, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score4 = subscoreBlack(chessboard, 15 - j, black, i, j);

		array[i][j] = 0;
	}
	else if ((i < 4) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 2;
		length = 5 + i;
		char black[10];
		int iv, ic;
		ic = i + 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic--, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score4 = subscoreBlack(chessboard, i + 1, black, i, j);
		array[i][j] = 0;
	}
	else if ((i > 11) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 2;
		length = 19 - i;
		char black[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic++, iblack++, iv++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score3 = subscoreBlack(chessboard, 14 - i + 1, black, i, j);
		array[i][j] = 0;
	}
	else
	{
		array[i][j] = 2;
		score4 = 0;
		length = 9;
		char black[10];
		int iv, ic;
		ic = i + 4;
		iv = j - 4;
		for (iblack = 0; iblack < length; ic--, iv++, iblack++)
		{
			black[iblack] = array[ic][iv] + '0';
		}
		black[iblack] = '\0';
		score4 = subscoreBlack(chessboard, 4, black, i, j);
		array[i][j] = 0;
	}
	score = score1 + score2 + score3 + score4;
	if (first == 1)//判断禁手
	{
		if (((score1 == 3000) && (score2 == 3000)) || ((score1 == 3000) && (score3 == 3000)) || ((score1 == 3000) && (score4 == 3000)) || ((score2 == 3000) && (score3 == 3000)) || ((score2 == 3000) && (score4 == 3000)) || ((score3 == 3000) && (score4 == 3000)))
			score = -100000;//双三判断
		else if ((score1 == -1000000) || (score2 == -1000000) || (score3 == -1000000) || (score4 == -1000000))//长连判断
			score = -100000;
		if ((score1 == 2800) || (score1 == 2600) || (score1 == 2500))//双四判断
			countD4++;
		else if ((score2 == 2800) || (score2 == 2600) || (score2 == 2500))
			countD4++;
		else if ((score3 == 2800) || (score3 == 2600) || (score3 == 2500))
			countD4++;
		else if ((score4 == 2800) || (score4 == 2600) || (score4 == 2500))
			countD4++;
		if (countD4 >= 2)
			score = -100000;
		
	}
	return score;
}
/******************************************************************************************************************/




/******************************************************************************************************************/
int scorewhite(int i, int j, int array[MAXLINE][MAXLINE], int first)
{
	int score1, score2, score3, score4;
	int score;
	int length;
	int iwhite;
	if (array[i][j] != 0)
		return -100000;

	if (i < 4)
	{
		score1 = 0;
		array[i][j] = 1;
		length = i + 4 + 1;
		char white[10];
		for (iwhite = 0; iwhite < length; iwhite++)
		{
			white[iwhite] = array[iwhite][j] + '0';
		}
		white[iwhite] = '\0';
		score1 = subscoreWhite(chessboard, i, white, i, j);
		array[i][j] = 0;

	}
	else if (i > 11)
	{
		score1 = 0;
		array[i][j] = 1;
		length = 14 - i + 4 + 1;
		char white[10];
		int m = i - 4;
		for (iwhite = 0; iwhite < length; iwhite++, m++)
		{
			white[iwhite] = array[m][j] + '0';
		}
		white[iwhite] = '\0';
		score1 = subscoreWhite(chessboard, 4, white, i, j);
		array[i][j] = 0;
	}
	else
	{
		score1 = 0;
		array[i][j] = 1;
		length = 9;
		char white[10];
		int m = i - 4;
		for (iwhite = 0; iwhite < length; iwhite++, m++)
		{
			white[iwhite] = array[m][j] + '0';
		}
		white[iwhite] = '\0';
		score1 = subscoreWhite(chessboard, 4, white, i, j);
		array[i][j] = 0;
	}

	if (j < 4)
	{
		score2 = 0;
		array[i][j] = 1;
		length = j + 4 + 1;
		char white[10];
		for (iwhite = 0; iwhite < length; iwhite++)
		{
			white[iwhite] = array[i][iwhite] + '0';
		}
		white[iwhite] = '\0';
		score2 = subscoreWhite(chessboard, j, white, i, j);
		array[i][j] = 0;
	}
	else if (j > 11)
	{
		score2 = 0;
		array[i][j] = 1;
		length = 14 - j + 4 + 1;
		char white[10];
		int m = j - 4;
		for (iwhite = 0; iwhite < length; iwhite++, m++)
		{
			white[iwhite] = array[i][m] + '0';
		}
		white[iwhite] = '\0';
		score2 = subscoreWhite(chessboard, 4, white, i, j);
		array[i][j] = 0;
	}
	else
	{
		score2 = 0;
		array[i][j] = 1;
		length = 9;
		char white[10];
		int m = j - 4;
		for (iwhite = 0; iwhite < length; iwhite++, m++)
		{
			white[iwhite] = array[i][m] + '0';
		}
		white[iwhite] = '\0';
		score2 = subscoreWhite(chessboard, 4, white, i, j);
		array[i][j] = 0;
	}

	if ((i < 4) && (j < 4))
	{
		score3 = 0;
		array[i][j] = 1;
		if (i < j)
		{
			length = i + 4 + 1;
			char white[10];
			int j_count = j - i;
			for (iwhite = 0; iwhite < length; iwhite++, j_count++)
			{
				white[iwhite] = array[iwhite][j_count] + '0';
			}
			white[iwhite] = '\0';
			score3 = subscoreWhite(chessboard, i, white, i, j);
			array[i][j] = 0;
		}
		else
		{
			score3 = 0;
			length = j + 4 + 1;
			char white[10];
			int i_count = i - j;
			for (iwhite = 0; iwhite < length; iwhite++, i_count++)
			{
				white[iwhite] = array[i_count][iwhite] + '0';
			}
			white[iwhite] = '\0';
			score3 = subscoreWhite(chessboard, j, white, i, j);
			array[i][j] = 0;
		}
	}
	else if ((i < 4) && (j>11))
	{
		score3 = 0;
		array[i][j] = 1;
		length = i + 1 + 14 - j;
		char white[10];
		int iv, ic;
		iv = j - i;
		for (ic = 0; ic < length; ic++, iv++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, length - 4, white, i, j);
		array[i][j] = 0;

	}
	else if ((j < 4) && (i>11))
	{
		array[i][j] = 1;
		score3 = 0;
		length = j + 1 + 14 - i;
		char white[10];
		int iv, ic;
		ic = i - j;
		for (iv = 0; iv < length; ic++, iv++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, length - 4, white, i, j);
		array[i][j] = 0;
	}
	else if ((j > 11) && (i > 11))
	{
		score3 = 0;
		array[i][j] = 1;
		if (i < j)

		{
			length = 19 - j;
			char white[10];
			int iv, ic;
			ic = i - 4;
			iv = j - 4;
			for (iwhite = 0; iwhite < length; ic++, iv++, iwhite++)
			{
				white[iwhite] = array[ic][iv] + '0';
			}
			white[iwhite] = '\0';
			score3 = subscoreWhite(chessboard, 14 - j + 1, white, i, j);
			array[i][j] = 0;
		}
		else
		{
			length = 19 - i;
			char white[10];
			int iv, ic;
			ic = i - 4;
			iv = j - 4;
			for (iwhite = 0; iwhite < length; ic++, iwhite++, iv++)
			{
				white[iwhite] = array[ic][iv] + '0';
			}
			white[iwhite] = '\0';
			score3 = subscoreWhite(chessboard, 14 - i + 1, white, i, j);
			array[i][j] = 0;
		}
	}
	else if ((i < 4) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 1;
		length = i + 4 + 1;
		char white[10];
		int j_count = j - i;
		for (iwhite = 0; iwhite < length; iwhite++, j_count++)
		{
			white[iwhite] = array[iwhite][j_count] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, i, white, i, j);
		array[i][j] = 0;
	}
	else if ((i > 11) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 1;
		length = 19 - i;
		char white[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iwhite = 0; iwhite < length; ic++, iwhite++, iv++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, 14 - i + 1, white, i, j);
		array[i][j] = 0;
	}
	else if ((j < 4) && (i >= 4) && (i <= 11))
	{
		array[i][j] = 1;
		score3 = 0;
		length = j + 4 + 1;
		char white[10];
		int i_count = i - j;
		for (iwhite = 0; iwhite < length; iwhite++, i_count++)
		{
			white[iwhite] = array[i_count][iwhite] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, j, white, i, j);
		array[i][j] = 0;
	}
	else if ((j > 11) && (i >= 4) && (i <= 11))
	{
		array[i][j] = 1;
		length = 19 - j;
		char white[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iwhite = 0; iwhite < length; ic++, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, 14 - j + 1, white, i, j);
		array[i][j] = 0;
	}
	else
	{
		array[i][j] = 1;
		score3 = 0;
		length = 9;
		char white[10];
		int iv, ic;
		ic = i - 4;
		iv = j - 4;
		for (iwhite = 0; iwhite < length; ic++, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score3 = subscoreWhite(chessboard, 4, white, i, j);
		array[i][j] = 0;
	}
	if ((i <= 4) && (j <= 4))
	{
		array[i][j] = 1;
		score4 = 0;
		length = i + j + 1;
		char white[10];
		int iv, ic;
		ic = i + j;
		iv = 0;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, length - 4, white, i, j);
		array[i][j] = 0;
	}
	else if ((i >= 11) && (j >= 11))
	{
		array[i][j] = 1;
		score4 = 0;
		length = 29 - i - j;
		char white[10];
		int iv, ic;
		ic = 14;
		iv = i + j - 14;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, length - 4, white, i, j);
		array[i][j] = 0;
	}
	else if ((i<4) && (j>11))
	{
		array[i][j] = 1;
		score4 = 0;
		if (i + j <= 14)
		{
			length = 5 + i;
			char white[10];
			int iv, ic;
			ic = i + 4;
			iv = j - 4;
			for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
			{
				white[iwhite] = array[ic][iv] + '0';
			}
			white[iwhite] = '\0';
			score4 = subscoreWhite(chessboard, i + 1, white, i, j);
			array[i][j] = 0;
		}
		else
		{
			length = 19 - j;
			char white[10];
			int iv, ic;
			ic = i + 4;
			iv = j - 4;
			for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
			{
				white[iwhite] = array[ic][iv] + '0';
			}
			white[iwhite] = '\0';
			score4 = subscoreWhite(chessboard, 15 - j, white, i, j);

			array[i][j] = 0;
		}
	}
	else if ((i > 11) && (j < 4))
	{
		array[i][j] = 1;
		score4 = 0;
		if (i + j <= 14)
		{
			length = 5 + j;
			char white[10];
			int iv, ic;
			ic = i + j;
			iv = 0;
			for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
			{
				white[iwhite] = array[ic][iv] + '0';
			}
			white[iwhite] = '\0';
			score4 = subscoreWhite(chessboard, j + 1, white, i, j);
			array[i][j] = 0;
		}

		else
		{
			length = 19 - i;
			char white[10];
			int iv, ic;
			ic = 14;
			iv = j + i - 14;
			for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
			{
				white[iwhite] = array[ic][iv] + '0';
			}
			white[iwhite] = '\0';
			score4 = subscoreWhite(chessboard, 15 - i, white, i, j);
			array[i][j] = 0;
		}
	}
	else if ((j < 4) && (i <= 11) && (i >= 4))
	{
		array[i][j] = 1;
		length = 5 + j;
		char white[10];
		int iv, ic;
		ic = i + j;
		iv = 0;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, j + 1, white, i, j);
		array[i][j] = 0;
	}
	else if ((j > 11) && (i <= 11) && (i >= 4))
	{
		array[i][j] = 1;
		length = 19 - j;
		char white[10];
		int iv, ic;
		ic = i + 4;
		iv = j - 4;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, 15 - j, white, i, j);

		array[i][j] = 0;
	}
	else if ((i < 4) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 1;
		length = 5 + i;
		char white[10];
		int iv, ic;
		ic = i + 4;
		iv = j - 4;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, i + 1, white, i, j);
		array[i][j] = 0;
	}
	else if ((i > 11) && (j >= 4) && (j <= 11))
	{
		array[i][j] = 1;
		length = 19 - i;
		char white[10];
		int iv, ic;
		ic = 14;
		iv = j + i - 14;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, 15 - i, white, i, j);
		array[i][j] = 0;

	}
	else
	{
		array[i][j] = 1;
		score4 = 0;
		length = 9;
		char white[10];
		int iv, ic;
		ic = i + 4;
		iv = j - 4;
		for (iwhite = 0; iwhite < length; ic--, iv++, iwhite++)
		{
			white[iwhite] = array[ic][iv] + '0';
		}
		white[iwhite] = '\0';
		score4 = subscoreWhite(chessboard, 4, white, i, j);
		array[i][j] = 0;
	}

	score = score1 + score2 + score3 + score4;
	return score;
}
/******************************************************************************************************************/




/******************************************************************************************************************/
int subscoreBlack(int array[MAXLINE][MAXLINE], int iCmp, char chess[10], int ic, int jc)//单点棋型估分

{
	int icmp;
	int score = 0;
	char pattern1[] = "22222";//30000000
	char pattern2[] = "022220";//5500
	char pattern3[] = "0022200";//3000
	char pattern4[] = "22202";//2800
	char pattern5[] = "22022";//2600
	char pattern6[] = "22220";//2500
	char pattern7[] = "020220";//3000
	char pattern8[] = "00022000";//650
	char pattern9[] = "20022";//600
	char pattern10[] = "20202";//550
	char pattern11[] = "22200";//500
	char pattern12[] = "0020200";//250
	char pattern13[] = "020020";//200
	char pattern14[] = "22000";//150
	char pattern15[] = "222222";
	char pattern16[] = "022020";//3000
	char pattern17[] = "20222";//2800
	char pattern18[] = "02222";//2500
	char pattern19[] = "22002";//600
	char pattern20[] = "00222";//500
	char pattern21[] = "00022";//150
	char pattern22[] = "0022201";//3000
	char pattern23[] = "1022200";//3000
	for (icmp = 0; icmp <= iCmp; icmp++)
	{
		if (strncmp((chess + icmp), pattern1, 5) == 0)
		{
			if (score<30000000)
				score = 30000000;
		}

		else if (strncmp((chess + icmp), pattern2, 6) == 0)
		{
			if (score<5500)
				score = 5500;
		}
		else if (strncmp((chess + icmp), pattern3, 7) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern16, 6) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern4, 5) == 0)
		{
			if (score<2800)
				score = 2800;
		}
		else if (strncmp((chess + icmp), pattern17, 5) == 0)
		{
			if (score<2800)
				score = 2800;
		}
		else if (strncmp((chess + icmp), pattern5, 5) == 0)
		{
			if (score<2600)
				score = 2600;
		}
		else if (strncmp((chess + icmp), pattern6, 5) == 0)
		{
			if (score<2500)
				score = 2500;
		}
		else if (strncmp((chess + icmp), pattern18, 5) == 0)
		{
			if (score<2500)
				score = 2500;
		}

		else if (strncmp((chess + icmp), pattern7, 6) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern8, 8) == 0)
		{
			if (score<650)
				score = 650;
		}
		else if (strncmp((chess + icmp), pattern9, 5) == 0)
		{
			if (score<600)
				score = 600;
		}
		else if (strncmp((chess + icmp), pattern19, 5) == 0)
		{
			if (score<600)
				score = 600;
		}
		else if (strncmp((chess + icmp), pattern10, 5) == 0)
		{
			if (score<550)
				score = 550;
		}
		else if (strncmp((chess + icmp), pattern11, 5) == 0)
		{
			if (score<500)
				score = 500;
		}
		else if (strncmp((chess + icmp), pattern20, 5) == 0)
		{
			array[ic][jc] = 0;
			if (score<500)
				score = 500;
		}
		else if (strncmp((chess + icmp), pattern12, 5) == 0)
		{
			if (score<250)
				score = 250;
		}
		else if (strncmp((chess + icmp), pattern13, 6) == 0)
		{
			if (score<200)
				score = 200;
		}
		else if (strncmp((chess + icmp), pattern14, 5) == 0)
		{
			if (score<150)
				score = 150;
		}
		else if (strncmp((chess + icmp), pattern21, 5) == 0)
		{
			if (score<150)
				score = 150;
		}
		else if (strncmp((chess + icmp), pattern22, 7) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern23, 7) == 0)
		{
			if (score<3000)
				score = 3000;
		}

		else if (strncmp((chess + icmp), pattern15, 6) == 0)
		{
			score = -100000;
			break;
		}


	}
	array[ic][jc] = 0;
	return score;
}
/******************************************************************************************************************/



/******************************************************************************************************************/
int subscoreWhite(int array[MAXLINE][MAXLINE], int iCmp, char chess[10], int ic, int jc)//单点棋型估分
{
	int icmp;
	int score = 0;
	char pattern1[] = "11111";//30000000
	char pattern2[] = "011110";//300000
	char pattern3[] = "0011100";//3000
	char pattern4[] = "11101";//2800
	char pattern5[] = "11011";//2600
	char pattern6[] = "11110";//2500
	char pattern7[] = "010110";//3000
	char pattern8[] = "00011000";//650
	char pattern9[] = "10011";//600
	char pattern10[] = "10101";//550
	char pattern11[] = "11100";//500
	char pattern12[] = "0010100";//250
	char pattern13[] = "010010";//200
	char pattern14[] = "11000";//150
	char pattern15[] = "111111";
	char pattern16[] = "011010";//3000
	char pattern17[] = "10111";//2800
	char pattern18[] = "01111";//2500
	char pattern19[] = "11001";//600
	char pattern20[] = "00111";//500
	char pattern21[] = "00011";//150
	char pattern22[] = "0011102";
	char pattern23[] = "2011100";
	for (icmp = 0; icmp <= iCmp; icmp++)
	{
		if (strncmp((chess + icmp), pattern1, 5) == 0)
		{
			if (score<30000000)
				score = 30000000;
		}

		else if (strncmp((chess + icmp), pattern2, 6) == 0)
		{
			if (score<5500)
				score = 5500;
		}
		else if (strncmp((chess + icmp), pattern3, 7) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern16, 6) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern4, 5) == 0)
		{
			if (score<2800)
				score = 2800;
		}
		else if (strncmp((chess + icmp), pattern17, 5) == 0)
		{
			if (score<2800)
				score = 2800;
		}
		else if (strncmp((chess + icmp), pattern5, 5) == 0)
		{
			if (score<2600)
				score = 2600;
		}
		else if (strncmp((chess + icmp), pattern6, 5) == 0)
		{
			if (score<2500)
				score = 2500;
		}
		else if (strncmp((chess + icmp), pattern18, 5) == 0)
		{
			if (score<2500)
				score = 2500;
		}

		else if (strncmp((chess + icmp), pattern7, 6) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern8, 8) == 0)
		{
			if (score<650)
				score = 650;
		}
		else if (strncmp((chess + icmp), pattern9, 5) == 0)
		{
			if (score<600)
				score = 600;
		}
		else if (strncmp((chess + icmp), pattern19, 5) == 0)
		{
			if (score<600)
				score = 600;
		}
		else if (strncmp((chess + icmp), pattern10, 5) == 0)
		{
			if (score<550)
				score = 550;
		}
		else if (strncmp((chess + icmp), pattern11, 5) == 0)
		{
			if (score<500)
				score = 500;
		}
		else if (strncmp((chess + icmp), pattern20, 5) == 0)
		{
			if (score<500)
				score = 500;
		}
		else if (strncmp((chess + icmp), pattern12, 5) == 0)
		{
			if (score<250)
				score = 250;
		}
		else if (strncmp((chess + icmp), pattern13, 6) == 0)
		{
			if (score<200)
				score = 200;
		}
		else if (strncmp((chess + icmp), pattern14, 5) == 0)
		{
			if (score<150)
				score = 150;
		}
		else if (strncmp((chess + icmp), pattern21, 5) == 0)
		{
			if (score<150)
				score = 150;
		}
		else if (strncmp((chess + icmp), pattern22, 7) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern23, 7) == 0)
		{
			if (score<3000)
				score = 3000;
		}
		else if (strncmp((chess + icmp), pattern15, 6) == 0)
		{
			score = -100000;
			break;
		}


	}
	array[ic][jc] = 0;
	return score;
}
/******************************************************************************************************************/



/******************************************************************************************************************/
/*int mycmp(const void *a, const void *b)//未完成部分
{
	MYPOINT* pa = (MYPOINT*)a;
	MYPOINT* pb = (MYPOINT*)b;
	return (pa->score > pb->score) ? -1 : 1;
}*/