#include "list.h"
#include "question.h"

int main()
{
	//ListNode *first;
	//ListInit(&first);	// 传值 1. first	传地址 2. &first
	//					// 链表是一条空链表， first == NULL

	//					// first 会变化
	//ListPushBack(&first, 1);

	//// 以后 first 不变了
	//ListPushBack(&first, 2);
	//ListPushBack(&first, 3);

	//ListPopFront(&first);
	//ListPopBack(&first);
	//ListPopBack(&first);

	//ListNode *first = NULL;
	//ListPushBack(&first, 1);
	//ListPushBack(&first, 2);
	//ListPushBack(&first, 3);
	//ListPushBack(&first, 4);

	//PrintReverse(first);
	//printf("\n");
	////ReverseList(first);
	////ReverseList2(first);
	//ListNode *result = ListFind(first, 2);
	//InsertNoFirst(result, 5);
	//PrintReverse(first);

	ListNode* list1 = NULL;
	ListNode* list2 = NULL;

	ListPushBack(&list1, 1);
	ListPushBack(&list1, 2);
	ListPushBack(&list1, 3);
	ListPushBack(&list1, 4);
	ListPushBack(&list1, 5);
	ListPushBack(&list1, 6);
	ListPushBack(&list1, 7);

	FindMid(list1);
	//DelListK(list1, 6);
	DelListK(&list1, 7);

	ListPrint(list1);
	//JosephCircle(list1, 3);

	//ListPushBack(&list2, 1);
	//ListPushBack(&list2, 1);
	//ListPushBack(&list2, 4);
	//ListPushBack(&list2, 6);
	//ListPushBack(&list2, 9);

	//Intersection(list1, list2);
	system("pause");
	return 0;
}