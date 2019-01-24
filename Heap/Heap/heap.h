#pragma once
#include <stdio.h>
#include <assert.h>

typedef struct Heap
{
	int array[100];
	int size;
} Heap;

// 初始化堆
void HeapInit(Heap* pH, int source[], int size)
{
	for (int i = 0; i < size; i++)
	{
		pH->array[i] = source[i];
	}
	pH->size = size;
}

// 向下调整
void HeapAdjustDown(Heap* pH, int root)
{
	int parent = root;
	while (1)
	{
		int left = 2 * parent + 1;
		if (left >= pH->size)
		{
			return;
		}
		int maxChild = left;
		if (2 * parent + 2 < pH->size && pH->array[2 * parent + 2] > pH->array[left])
		{
			maxChild = 2 * parent + 2;
		}
		if (pH->array[parent] > pH->array[maxChild])
		{
			return;
		}

		// 交换 root 和 maxChild 下标所在的值
		int t = pH->array[parent];
		pH->array[parent] = pH->array[maxChild];
		pH->array[maxChild] = t;

		parent = maxChild;
	}
}
// 建大堆
void MakeHeap(Heap* pH)
{
	for (int i = (pH->size - 2) / 2; i >= 0; i--)
	{
		HeapAdjustDown(pH, i);
	}
}
// 堆删除
void HeapPop(Heap *pH)
{
	pH->array[0] = pH->array[pH->size - 1];
	pH->size--;

	HeapAdjustDown(pH, 0);
}
// 堆顶元素
int HeapTop(const Heap *pH)
{
	return pH->array[0];
}

static void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
// 向上调整
void HeapAdjustUp(Heap *pH, int child)
{
	int parent;
	while (child > 0) {
		parent = (child - 1) / 2;
		if (pH->array[parent] >= pH->array[child]) {
			return;
		}

		Swap(pH->array + parent, pH->array + child);

		child = parent;
	}
}
// 插入元素
void HeapPush(Heap *pH, int data)
{
	assert(pH->size < 100);
	pH->array[pH->size++] = data;
	HeapAdjustUp(pH, pH->size - 1);
}

void Test()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 23, 31 };
	int size = sizeof(array) / sizeof(int);

	Heap	heap;
	HeapInit(&heap, array, size);
	MakeHeap(&heap);
	HeapPush(&heap, 100);
	printf("%d\n", HeapTop(&heap));
	HeapPop(&heap);

	printf("建堆完成\n");
}

// 面试题
void ArrayAdjustDown(int array[], int size, int root)
{
	int parent = root;

	while (1) {
		// 先判断有没有孩子（叶子结点）
		// 数组角度去想	-> 孩子的下标是否越界
		// 只要判断左孩子的下标（因为是完全二叉树)
		int left = parent * 2 + 1;
		if (left >= size) {
			// 越界，没有左孩子，也肯定没有右孩子
			return;
		}

		// 一定有左孩子
		int maxChild = left;
		if (2 * parent + 2 < size && array[2 * parent + 2] > array[left]) {
			// 前一个条件是判断右孩子有没有
			// 后一个条件判读是右孩子是否比左孩子大
			maxChild = 2 * parent + 2;
		}

		if (array[parent] > array[maxChild]) {
			return;
		}

		// 交换 root 和 maxChild 下标所在的值
		int t = array[parent];
		array[parent] = array[maxChild];
		array[maxChild] = t;

		parent = maxChild;
	}
}

// 堆排序（升序）
// 时间复杂度 O(n * Logn)
// 空间复杂度 O(1)
void HeapSort(int array[], int size)
{
	// 建大堆
	for (int i = (size - 2) / 2; i >= 0; i--) {
		ArrayAdjustDown(array, size, i);
	}

	// 开始排序
	for (int j = 0; j < size; j++) {
		// 位置
		int s = size - 1 - j;
		Swap(array, array + s);
		ArrayAdjustDown(array, size - 1 - j, 0);
	}
}

void TestSort()
{
	int array[] = { 1, 4, 9, 4, 2, 7, 8, 5, 3, 6, 2, 2, 3 };
	int size = sizeof(array) / sizeof(int);

	HeapSort(array, size);

	printf("成功\n");
}

#include <stdlib.h>

// TopK	找最小的 k 个数据，需要建大堆
// 和排序不太一样：排序是在原数组调整。TopK 最好不要在原数组上调整
int * TopK(int array[], int size, int k)
{
	int *heapArray = (int *)malloc(k * sizeof(int));
	assert(heapArray);

	// 搬 前 k 个数过去
	for (int i = 0; i < k; i++) {
		heapArray[i] = array[i];
	}

	// 建堆，建大堆
	// 这里的 size 其实是 k
	for (int j = (k - 2) / 2; j >= 0; j--) {
		ArrayAdjustDown(heapArray, k, j);
	}

	for (int m = k; m < size; m++) {
		if (array[m] >= heapArray[0]) {
			continue;
		}

		heapArray[0] = array[m];
		ArrayAdjustDown(heapArray, k, 0);
		// 不要用  Swap(heapArray, array + m);
	}

	return heapArray;
}

void TestTopK()
{
	int array[] = { 1, 4, 9, 4, 2, 7, 8, 5, 3, 6, 2, 2, 3 };
	int size = sizeof(array) / sizeof(int);

	int *r = TopK(array, size, 3);

	printf("成功\n");
}