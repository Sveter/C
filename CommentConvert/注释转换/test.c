#include "CommentConvert.h"
//ÓÐÏÞ×´Ì¬»ú£¨Finite State Machine£©

void test()
{
	FILE* pfread = NULL;
	FILE* pfwrite = NULL;
	pfread = fopen("input.c","r");
	pfwrite = fopen("output.c", "w");
	if (pfread == NULL)
	{
		perror("fopen input");
	}
	if (pfwrite == NULL)
	{
		perror("fopen output");
		fclose(pfread);
	}
	CommentConvertMachine(pfread,pfwrite);
	fclose(pfread);
	fclose(pfwrite);
	pfread = NULL;
	pfwrite = NULL;
}


int main()
{
	test();
	return 0;
	system("pause");
}