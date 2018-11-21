#pragma once

// 用全局变量，但不是最好的方式
#define ROWS (6)
#define COLS (6)

// 用来保存迷宫中的坐标
// 坐标方向和平时不太一样，x 朝下，y 朝右
typedef struct {
	int	x;
	int y;
}	Position;
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef Position StackDataType;

#define	MAX_SIZE	(100)

typedef struct Stack {
	StackDataType	array[MAX_SIZE];
	int				top;	// 表示当前个数
}	Stack;

// 初始化/销毁
// 增（只能从栈顶）/删（只能删除栈顶）/查（只能查看栈顶元素）
// 个数 / 是否空 / 是否满
// 增 -> 顺序表的尾插
// 删 -> 顺序表的尾删

void StackInit(Stack *pStack)
{
	pStack->top = 0;
}

void StackDestroy(Stack *pStack)
{
	pStack->top = 0;
}

void StackPush(Stack *pStack, StackDataType data)
{
	assert(pStack->top < MAX_SIZE);

	pStack->array[pStack->top++] = data;
}

void StackPop(Stack *pStack)
{
	assert(pStack->top > 0);

	pStack->top--;
}

StackDataType StackTop(const Stack *pStack)
{
	assert(pStack->top > 0);

	return pStack->array[pStack->top - 1];
}

int StackSize(const Stack *pStack)
{
	return pStack->top;
}

int StackFull(const Stack *pStack)
{
	return pStack->top >= MAX_SIZE;
}

int StackEmpty(const Stack *pStack)
{
	return pStack->top <= 0;
}

void StackCopy(Stack *pDest, Stack *pSrc)
{
	memcpy(pDest->array, pSrc->array, sizeof(StackDataType)* pSrc->top);
	pDest->top = pSrc->top;
}

void PrintPath(Stack *pStack)
{
	Position at;
	for (int i = 0; i < pStack->top; i++) {
		at = pStack->array[i];
		printf("x = %d, y = %d\n", at.x, at.y);
	}
}

