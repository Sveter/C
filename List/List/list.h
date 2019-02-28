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

//初始化
void ListInit(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	*ppFirst = NULL;
}

//销毁
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
//增
//头增
void ListPushFront(ListNode** ppFirst, DataType data)
{
	assert(ppFirst);
	//特殊情况 *ppFirst == NULL
	//正常情况
	ListNode* newNode = CreateNode(data);
	newNode->next = *ppFirst;

	*ppFirst = newNode;
}
//尾增
void ListPushBack(ListNode** ppFirst, DataType data)
{
	ListNode* newNode = CreateNode(data);
	assert(ppFirst);
	//链表为空
	if (*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	//正常情况
	ListNode* cur = *ppFirst;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = newNode;
}
//删
//头删
void ListPopFront(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	//正常情况
	ListNode* del = *ppFirst;
	*ppFirst = del->next;
	free(del);
}

//尾删
void ListPopBack(ListNode** ppFirst)
{
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	//特殊情况:只有一个节点
	if ((*ppFirst)->next == NULL) {
		free(*ppFirst);
		*ppFirst = NULL;
		return;
	}
	//正常情况
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
//查找
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

//插入
void ListInsert(ListNode** ppfirst, ListNode* pos, DataType data)
{
	//头插
	if (*ppfirst == pos)
	{
		ListPushFront(ppfirst, data);
		return;
	}
	//找到pos前一个节点
	ListNode* cur = *ppfirst;
	while (cur->next != pos)
	{
		cur = cur->next;
	}
	//插入新节点
	ListNode* newnode = CreateNode(data);
	newnode->next = cur->next;
	cur->next = newnode;
}

//删除
void ListErase(ListNode** ppFirst, ListNode* pos)
{
	// 头删
	if (*ppFirst == pos) {
		ListPopFront(ppFirst);
		return;	// 记得 return，否则下面加上 else
	}

	ListNode *cur = *ppFirst;
	// 找 pos 的前一个结点
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
