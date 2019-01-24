#pragma once
#include <stdio.h>
#include <assert.h>

typedef struct Heap
{
	int array[100];
	int size;
} Heap;

// ��ʼ����
void HeapInit(Heap* pH, int source[], int size)
{
	for (int i = 0; i < size; i++)
	{
		pH->array[i] = source[i];
	}
	pH->size = size;
}

// ���µ���
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

		// ���� root �� maxChild �±����ڵ�ֵ
		int t = pH->array[parent];
		pH->array[parent] = pH->array[maxChild];
		pH->array[maxChild] = t;

		parent = maxChild;
	}
}
// �����
void MakeHeap(Heap* pH)
{
	for (int i = (pH->size - 2) / 2; i >= 0; i--)
	{
		HeapAdjustDown(pH, i);
	}
}
// ��ɾ��
void HeapPop(Heap *pH)
{
	pH->array[0] = pH->array[pH->size - 1];
	pH->size--;

	HeapAdjustDown(pH, 0);
}
// �Ѷ�Ԫ��
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
// ���ϵ���
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
// ����Ԫ��
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

	printf("�������\n");
}

// ������
void ArrayAdjustDown(int array[], int size, int root)
{
	int parent = root;

	while (1) {
		// ���ж���û�к��ӣ�Ҷ�ӽ�㣩
		// ����Ƕ�ȥ��	-> ���ӵ��±��Ƿ�Խ��
		// ֻҪ�ж����ӵ��±꣨��Ϊ����ȫ������)
		int left = parent * 2 + 1;
		if (left >= size) {
			// Խ�磬û�����ӣ�Ҳ�϶�û���Һ���
			return;
		}

		// һ��������
		int maxChild = left;
		if (2 * parent + 2 < size && array[2 * parent + 2] > array[left]) {
			// ǰһ���������ж��Һ�����û��
			// ��һ�������ж����Һ����Ƿ�����Ӵ�
			maxChild = 2 * parent + 2;
		}

		if (array[parent] > array[maxChild]) {
			return;
		}

		// ���� root �� maxChild �±����ڵ�ֵ
		int t = array[parent];
		array[parent] = array[maxChild];
		array[maxChild] = t;

		parent = maxChild;
	}
}

// ����������
// ʱ�临�Ӷ� O(n * Logn)
// �ռ临�Ӷ� O(1)
void HeapSort(int array[], int size)
{
	// �����
	for (int i = (size - 2) / 2; i >= 0; i--) {
		ArrayAdjustDown(array, size, i);
	}

	// ��ʼ����
	for (int j = 0; j < size; j++) {
		// λ��
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

	printf("�ɹ�\n");
}

#include <stdlib.h>

// TopK	����С�� k �����ݣ���Ҫ�����
// ������̫һ������������ԭ���������TopK ��ò�Ҫ��ԭ�����ϵ���
int * TopK(int array[], int size, int k)
{
	int *heapArray = (int *)malloc(k * sizeof(int));
	assert(heapArray);

	// �� ǰ k ������ȥ
	for (int i = 0; i < k; i++) {
		heapArray[i] = array[i];
	}

	// ���ѣ������
	// ����� size ��ʵ�� k
	for (int j = (k - 2) / 2; j >= 0; j--) {
		ArrayAdjustDown(heapArray, k, j);
	}

	for (int m = k; m < size; m++) {
		if (array[m] >= heapArray[0]) {
			continue;
		}

		heapArray[0] = array[m];
		ArrayAdjustDown(heapArray, k, 0);
		// ��Ҫ��  Swap(heapArray, array + m);
	}

	return heapArray;
}

void TestTopK()
{
	int array[] = { 1, 4, 9, 4, 2, 7, 8, 5, 3, 6, 2, 2, 3 };
	int size = sizeof(array) / sizeof(int);

	int *r = TopK(array, size, 3);

	printf("�ɹ�\n");
}