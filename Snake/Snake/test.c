#include "Model.h"

void SnakeGame()
{
	Game game;
	GameInit(&game);

	DisplayWall(game.width, game.height);
	DisplaySnake(&game.snake);

	while (1)
	{
		if (GetAsyncKeyState(VK_UP) && game.snake.direction != DOWN) {
			game.snake.direction = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN) && game.snake.direction != UP) {
			game.snake.direction = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT) && game.snake.direction != RIGHT) {
			game.snake.direction = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && game.snake.direction != LEFT) {
			game.snake.direction = RIGHT;
		}

		Position nextPos = GetNextPosition(&game.snake);

		if (EatFood(game.food, nextPos))
		{
			AddHead(&game.snake, nextPos);
			//吃到食物后，更新下一个食物
			game.food = GenerateFood(game.width, game.height, &game.snake);
		}
		else
		{
			// 消掉尾巴
			RemoveTail(&game.snake);
			// 头增加
			AddHead(&game.snake, nextPos);
		}
		if (GameOver(&game.snake, game.width, game.height))
		{
			break;
		}
		Sleep(300);
	}
}

void FirstIn()
{

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;

	for (int i = 0; i < 7; i++) 
	{
		coord.X = 2 * i;
		coord.Y = i;
		SetConsoleCursorPosition(hOutput, coord);
	}
	printf("Welcome 贪吃蛇\n");
	system("pause");
	system("cls");
}

int main()
{
	FirstIn();
	srand((unsigned)time(NULL));
	SnakeGame();
	system("pause");
	return 0;
}