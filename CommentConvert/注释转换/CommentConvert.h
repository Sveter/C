#ifndef __CommentConvert_H__
#define __CommentConvert_H__
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>

typedef enum State
{
	CODE,   //正常代码
	M_XIE_GANG,  //遇到/
	CCODE,  //C风格注释
	CPPCODE,  //C++风格注释
	CM_XING  //遇到*
} State;

void CommentConvertMachine(FILE* pfread, FILE* pfwrite);

#endif // !__CommentConvert_H__

