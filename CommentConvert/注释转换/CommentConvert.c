#include "CommentConvert.h"

void CommentConvertMachine(FILE* pfread, FILE* pfwrite)
{
	State state = CODE;
	int ch;
	int nextch;
	while (1)
	{
		ch = fgetc(pfread);
		if (ch == EOF)
		{
			break;
		}

		switch (state)
		{
		case CODE:
			if (ch == '/')
			{
				state = M_XIE_GANG;
			}
			fputc(ch, pfwrite);
			break;
		case M_XIE_GANG:
			if (ch == '*')
			{
				state = CCODE;
				fputc('/',pfwrite);
			}
			else if (ch == '/')
			{
				state = CPPCODE;
				fputc(ch, pfwrite);
			}
			else
			{
				state = CODE;
				fputc(ch, pfwrite);
			}
			break;
		case CCODE:
			if (ch == '*')
			{
				state = CM_XING;
			}
			else
			{
				fputc(ch, pfwrite);
				if (ch == '\n')
				{
					fprintf(pfwrite, "//");
				}
			}
			break;
		case CPPCODE:
			if (ch == '\n')
			{
				state = CODE;
			}
			fputc(ch, pfwrite);
			break;
		case CM_XING:
			if (ch == '/')
			{
				state = CODE;
				nextch = fgetc(pfread);
				if (nextch != '\n')
				{
					fputc('\n', pfwrite);
				}
				ungetc(nextch, pfread);
			}
			else if (ch != '*')
			{
				state = CCODE;
				fputc('*', pfwrite);
				fputc(ch, pfwrite);
			}
			else
			{
				fputc('*', pfwrite);
			}
			break;
		}
	}
}