#pragma once

#include <stdlib.h>
#include <assert.h>


//带头节点，循环，双向
typedef struct DListNode
{
	int data;
	struct DListNode *prev;
	struct DListNode *next;
} DListNode;

//初始化/销毁
void DListInit(DListNode **ppHead)
{
	assert(ppHead != NULL);
	DListNode* pHead = (DListNode*)malloc(sizeof(DListNode));
	pHead->next = pHead;
	pHead->prev = pHead;

	*ppHead = pHead;
}
// 销毁头结点
void DListDestroy(DListNode **ppHead)
{
	assert(ppHead != NULL);
	DListClear(*ppHead);
	free(*ppHead);
	*ppHead = NULL;
}


// 清空链表
// 保留头结点
void DListClear(DListNode *pHead)
{
	DListNode* cur = pHead->next;
	DListNode* next;
	while (cur != pHead)
	{
		next = cur->next;
		free(cur);
	}

	pHead->next = pHead;
	pHead->prev = pHead;
}

void DListInsert(DListNode *pHead, DListNode *pos, int data)
{
	(void)pHead;	// 没有用，强制转换的目的是防止编译器警告
	DListNode *node = (DListNode *)malloc(sizeof(DListNode));
	node->data = data;

	node->prev = pos->prev;
	node->next = pos;
	pos->prev->next = node;
	pos->prev = node;
}

//头插
void DListPushFront(DListNode *pHead, int data)
{
	DListInsert(pHead,pHead->next,data);
}
//尾插
void DListPushBack(DListNode *pHead, int data)
{
	DListInsert(pHead,pHead,data);
}

// pos 肯定不是头结点
void DListErase(DListNode *pHead, DListNode *pos)
{
	(void)pHead;
	assert(pos != pHead);

	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}

//头删
void DListPopFront(DListNode *pHead)
{
	DListErase(pHead,pHead->next);
}
//尾删
void DListPopBack(DListNode *pHead)
{
	DListErase(pHead, pHead->prev);
}