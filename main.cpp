#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

int panel[4][4];

enum Direction {
	LEFT = 1,
	UP,
	RIGHT,
	DOWN
}direction;

void init()
{
	srand(time(NULL));
	memset(panel, 0, sizeof(panel));
}

int checkBlock()
{
	int haveBlank = 0;//有空位标志
	int i = 0, j = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (panel[i][j] == 0)
			{
				haveBlank = 1;
				break;
			}
		}
	}
	return haveBlank;
}

void printNum(int number)
{
	int color;
	switch (number)
	{
	case 2:color = 32; break;
	case 4:color = 33; break;
	case 8:color = 31; break;
	case 16:color = 34; break;
	case 32:color = 35; break;
	case 64:color = 36; break;
	case 128:color = 31; break;
	case 256:color = 32; break;
	case 512:color = 33; break;
	case 1024:color = 34; break;
	case 2048:color = 35; break;
	case 0:
	default:
		color = 37;
		break;
	}
	printf("\033[%d;1m %5d\033[0m", color, number);
}

void printPanel()
{
	system("cls");
	printf("输入WASD四向移动\n\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printNum(panel[i][j]);
		}
		printf("\n\n");
	}
}

void Move(Direction& direction)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			switch (direction)
			{
			case LEFT:
			{
				if (j == 0 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i][j - 1] == 0)
				{
					panel[i][j - 1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j - 1] == panel[i][j])
				{
					panel[i][j - 1] *= 2;
					panel[i][j] = 0;
					continue;
				}
				else continue;
			}break;
			case UP:
			{
				if (i == 0 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i - 1][j] == 0)
				{
					panel[i - 1][j] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i - 1][j] == panel[i][j])
				{
					panel[i - 1][j] *= 2;
					panel[i][j] = 0;
					continue;
				}
				else continue;
			}break;
			case RIGHT:
			{
				if (j == 3 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i][j + 1] == 0)
				{
					panel[i][j + 1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j + 1] == panel[i][j])
				{
					panel[i][j + 1] *= 2;
					panel[i][j] = 0;
					continue;
				}
				else continue;
			}break;
			case DOWN:
			{
				if (i == 3 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i + 1][j] == 0)
				{
					panel[i + 1][j] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i + 1][j] == panel[i][j])
				{
					panel[i + 1][j] *= 2;
					panel[i][j] = 0;
					continue;
				}
				else continue;
			}break;
			default:
				break;
			}
		}
	}
}

void play()
{
	char action;
	int re = scanf("%c", &action);
	if (re == 0)
	{
		printf("输入错误重新输入！\n");
		play();
		return;
	}
	switch (action)
	{
	case'a':direction = LEFT; break;
	case'w':direction = UP; break;
	case'd':direction = RIGHT; break;
	case's':direction = DOWN; break;
	default:
		play();
		break;
	}
	Move(direction);
}

void newBlock()
{
	int i, j, count = 0;
	do
	{
		i = rand() % 4;
		j = rand() % 4;
		count++;
	} while (panel[i][j] != 0);//随机找到一个空位
	if (i % 2 == 0)
		panel[i][j] = 4;
	else
		panel[i][j] = 2;
}

int main()
{
	init();//初始化
	do
	{
		newBlock();//随机找一个位置生成2
		printPanel();//展示界面
		play();
	} while (checkBlock());
	printf("GameOver!\n");
	system("pause");
	return 0;
}
