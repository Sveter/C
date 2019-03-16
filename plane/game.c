#include <stdio.h>
#include <windows.h>
#include <conio.h>
#pragma warning(disable:4996)
int main()
{
	//int x = 1;
	//int y = 5;

	//for(x = 1; x < 10 ; x++)
	//{
	//	system("cls");
	//	int i = 0;
		//for (i = 0; i < x; i++)
		//{
		//	printf("\n");
		//}
		//for (i = 0; i < y; i++)
		//{
		//	printf(" ");
		//}
	//	printf("0\n");
	//	Sleep(100);
	//}

	////边界
	//int left = 0;
	//int right = 20;
	//int top = 0;
	//int bottom = 10;
	////方向
	//int dir_x = 1;
	//int dir_y = 1;

	////当前位置
	//int x = bottom / 2;
	//int y = right / 2;

	//while (1)
	//{
	//	system("cls");

	//	x = x + dir_x;
	//	y = y + dir_y;
	//	int i = 0;
	//
	//	for (i = 0; i < x; i++)
	//	{
	//		printf("\n");
	//	}
	//	for (i = 0; i < y; i++)
	//	{
	//		printf(" ");
	//	}
	//	printf("0\n");
	//	
	//	if (x == bottom || x == top)
	//	{
	//		dir_x = -dir_x;
	//	}
	//	if (y == left || y == right)
	//	{
	//		dir_y = -dir_y;
	//	}
	//}

	int x = 10;
	int y = 5;
	char input;
	int isFire = 0;
	int ny = y;
	int isKilled = 0;

	while (1)
	{
		system("cls");

		if (isKilled == 0)
		{
			for (int i = 0; i < ny;i++)
			{
				printf(" ");
			}
			printf("  @\n");
		}

		if (isFire == 0) 
		{
			for (int i = 0; i < x; i++)
				printf("\n");
		}
		else
		{
			for (int i = 0; i < x; i++) 
			{
				for (int j = 0; j < y; j++)
				{
					printf(" ");
				}
				printf("  |\n");
			}
			if (ny == y)
			{
				isKilled = 1;
			}
			isFire = 0;

		}

		for (int i = 0; i < y; i++)
			printf(" ");
		printf("  *\n");
		for (int i = 0; i < y; i++)
			printf(" ");
		printf("*****\n");
		for (int i = 0; i < y; i++)
			printf(" ");
		printf(" * * \n");

		//scanf("%c", &input);
		if (kbhit())
		{
			input = getch();
			if (input == 's') x++;
			if (input == 'a') y--;
			if (input == 'd') y++;
			if (input == 'w') x--;
			if (input == ' ') isFire = 1;
		}
		Sleep(50);
	}



	system("pause");
	return 0;
}