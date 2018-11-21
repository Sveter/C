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

void RunMaze()
{
	// ��Ҫһ��ջ��ʵ�ֻ���
	Stack stack;
	StackInit(&stack);
	Position at;
	Position next;
	at.x = gEntry.x;
	at.y = gEntry.y;

	while (1)
	{
		// ��ǵ�ǰλ�����Ѿ��߹���
		gMaze[at.x][at.y] = 2;

		// ��ջ���¼��ǰλ�ã�Ϊ���Ժ������׼��
		StackPush(&stack, at);
		
		if (IsExit(at))
		{
			//printf("x = %d, y = %d\n", at.x, at.y);
			PrintPath(&stack);
			return;
		}
		// ���� �� -> �� -> �� -> �� ������
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
		// ������裬����
		StackPop(&stack);

		if (StackEmpty(&stack)) {
			printf("û�г���\n");
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