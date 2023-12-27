// Game2048.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <time.h>
#include <easyx.h>
#include <math.h>


/***
2048��Ϸ��
1.���ݿ���ʹ�ö�ά���鴢��
2.������� srand rand
3.������ת��ͼ�ν���
***/


#define ROW 4
#define COL 4
#define GRID_SIZE 100
#define INTERVAL  15

int count = 0;
int bestCount = 0;

enum Color
{
	zero = RGB(205, 193, 180),  // 0 ���ڸ��ӵ���ɫ
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



//������� 2 or 4
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

//������հ״����һ����
void mapFillNumber()
{
	//�������һ�������ŵ���������
	while(true)
	{
		//��β����±꣬�����ظ�
		int r = rand() % ROW;  //0 1 2 3
		int c = rand() % COL;  //0 1 2 3
		if (map[r][c] == 0)
		{
			map[r][c] = createNumber();
			break;   //ֻ����ȷ����������
		}
	}
}


void init()
{
	srand(time(NULL));

	//�������һ�������ŵ���������
	for (int i = 0; i < 2; i++)
	{
		mapFillNumber();
	}

	//map[1][0] = 2;
	//map[0][0] = 2;
	//map[0][2] = 512;

}

//����
int draw()
{
	// 187,173,160
	setbkcolor(RGB(187, 173, 160));
	cleardevice();

	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			//��ÿ�и������Ͻǵ����������
			int x = k * GRID_SIZE + (k + 1)*INTERVAL;
			int y = i * GRID_SIZE + (i + 1)*INTERVAL;
			// RGB 205,193,180
			//map[][] 2048 2^11=2048

			int index = map[i][k]? log2(map[i][k]) : 0;
			setfillcolor(colors[index]);
			solidroundrect(x, y, x+GRID_SIZE, y+GRID_SIZE, 10, 10);

			if (map[i][k])
			{
				//�Ȱ�����ת��Ϊ�ַ���
				char numberStr[5] = { 0 };
				sprintf(numberStr, "%d", map[i][k]);
				//��������
				settextcolor(RGB(119, 110, 101));
				settextstyle(50, 0, "΢���ź�");
				setbkmode(TRANSPARENT);
				//���־�����ʾ
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

//�����ƶ�
void moveUp()
{
	bool isMoved = false;
	for (int c = 0; c < COL; c++)   //���� ��
	{
		int temp = 0;
		for (int begin = 1; begin < ROW; begin++)  //���� ��
		{
			//�ж�begin ���ǲ��� 0
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
//�����ƶ�
void moveDown()
{
	bool isMoved = false;
	for (int c = 0; c < COL; c++)   //���� ��
	{
		int temp = ROW  -1;
		for (int begin = ROW - 2; begin >= 0; begin--)  //���� ��
		{
			//�ж�begin ���ǲ��� 0
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

//�����ƶ�
void moveLeft()
{
	bool isMoved = false;
	for (int r = 0; r < ROW; r++)   //���� ��
	{
		int temp = 0;
		for (int begin = 1; begin < COL; begin++)  //���� ��
		{
			//�ж�begin ���ǲ��� 0
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

//�����ƶ�
void moveRight()
{
	bool isMoved = false;
	for (int r = 0; r < ROW; r++)   //���� ��
	{
		int temp = COL - 1;
		for (int begin = COL - 2; begin >= 0; begin--)  //���� ��
		{
			//�ж�begin ���ǲ��� 0
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
	//�ж�map�Ƿ�����
	int isFull = checkMapFull();
	printf("isFull = %d\n", isFull);

	//�ж�map����Ԫ���Ƿ����
	int isInequal= checkNearEqual();
	printf("isInequal = %d\n", isInequal);


	if (isFull ==0 && isInequal == 0)
	{
		printf("isFull & 0xffff = %d\n", isFull & 0xffff);
		HWND hnd = GetHWnd();
		SetWindowText(hnd, "2048");
		int isOK = MessageBox(hnd, "��Ϸ���������¿�ʼ", "��ʾ", MB_OKCANCEL);
		if (isOK == IDOK)
		{
			printf("������OK");
			count = 0;
			resetMap();
			init();
			draw();
			
		}
		else if (isOK == IDCANCEL)
		{
			printf("������ȡ��");
		}
	}
	else
	{


	}
}

//�ƶ�����
//72 80 75 77  ��������
void move()
{
	//��ȡ���̰���
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
	//������һ��
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

