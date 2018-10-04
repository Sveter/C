#pragma once

#include "Stack.h"

void MatchBrackt(char* sequence, int size)
{
	Stack stack;
	StackInit(&stack);
	char ch;
	char leftBracket;
	for (int i = 0; i < size; i++)
	{
		ch = sequence[i];
		switch (ch)
		{
		case '(':
		case '[':
		case '{':
			StackPush(&stack, (StackDataType)ch);
			break;
		case ')':
		case ']':
		case '}':
			if (StackEmpty(&stack))
			{
				printf("右括号多\n");
				StackDestroy(&stack);
				return;
			}
			leftBracket = (char)StackTop(&stack);
			StackPop(&stack);

			if (leftBracket == '('&&ch != ')')
			{
				printf("不匹配\n");
				return;
			}
			if (leftBracket == '[' && ch != ']') {
				printf("不匹配\n");
				return;
			}

			if (leftBracket == '{' && ch != '}') {
				printf("不匹配\n");
				return;
			}
		default:
			break;
		}
	}
	if (!StackEmpty(&stack))
	{
		printf("左括号多\n");
		return;
	}
	printf("正常匹配\n");
}
void test()
{
	const char * seqs[] = {
		"(())abc{[(])}",
		"(()))abc{[]}",
		"(()()abc{[]}",
		"(())abc{[]()}"
	};

	int sz = sizeof(seqs) / sizeof(seqs[0]);

	for (int i = 0; i < sz; i++)
	{
		MatchBrackt(seqs[i], strlen(seqs[i]));
	}
}

// 逆波兰表达式
typedef enum {
	OPERAND,	// 操作数类型
	OPERATOR	// 操作符类型
}	Type;

typedef enum {
	ADD, SUB, MUL, DIV
}	Operator;

typedef struct  Element{
	Type type;
	int	operand;		// 操作数
	Operator opera;	// 操作符
}	Element;

int Run(Operator opera, int a, int b)
{
	int c = 0;
	switch (opera) {
	case ADD:
		c = a + b;
		break;
	case SUB:
		c = a - b;
		break;
	case MUL:
		c = a * b;
		break;
	case DIV:
		c = a / b;
		break;
	default:
		// 不应该出现
		assert(0);
	}
	return c;
}

int ReversePolishNotation(Element expression[], int size)
{
	Stack stack;
	StackInit(&stack);
	int op1, op2;
	int result;

	for (int i = 0; i < size; i++)
	{
		Element e = expression[i];
		switch (e.type)
		{
		case OPERAND:
			StackPush(&stack, e.operand);
				break;
		case OPERATOR:
			op1 = StackTop(&stack); StackPop(&stack);
			op2 = StackTop(&stack); StackPop(&stack);

			result = Run(e.opera, op1, op2);

			StackPush(&stack, result);
			break;
		default:
			assert(0);
		}
	}

	// 栈里面只剩一个结果数
	assert(StackSize(&stack) == 1);
	result = StackTop(&stack);

	return result;
}