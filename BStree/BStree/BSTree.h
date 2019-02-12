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



// 递归形式
// 0 表示查找失败， 1 表示成功
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


// 非递归
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


//  插入
int BSTreeInsert(BSTreeNode **root, DataType key)
{
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;
	while (cur != NULL) {
		if (key == cur->key) {
			// 重复了，插入失败
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
		// 空树中插入
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

// 插入递归
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
		// 这个是不对的，更改的只是栈上临时变量的值
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

// 删除左为空的情况
static void RemoveLeftNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if (parent == NULL) {
		// 要删除的就是根结点
		*root = cur->right;
	}
	else {
		if (key < parent->key) {
			// cur 是 parent 的 left
			parent->left = cur->right;
		}
		else {
			// cur 是 parent 的 right
			parent->right = cur->right;
		}
	}

	free(cur);
}

// 删除右为空的情况
static void RemoveRightNULL(DataType key, BSTreeNode *parent, BSTreeNode **root, BSTreeNode *cur)
{
	if (parent == NULL) {
		// 要删除的就是根结点
		*root = cur->left;
	}
	else {
		if (key < parent->key) {
			// cur 是 parent 的 left
			parent->left = cur->left;
		}
		else {
			// cur 是 parent 的 right
			parent->right = cur->left;
		}
	}

	free(cur);
}

static void RemoveHasLeftAndRight(BSTreeNode *cur)
{
	// 找左子树中最大的
	BSTreeNode *del = cur->left;
	BSTreeNode *delParent = NULL;
	while (del->right != NULL) {
		delParent = del;
		del = del->right;
	}
	// del 就是左子树中最大的

	cur->key = del->key;
	// 删除 del 结点
	if (delParent == NULL) {
		// 左孩子中最大的就是 cur 的左孩子
		cur->left = del->left;
	}
	else {
		delParent->right = del->left;
	}

	free(del);
}

// 找到就删除，返回成功 1
// 没找到删除失败，返回 0
int BSTreeNodeRemove(BSTreeNode **root, DataType key)
{
	// 先查找，后删除
	BSTreeNode *cur = *root;
	BSTreeNode *parent = NULL;

	while (cur != NULL) {
		if (key == cur->key) {
			// 这里找到了，这里是删除的地方
			if (cur->left == NULL) {
				// cur 没有左孩子
				RemoveLeftNULL(key, parent, root, cur);
			}
			else if (cur->right == NULL) {
				// cur 没有右孩子
				RemoveRightNULL(key, parent, root, cur);
			}
			else {
				// 左右孩子都不为空
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

// 递归的删除
int ReBSTreeNodeRemove(BSTreeNode **root, DataType key)
{
	if (*root == NULL) {
		return 0;
	}

	if (key == (*root)->key) {
		BSTreeNode *del = *root;
		if ((*root)->left == NULL) {
			// 1. 要删除的是不是根
			// 2. 判断要删除的结点是根的左还是右
			*root = (*root)->right;
			free(del);
		}
		else if ((*root)->right == NULL) {
			*root = (*root)->left;
			free(del);
		}
		else {
			// 左右都不为空
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
	//要改变参数，所以传地址
	r = BSTreeInsert(&root, 5); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 3); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 7); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 1); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 4); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 6); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 8); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 0); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 2); printf("插入%s\n", r ? "成功" : "失败");
	r = BSTreeInsert(&root, 9); printf("插入%s\n", r ? "成功" : "失败");
	r = ReBSTreeInsert(&root, 10); printf("插入%s\n", r ? "成功" : "失败");

	InOrder(root); printf("\n");

	r = BSTreeFind(root, 9); printf("查找 9 %s\n", r ? "成功" : "失败");
	r = ReBSTreeFind(root, 10); printf("查找 10 %s\n", r ? "成功" : "失败");

	BSTreeNodeRemove(&root, 8);
	BSTreeNodeRemove(&root, 2);
	BSTreeNodeRemove(&root, 5);
}