#pragma once
#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef int	DataType;

typedef struct BSTreeNode {
	DataType	key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
}	BSTreeNode;



// �ݹ���ʽ
// 0 ��ʾ����ʧ�ܣ� 1 ��ʾ�ɹ�
int BSTreeFind(const BSTreeNode *root, DataType key)
{
	if (root == NULL) {
		return 0;
	}

	if (key == root->key) {
		return 1;
	}
	else if (key > root->key) {
		return BSTreeFind(root->right, key);
	}
	else {
		return BSTreeFind(root->left, key);
	}
}


// �ǵݹ�
int ReBSTreeFind(const BSTreeNode *root, DataType key)
{
	BSTreeNode *cur = (BSTreeNode *)root;
	while (cur != NULL) {
		if (key == cur->key) {
			return 1;
		}
		else if (key > cur->key) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
	}

	return 0;
}


//  ����
int BSTreeInsert(BSTreeNode **root, DataType key)
{
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;
	while (cur != NULL) {
		if (key == cur->key) {
			// �ظ��ˣ�����ʧ��
			return 0;
		}

		parent = cur;
		if (key > cur->key) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
	}

	BSTreeNode *node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
	node->key = key;
	node->left = node->right = NULL;

	if (parent == NULL) {
		// �����в���
		*root = node;
		return 1;
	}

	if (key < parent->key) {
		parent->left = node;
	}
	else {
		parent->right = node;
	}

	return 1;
}

// ����ݹ�
int ReBSTreeInsert(BSTreeNode **root, DataType key)
{
	if (*root == NULL) {
		BSTreeNode *node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
		node->key = key;
		node->left = node->right = NULL;
		*root = node;
		return 1;
	}

	if (key == (*root)->key) {
		return 0;
	}

	if (key < (*root)->key) {
		// ����ǲ��Եģ����ĵ�ֻ��ջ����ʱ������ֵ
		// BSTreeNode *child = (*root)->left;
		// return BSTreeInsert2(&child, key);	
		return ReBSTreeInsert(&(*root)->left, key);
	}
	else {
		return ReBSTreeInsert(&(*root)->right, key);
	}
}

void InOrder(BSTreeNode *root)
{
	if (root == NULL) { return; }
	InOrder(root->left);
	printf("%d ", root->key);
	InOrder(root->right);
}

// ɾ����Ϊ�յ����
static void RemoveLeftNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if (parent == NULL) {
		// Ҫɾ���ľ��Ǹ����
		*root = cur->right;
	}
	else {
		if (key < parent->key) {
			// cur �� parent �� left
			parent->left = cur->right;
		}
		else {
			// cur �� parent �� right
			parent->right = cur->right;
		}
	}

	free(cur);
}

// ɾ����Ϊ�յ����
static void RemoveRightNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if (parent == NULL) {
		// Ҫɾ���ľ��Ǹ����
		*root = cur->left;
	}
	else {
		if (key < parent->key) {
			// cur �� parent �� left
			parent->left = cur->left;
		}
		else {
			// cur �� parent �� right
			parent->right = cur->left;
		}
	}

	free(cur);
}

static void RemoveHasLeftAndRight(BSTreeNode *cur)
{
	// ��������������
	BSTreeNode *del = cur->left;
	BSTreeNode *delParent = NULL;
	while (del->right != NULL) {
		delParent = del;
		del = del->right;
	}
	// del ����������������

	cur->key = del->key;
	// ɾ�� del ���
	if (delParent == NULL) {
		// ���������ľ��� cur ������
		cur->left = del->left;
	}
	else {
		delParent->right = del->left;
	}

	free(del);
}

// �ҵ���ɾ�������سɹ� 1
// û�ҵ�ɾ��ʧ�ܣ����� 0
int BSTreeNodeRemove(BSTreeNode **root, DataType key)
{
	// �Ȳ��ң���ɾ��
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;

	while (cur != NULL) {
		if (key == cur->key) {
			// �����ҵ��ˣ�������ɾ���ĵط�
			if (cur->left == NULL) {
				// cur û������
				RemoveLeftNULL(key, parent, root, cur);
			}
			else if (cur->right == NULL) {
				// cur û���Һ���
				RemoveRightNULL(key, parent, root, cur);
			}
			else {
				// ���Һ��Ӷ���Ϊ��
				RemoveHasLeftAndRight(cur);
			}

			return 1;
		}

		parent = cur;
		if (key < cur->key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	return 0;
}

// �ݹ��ɾ��
int ReBSTreeNodeRemove(BSTreeNode **root, DataType key)
{
	if (*root == NULL) {
		return 0;
	}

	if (key == (*root)->key) {
		BSTreeNode *del = *root;
		if ((*root)->left == NULL) {
			// 1. Ҫɾ�����ǲ��Ǹ�
			// 2. �ж�Ҫɾ���Ľ���Ǹ���������
			*root = (*root)->right;
			free(del);
		}
		else if ((*root)->right == NULL) {
			*root = (*root)->left;
			free(del);
		}
		else {
			// ���Ҷ���Ϊ��
			RemoveHasLeftAndRight(*root);
		}

		return 1;
	}

	if (key < (*root)->key) {
		return ReBSTreeNodeRemove(&(*root)->left, key);
	}
	else {
		return ReBSTreeNodeRemove(&(*root)->right, key);
	}
}

void Test()
{
	int r;
	BSTreeNode *root = NULL;
	//Ҫ�ı���������Դ���ַ
	r = BSTreeInsert(&root, 5); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 3); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 7); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 1); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 4); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 6); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 8); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 0); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 2); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = BSTreeInsert(&root, 9); printf("����%s\n", r ? "�ɹ�" : "ʧ��");
	r = ReBSTreeInsert(&root, 10); printf("����%s\n", r ? "�ɹ�" : "ʧ��");

	InOrder(root); printf("\n");

	r = BSTreeFind(root, 9); printf("���� 9 %s\n", r ? "�ɹ�" : "ʧ��");
	r = ReBSTreeFind(root, 10); printf("���� 10 %s\n", r ? "�ɹ�" : "ʧ��");

	BSTreeNodeRemove(&root, 8);
	BSTreeNodeRemove(&root, 2);
	BSTreeNodeRemove(&root, 5);
}