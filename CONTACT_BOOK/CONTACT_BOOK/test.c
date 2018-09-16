#include "contact.h"

void menu()
{
	printf("********************************\n");
	printf("**** 1. add       2. del    ****\n");
	printf("**** 3. search    4. modify ****\n");
	printf("**** 5. show      6. clear  ****\n");
	printf("**** 7. sort      8. save   ****\n");
	printf("**** 0. exit                ****\n");
	printf("********************************\n");
}

void test()
{
	struct Contact con;
	InitContact(&con);
	int input = 0;
	do
	{
		menu();
		printf("ÇëÑ¡Ôñ:>");
		scanf("%d",&input);
		
		switch (input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case CLEAR:
			ClearContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case SAVE:
			break;
		case EXIT:
			SaveContact(&con);
			DestoryContact(&con);
			break;
		}

		
	} while(input);
}

int main()
{
	test();
	return 0;
	//system("pause");
}