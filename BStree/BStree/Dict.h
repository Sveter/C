#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Dict
{
	char	en[20];		// key
	char	cn[20];		// value
	struct Dict *left;
	struct Dict *right;
}	Dict;


const char * DictFind(const Dict *root, char en[])
{
	const Dict *cur = root;
	int r;

	while (cur != NULL) {
		r = strncmp(en, cur->en, 20);
		if (r == 0) {
			return cur->cn;
		}
		else if (r > 0) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
	}

	return NULL;
}

int DictInsert(Dict **root, char en[], char cn[])
{
	int r;
	if (*root == NULL) {
		Dict *node = (Dict *)malloc(sizeof(Dict));
		strncpy(node->en, en, 20);
		strncpy(node->cn, cn, 20);
		node->left = node->right = NULL;
		*root = node;
		return 1;
	}

	r = strncmp(en, (*root)->en, 20);
	if (r == 0) {
		return 0;
	}

	if (r < 0) {
		return DictInsert(&(*root)->left, en, cn);
	}
	else {
		return DictInsert(&(*root)->right, en, cn);
	}
}


void TestDict2()
{
	Dict *dict = NULL;
	DictInsert(&dict, "apple", "苹果");
	DictInsert(&dict, "pear", "梨");
	DictInsert(&dict, "orange", "橘子");


	char en[20];
	const char *cn;

	while (1) {
		scanf("%s", en);
		if ((cn = DictFind(dict, en)) != NULL) {
			printf("%s\n", cn);
		}
		else {
			printf("拼写错误\n");
		}
	}
}

/*
/A apple
/B pear
...

全班最受欢迎的 5 种水果
*/