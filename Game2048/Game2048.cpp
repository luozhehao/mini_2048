// Game2048.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <time.h>
#include <easyx.h>
#include <math.h>


/***
2048游戏：
1.数据可以使用二维数组储存
2.随机数？ srand rand
3.把数据转成图形界面
***/


#define ROW 4
#define COL 4
#define GRID_SIZE 100
#define INTERVAL  15

int count = 0;
int bestCount = 0;

enum Color
{
	zero = RGB(205, 193, 180),  // 0 所在格子的颜色
	twoTo1 = RGB(238, 228, 218),
	twoTo2 = RGB(237, 224, 200),
	twoTo3 = RGB(242, 177, 180),
	twoTo4 = RGB(245, 149, 99),
	twoTo5 = RGB(246, 124, 95),
	twoTo6 = RGB(246, 94, 59),
	twoTo7 = RGB(242, 177, 121),
	twoTo8 = RGB(237, 204, 97),
	twoTo9 = RGB(255, 0, 128),
	twoTo10 = RGB(145, 0, 72),
	twoTo11 = RGB(242, 17, 158),
	back = RGB(187, 160, 160),

};

Color colors[13] = { zero , twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11, back };


int map[ROW][COL];

int map_moved[ROW][COL];



//随机产生 2 or 4
int createNumber()
{
	if (rand() % 10 != 0)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}

//给数组空白处填充一个数
void mapFillNumber()
{
	//随机产生一个数，放到数组里面
	while(true)
	{
		//多次产生下标，可能重复
		int r = rand() % ROW;  //0 1 2 3
		int c = rand() % COL;  //0 1 2 3
		if (map[r][c] == 0)
		{
			map[r][c] = createNumber();
			break;   //只有正确生成了数字
		}
	}
}


void init()
{
	srand(time(NULL));

	//随机产生一个数，放到数组里面
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}

	//map[1][0] = 2;
	//map[0][0] = 2;
	//map[0][2] = 512;

}

//绘制
int draw()
{
	// 187,173,160
	setbkcolor(RGB(187, 173, 160));
	cleardevice();

	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//把每行格子左上角的坐标求出来
			int x = k * GRID_SIZE + (k + 1)*INTERVAL;
			int y = i * GRID_SIZE + (i + 1)*INTERVAL;
			// RGB 205,193,180
			//map[][] 2048 2^11=2048

			int index = map[i][k]? log2(map[i][k]) : 0;
			setfillcolor(colors[index]);
			solidroundrect(x, y, x+GRID_SIZE, y+GRID_SIZE, 10, 10);

			if (map[i][k])
			{
				//先把数字转换为字符串
				char numberStr[5] = { 0 };
				sprintf(numberStr, "%d", map[i][k]);
				//绘制文字
				settextcolor(RGB(119, 110, 101));
				settextstyle(50, 0, "微软雅黑");
				setbkmode(TRANSPARENT);
				//文字居中显示
				int hspace = (GRID_SIZE - textwidth(numberStr)) / 2;
				int vspace = (GRID_SIZE - textheight(numberStr)) / 2;
				outtextxy(x + hspace, y + vspace, numberStr);
			}
			printf("%d ", map[i][k]);
		}
		printf("\n");
	}

	char scoreStr[6] = "Score";
	outtextxy(15, 460, scoreStr);

	char cntStr[5] = { 0 };
	sprintf(cntStr, "%d", count);
	outtextxy(130, 460, cntStr);

	char bestStr[5] = "Best";
	outtextxy(245, 460, bestStr);

	char bestcntStr[5] = { 0 };
	sprintf(bestcntStr, "%d", bestCount);
	outtextxy(360, 460, bestcntStr);


	return 0;
}

//向上移动
void moveUp()
{
	bool isMoved = false;
	for (int c = 0; c < COL; c++)   //遍历 列
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)  //遍历 行
		{
			//判断begin 处是不是 0
			if (map[begin][c] != 0)
			{
				if (map[temp][c] == 0)
				{
					map[temp][c] = map[begin][c];
					map[begin][c] = 0;
					isMoved = true;
				}
				else if (map[temp][c] == map[begin][c])
				{
					//map[temp][c] += map[begin][c];
					map[temp][c] *= 2;
					count += map[temp][c];
					map[begin][c] = 0;
					temp++;
					isMoved = true;
				}
				else //if (map[temp][c] != map[begin][c])
				{
					//map[temp + 1][c] == map[begin][c];
					map[temp + 1][c] = map[begin][c];
					if (temp + 1 != begin)
					{
						map[begin][c] = 0;
						isMoved = true;
					}
					temp++;
				}
			}

		}
	}

	if (isMoved)
	{
		mapFillNumber();
	}
}
//向下移动
void moveDown()
{
	bool isMoved = false;
	for (int c = 0; c < COL; c++)   //遍历 列
	{
		int temp = ROW  -1;
		for (int begin = ROW - 2; begin >= 0; begin--)  //遍历 行
		{
			//判断begin 处是不是 0
			if (map[begin][c] != 0)
			{
				if (map[temp][c] == 0)
				{
					map[temp][c] = map[begin][c];
					map[begin][c] = 0;
					isMoved = true;
				}
				else if (map[temp][c] == map[begin][c])
				{
					//map[temp][c] += map[begin][c];
					map[temp][c] *= 2;
					count += map[temp][c];
					map[begin][c] = 0;
					temp--;
					isMoved = true;
				}
				else //if (map[temp][c] == map[begin][c])
				{
					map[temp - 1][c] = map[begin][c];
					if (temp - 1 != begin)
					{
						map[begin][c] = 0;
						isMoved = true;
					}
					temp--;
				}
			}

		}
	}

	if (isMoved)
	{
		mapFillNumber();
	}

}

//向左移动
void moveLeft()
{
	bool isMoved = false;
	for (int r = 0; r < ROW; r++)   //遍历 行
	{
		int temp = 0;
		for (int begin = 1; begin < COL; begin++)  //遍历 行
		{
			//判断begin 处是不是 0
			if (map[r][begin] != 0)
			{
				if (map[r][temp] == 0)
				{
					map[r][temp] = map[r][begin];
					map[r][begin] = 0;
					isMoved = true;
				}
				else if (map[r][temp] == map[r][begin])
				{
					//map[temp][c] += map[begin][c];
					map[r][temp] *= 2;
					count += map[r][temp];
					map[r][begin] = 0;
					temp++;
					isMoved = true;
				}
				else //if (map[temp][c] == map[begin][c])
				{
					map[r][temp + 1] = map[r][begin];
					if (temp + 1 != begin)
					{
						map[r][begin] = 0;
						isMoved = true;
					}
					temp++;
				}
			}

		}
	}

	if (isMoved)
	{
		mapFillNumber();
	}
}

//向右移动
void moveRight()
{
	bool isMoved = false;
	for (int r = 0; r < ROW; r++)   //遍历 行
	{
		int temp = COL - 1;
		for (int begin = COL - 2; begin >= 0; begin--)  //遍历 行
		{
			//判断begin 处是不是 0
			if (map[r][begin] != 0)
			{
				if (map[r][temp] == 0)
				{
					map[r][temp] = map[r][begin];
					map[r][begin] = 0;
					isMoved = true;
				}
				else if (map[r][temp] == map[r][begin])
				{
					//map[temp][c] += map[begin][c];
					map[r][temp] *= 2;
					count += map[r][temp];
					map[r][begin] = 0;
					temp--;
					isMoved = true;
				}
				else //if (map[temp][c] == map[begin][c])
				{
					map[r][temp - 1] = map[r][begin];
					if (temp - 1 != begin)
					{
						map[r][begin] = 0;
						isMoved = true;
					}
					temp--;
				}
			}

		}
	}

	if (isMoved)
	{
		mapFillNumber();
	}
}


int checkMapFull()
{
	INT32 flag = 0;
	for (int i = 0; i< ROW; i++)
	{
		for (int j = 0; j<COL; j++)
		{
			if ( map[i][j] == 0)
			{
				return -1;
				
			}
		}
	}
	return 0;
}

int checkNearEqual()
{
	for (int i = 0; i< ROW; i++)
	{
		for (int j = 0; j<COL-1; j++)
		{
			if (map[i][j] == map[i][j+1])
			{
				return -1;
			}

		}
	}

	for (int i = 0; i< ROW - 1; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] == map[i + 1][j])
			{
				return -1;
			}
		}
	}

	return 0;
}


void resetMap()
{
	for (int i = 0; i< ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			map[i][j] = 0;
			
		}
	}

}

void checkGameOver()
{
	//判断map是否满了
	int isFull = checkMapFull();
	printf("isFull = %d\n", isFull);

	//判断map相邻元素是否相等
	int isInequal= checkNearEqual();
	printf("isInequal = %d\n", isInequal);


	if (isFull ==0 && isInequal == 0)
	{
		printf("isFull & 0xffff = %d\n", isFull & 0xffff);
		HWND hnd = GetHWnd();
		SetWindowText(hnd, "2048");
		int isOK = MessageBox(hnd, "游戏结束，重新开始", "提示", MB_OKCANCEL);
		if (isOK == IDOK)
		{
			printf("你点击了OK");
			count = 0;
			resetMap();
			init();
			draw();
			
		}
		else if (isOK == IDCANCEL)
		{
			printf("你点击了取消");
		}
	}
	else
	{


	}
}

//移动格子
//72 80 75 77  上下左右
void move()
{
	//获取键盘按键
	int key = _getch();
	printf("key = %d\n", key);
	switch (key)
	{
	case 'W':
	case 'w':
	case 72: // 'w'
		moveUp();
		break;
	case 80:
		moveDown();
		break;
	case 75:
		moveLeft();
		break;
	case 77:
		moveRight();
		break;
	}

	if (bestCount<count)
	{
		bestCount = count;
	}

}


int main()
{
	//窗口走一个
	initgraph(COL*GRID_SIZE + (COL+1) * INTERVAL, ROW*GRID_SIZE + (ROW + 1) * INTERVAL + 30, EX_SHOWCONSOLE);  //  EW_SHOWCONSOLE


	init();
	while (true)
	{
		draw();
		checkGameOver();
		move();

	}
	

	getchar();

/**
	while (1)
	{
		int key_val = _getch();
		printf("key_val=%d\n", key_val);
	}
**/



    return 0;
}

