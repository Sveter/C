#pragma once

#include "list.h"


//从尾到头打印链表
void PrintReverse(ListNode* first)
{
	ListNode* end = NULL;

	while (end != first)
	{
		ListNode* cur = first;
		while (cur->next != end)
		{
			cur = cur->next;
		}

		printf("%d ",cur->data);
		end = cur;
	}
}

void PrintReverseRecursion(ListNode* first)
{
	//方式一
	//if (first->next == NULL)
	//{
	//	printf("%d ",first->data);
	//}
	//else
	//{
	//	PrintReverseRecursion(first->next);
	//	printf("%d ",first->data);
	//}
	//方式二
	if (first == NULL)
	{
		return;
	}
	else
	{
		PrintReverseRecursion(first->next);
		printf("%d ",first->data);
	}
}

//逆置链表
ListNode* ReverseList1(ListNode* first)
{
	ListNode* node;
	ListNode* cur = first;
	ListNode* result = NULL;
	while (cur != NULL) {
		// 从 原来链表中头删（光摘下，没有真正删除）
		node = cur;
		cur = cur->next;

		// node 就是被头删下来的结点
		node->next = result;
		result = node;
	}

	return result;
}

ListNode* ReverseList2(ListNode* first)
{
	ListNode* p1 = NULL;
	ListNode* p2 = first;
	ListNode* p3 = first->next;

	while (p2 != NULL)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		if (p3 != NULL)
		{
			p3 = p3->next;
		}
	}
	return p1;
}

//删除无头链表
void RemoveNoFirst(ListNode* pos)
{
	pos->data = pos->next->data;
	ListNode* del = pos->next;
	pos->next = pos->next->next;

	free(del);
}
//插入节点到无头链表
void InsertNoFirst(ListNode *pos, DataType data)
{
	DataType tmp;
	ListNode* cur = CreateNode(data);
	tmp = pos->data;
	pos->data = cur->data;
	cur->data = tmp;

	cur->next = pos->next;
	pos->next = cur;
}

//求两个有序单链表的交集
void Intersection(ListNode* list1, ListNode* list2)
{
	ListNode* cur1 = list1;
	ListNode* cur2 = list2;
	DataType data;

	while (cur1!=NULL && cur2!=NULL)
	{
		if (cur1->data == cur2->data)
		{
			printf("%d ",cur1->data);
			data = cur1->data;
			while (cur1 != NULL && cur1->data == data)
			{
				cur1 = cur1->next;
			}
			while(cur2 != NULL && cur2->data == data)
			{
				cur2 = cur2->next;
			}
		}
		else if (cur1->data > cur2->data)
		{
			cur2 = cur2->next;
		}
		else
		{
			cur1 = cur1->next;
		}
	}
}
//约瑟夫环
ListNode* JosephCircle(ListNode* first, int k)
{
	ListNode* perv = NULL;
	ListNode* cur = first;
	//链表构成环
	ListNode* tail = first;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = first;
	//第二步
	
	while (cur->next != cur)
	{
		for(int i = 0;i < k-1;i++)
		{
			perv = cur;
			cur = cur->next;
		}
		perv->next = cur->next;
		free(cur);
		cur = perv->next;
	}
	printf("%d\n",perv->data);
	cur->next = NULL;
	return cur;
}

//合并两个有序链表
ListNode* MergeOrderedList(ListNode* list1, ListNode* list2)
{
	ListNode* cur1 = list1;
	ListNode* cur2 = list2;
	ListNode* result = NULL;
	ListNode* tail = NULL;
	ListNode* next;
	ListNode* node;
	
	while (cur1 != NULL && cur2 != NULL)
	{
		if (cur1->data <= cur2->data)
		{
			node = cur1;
		}
		else
		{
			node = cur2;
		}
		next = node->next;
		if (result != NULL)
		{
			tail->next = node;
		}
		else
		{
			result = node;
		}
		node->next = NULL;
		tail = node;
		if (node == cur1)
		{
			cur1 = next;
		}
		else
		{
			cur2 = next;
		}
	}
	//一个链表为空
	if (cur1 == NULL)
	{
		tail->next = cur2;
	}
	if (cur2 == NULL)
	{
		tail->next = cur1;
	}
	return result;
}

//查找中间节点
void FindMid(ListNode *first)
{
	ListNode* fast = first;
	ListNode* slow = first;

	while (1)
	{
		fast = fast->next;
		if (fast == NULL)
		{
			break;
		}
		fast = fast->next;
		if (fast == NULL)
		{
			break;
		}
		slow = slow->next;
	}
	printf("%d\n", slow->data);
}

//查找倒数第k个节点
void FindTailK(ListNode *first, int k)
{
	ListNode* cur1 = first;
	ListNode* cur2 = first;

	while (k--)
	{
		cur1 = cur1->next;
	}
	while (cur1 != NULL) 
	{
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	printf("%d ",cur2->data);
}

//删除第K个节点
void DelListK(ListNode **first, int k)
{
	ListNode* cur1 = *first;
	ListNode* cur2 = *first;
	ListNode* f1 = *first;

	ListNode* del;

	while (k--)
	{
		cur1 = cur1->next;
	}
	//只有K个节点时
	if (cur1 == NULL)
	{
		ListPopFront(first);
		return;
	}
	while (cur1->next != NULL)
	{
		cur1 = cur1->next;
		cur2 = cur2->next;
	}

	del = cur2->next;
	cur2->next = del->next;
	free(del);
}

