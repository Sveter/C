#pragma once
#include "stack.h"


int gMaze[ROWS][COLS] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 1, 1, 1 },
	{ 0, 0, 1, 0, 0, 0 }
};

// ��ڵ�
Position gEntry = { 5, 2 };

// �ж��Ƿ��ߵ����ڣ����һ�ж��ǳ���
int IsExit(Position pos)
{
	if (pos.y == COLS - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// �ж��Ƿ������
// û��Խ�� && ֵ�� 1
int CanPass(Position pos)
{
	if (pos.x >= ROWS)
	{
		return 0;
	}
	if (pos.y >= COLS)
	{
		return 0;
	}
	return gMaze[pos.x][pos.y] == 1;
}

Stack path;
Stack min;


void PrintMaze()
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (gMaze[i][j] == 0) {
				printf("��");
			}
			else if (gMaze[i][j] == 1) {
				printf("  ");
			}
			else if (gMaze[i][j] == 2) {
				printf("��");
			}
		}
		printf("\n");
	}

	printf("\n\n");
}

void RunMazeRec(Position at)
{
	Position next;
	StackPush(&path, at);

	// һ�������������߹���
	gMaze[at.x][at.y] = 2;
	PrintMaze();

	// Ϊʲô����Ҫ��ջ���¼��ֱ�����õ���ջ����

	if (IsExit(at)) {
		// �����ǰ·�� ��path��С��֮ǰ����С·�� (min)����ǰ·�������
		if (StackEmpty(&min) || StackSize(&path) < StackSize(&min)) {
			StackCopy(&min, &path);
		}

		PrintPath(&path);
		printf("============================\n");
		//printf("�ҵ�����: x = %d, y = %d\n", at.x, at.y);

		// ������Ϊ 1
		gMaze[at.x][at.y] = 1;

		StackPop(&path);
		return;	// �ᷢ������
	}
	// ���� �� -> �� -> �� -> �� ������
	next.x = at.x;
	next.y = at.y - 1;
	if (CanPass(next)) {
		RunMazeRec(next);
		PrintMaze();
	}

	next.x = at.x - 1;
	next.y = at.y;
	if (CanPass(next)) {
		RunMazeRec(next);
		PrintMaze();
	}

	next.x = at.x;
	next.y = at.y + 1;
	if (CanPass(next)) {
		RunMazeRec(next);
		PrintMaze();
	}

	next.x = at.x + 1;
	next.y = at.y;
	if (CanPass(next)) {
		RunMazeRec(next);
		PrintMaze();
	}

	// ������Ϊ 1
	gMaze[at.x][at.y] = 1;

	StackPop(&path);
	return;	// ����

}

void TestRunMaze2()
{
	StackInit(&path);
	StackInit(&min);
	RunMazeRec(gEntry);

	printf("���·�������� %d\n", StackSize(&min));
}