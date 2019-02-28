#pragma once

#include <stdlib.h>
#include <assert.h>


//��ͷ�ڵ㣬ѭ����˫��
typedef struct DListNode
{
	int data;
	struct DListNode *prev;
	struct DListNode *next;
} DListNode;

//��ʼ��/����
void DListInit(DListNode **ppHead)
{
	assert(ppHead != NULL);
	DListNode* pHead = (DListNode*)malloc(sizeof(DListNode));
	pHead->next = pHead;
	pHead->prev = pHead;

	*ppHead = pHead;
}
// ����ͷ���
void DListDestroy(DListNode **ppHead)
{
	assert(ppHead != NULL);
	DListClear(*ppHead);
	free(*ppHead);
	*ppHead = NULL;
}


// �������
// ����ͷ���
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
	(void)pHead;	// û���ã�ǿ��ת����Ŀ���Ƿ�ֹ����������
	DListNode *node = (DListNode *)malloc(sizeof(DListNode));
	node->data = data;

	node->prev = pos->prev;
	node->next = pos;
	pos->prev->next = node;
	pos->prev = node;
}

//ͷ��
void DListPushFront(DListNode *pHead, int data)
{
	DListInsert(pHead,pHead->next,data);
}
//β��
void DListPushBack(DListNode *pHead, int data)
{
	DListInsert(pHead,pHead,data);
}

// pos �϶�����ͷ���
void DListErase(DListNode *pHead, DListNode *pos)
{
	(void)pHead;
	assert(pos != pHead);

	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}

//ͷɾ
void DListPopFront(DListNode *pHead)
{
	DListErase(pHead,pHead->next);
}
//βɾ
void DListPopBack(DListNode *pHead)
{
	DListErase(pHead, pHead->prev);
}