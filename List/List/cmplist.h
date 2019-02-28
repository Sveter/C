#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct CLNode
{
	int data;
	struct CLNode* random;
	struct CLNode* next;
}   CLNode;

static CLNode * ComplexCreateNode(int data)
{
	CLNode *node = (CLNode *)malloc(sizeof(CLNode));
	node->data = data;
	node->random = NULL;
	node->next = NULL;

	return node;
}

CLNode* CopyCmpList(CLNode* list)
{
	CLNode* cur = list;
	//1.¸´ÖÆ
	while (cur != NULL)
	{
		CLNode* newnode = ComplexCreateNode(cur->data);
		newnode->next = cur->next;
		cur->next = newnode;

		cur = cur->next->next;
	}
	//2.¸´ÖÆrandom
	cur = list;
	while (cur != NULL)
	{
		if (cur->random != NULL)
		{
			cur->next->random = cur->random->next;
		}

		cur = cur->next->next;
	}
	//3.²ð·Ö
	cur = list;
	CLNode* newlist = cur->next;
	while (cur != NULL)
	{
		CLNode* node = cur->next;
		cur->next = node->next;
		if (cur->next != NULL)
		{
			node->next = cur->next->next;
		}
		else
		{
			node->next = NULL;
		}

		cur = cur->next;
	}
	return newlist;
}

void PrintComplexList(CLNode *list)
{
	for (CLNode *cur = list; cur != NULL; cur = cur->next) {
		printf("[%d, random(%p)->%d] ", cur->data,
			cur->random,
			cur->random ? cur->random->data : 0);
	}
	printf("\n");
}
