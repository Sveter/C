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

// 入口点
Position gEntry = { 5, 2 };

// 判断是否走到出口，最后一列都是出口
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

// 判定是否可以走
// 没有越界 && 值是 1
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
				printf("█");
			}
			else if (gMaze[i][j] == 1) {
				printf("  ");
			}
			else if (gMaze[i][j] == 2) {
				printf("⊕");
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

	// 一进来标记这个我走过了
	gMaze[at.x][at.y] = 2;
	PrintMaze();

	// 为什么不需要在栈里记录，直接利用调用栈回溯

	if (IsExit(at)) {
		// 如果当前路径 （path）小于之前的最小路径 (min)，则当前路径是最短
		if (StackEmpty(&min) || StackSize(&path) < StackSize(&min)) {
			StackCopy(&min, &path);
		}

		PrintPath(&path);
		printf("============================\n");
		//printf("找到出口: x = %d, y = %d\n", at.x, at.y);

		// 重新置为 1
		gMaze[at.x][at.y] = 1;

		StackPop(&path);
		return;	// 会发生回溯
	}
	// 根据 左 -> 上 -> 右 -> 下 来尝试
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

	// 重新置为 1
	gMaze[at.x][at.y] = 1;

	StackPop(&path);
	return;	// 回溯

}

void TestRunMaze2()
{
	StackInit(&path);
	StackInit(&min);
	RunMazeRec(gEntry);

	printf("最短路径长度是 %d\n", StackSize(&min));
}