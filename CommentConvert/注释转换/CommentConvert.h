#ifndef __CommentConvert_H__
#define __CommentConvert_H__
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

typedef enum State
{
	CODE,   //��������
	M_XIE_GANG,  //����/
	CCODE,  //C���ע��
	CPPCODE,  //C++���ע��
	CM_XING  //����*
} State;

void CommentConvertMachine(FILE* pfread, FILE* pfwrite);

#endif // !__CommentConvert_H__

