#pragma once
#include "stack.h"


int gMaze[ROWS][COLS] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0 },
	{ 0, 0, 1, 0, 1, 1 },
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

void RunMaze()
{
	// 需要一个栈，实现回溯
	Stack stack;
	StackInit(&stack);
	Position at;
	Position next;
	at.x = gEntry.x;
	at.y = gEntry.y;

	while (1)
	{
		// 标记当前位置我已经走过了
		gMaze[at.x][at.y] = 2;

		// 在栈里记录当前位置，为了以后回溯做准备
		StackPush(&stack, at);
		
		if (IsExit(at))
		{
			//printf("x = %d, y = %d\n", at.x, at.y);
			PrintPath(&stack);
			return;
		}
		// 根据 左 -> 上 -> 右 -> 下 来尝试
		next.x = at.x;
		next.y = at.y - 1;
		if (CanPass(next))
		{
			at.x = next.x;
			at.y = next.y;
			continue;
		}

		next.x = at.x - 1;
		next.y = at.y;
		if (CanPass(next)) {
			at.x = next.x;
			at.y = next.y;
			continue;
		}

		next.x = at.x;
		next.y = at.y + 1;
		if (CanPass(next)) {
			at.x = next.x;
			at.y = next.y;
			continue;
		}

		next.x = at.x + 1;
		next.y = at.y;
		if (CanPass(next)) {
			at.x = next.x;
			at.y = next.y;
			continue;
		}
		// 四面楚歌，回溯
		StackPop(&stack);

		if (StackEmpty(&stack)) {
			printf("没有出口\n");
			return;
		}

		at = StackTop(&stack);
		StackPop(&stack);
	}
}

void TestRunMaze1()
{
	RunMaze();
}