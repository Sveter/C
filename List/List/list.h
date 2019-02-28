#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef int DataType;
typedef struct ListNode
{
	DataType data;
	struct ListNode* next;
} ListNode;

//��ʼ��
void ListInit(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	*ppFirst = NULL;
}

//����
void ListDestroy(ListNode** ppFirst)
{
	ListNode* next;
	for (ListNode* cur = *ppFirst; cur != NULL; cur = next)
	{
		next = cur->next;
		free(cur);
	}

	*ppFirst = NULL;
}

static ListNode * CreateNode(DataType data)
{
	ListNode* newNode = (ListNode *)malloc(sizeof(ListNode));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}
//��
//ͷ��
void ListPushFront(ListNode** ppFirst, DataType data)
{
	assert(ppFirst);
	//������� *ppFirst == NULL
	//�������
	ListNode* newNode = CreateNode(data);
	newNode->next = *ppFirst;

	*ppFirst = newNode;
}
//β��
void ListPushBack(ListNode** ppFirst, DataType data)
{
	ListNode* newNode = CreateNode(data);
	assert(ppFirst);
	//����Ϊ��
	if (*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	//�������
	ListNode* cur = *ppFirst;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = newNode;
}
//ɾ
//ͷɾ
void ListPopFront(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	//�������
	ListNode* del = *ppFirst;
	*ppFirst = del->next;
	free(del);
}

//βɾ
void ListPopBack(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	//�������:ֻ��һ���ڵ�
	if ((*ppFirst)->next == NULL) {
		free(*ppFirst);
		*ppFirst = NULL;
		return;
	}
	//�������
	ListNode* del;
	ListNode* cur = *ppFirst;
	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	del = cur->next;
	cur->next = NULL;
	free(del);

}
//����
ListNode* ListFind(ListNode* first, DataType data)
{
	assert(first);

	for (ListNode* cur = first; cur != NULL; cur = cur->next)
	{
		if (data == cur->data)
		{
			return cur;
		}
	}
	return NULL;
}

//����
void ListInsert(ListNode** ppfirst, ListNode* pos, DataType data)
{
	//ͷ��
	if (*ppfirst == pos)
	{
		ListPushFront(ppfirst, data);
		return;
	}
	//�ҵ�posǰһ���ڵ�
	ListNode* cur = *ppfirst;
	while (cur->next != pos)
	{
		cur = cur->next;
	}
	//�����½ڵ�
	ListNode* newnode = CreateNode(data);
	newnode->next = cur->next;
	cur->next = newnode;
}

//ɾ��
void ListErase(ListNode** ppFirst, ListNode* pos)
{
	// ͷɾ
	if (*ppFirst == pos) {
		ListPopFront(ppFirst);
		return;	// �ǵ� return������������� else
	}

	ListNode *cur = *ppFirst;
	// �� pos ��ǰһ�����
	while (cur->next != pos) {
		cur = cur->next;
	}

	cur->next = pos->next;
	free(pos);
}
void ListPrint(ListNode *first)
{
	for (ListNode *cur = first; cur != NULL; cur = cur->next) {
		printf("%d -> ", cur->data);
	}
	printf("NULL\n");
}
