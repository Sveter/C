#include "Model.h"


//初始化
void SnakeInit(Snake* pSnake)
{
	pSnake->tail = NULL;
	for (int i = 0; i < INIT; i++)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->pos.x = POSX + i;
		node->pos.y = POSY;
		if (i == 0)
		{
			pSnake->head = node;
		}
		node->next = pSnake->tail;
		pSnake->tail = node;
	}
	pSnake->direction = LEFT;
}

bool IsOverlap(Position pos, const Snake *pSnake)
{
	Node* node;
	for (node = pSnake->tail; node != NULL; node = node->next)
	{
		if (node->pos.x == pos.x &&node->pos.y == pos.y)
		{
			return true;
		}
	}
	return false;
}

Position GenerateFood(int width, int height, const Snake* pSnake)
{
	Position pos;

	do
	{
		pos.x = rand() % width;
		pos.y = rand() % height;
	} while (IsOverlap(pos, pSnake));

	DisplayFood(&pos);
	return pos;
}

void GameInit(Game *pGame)
{
	pGame->width = WIDTH;
	pGame->height = HEIGHT;

	SnakeInit(&pGame->snake);
	//初始化食物
	pGame->food = GenerateFood(pGame->width, pGame->height, &pGame->snake);
}

Position GetNextPosition(const Snake* pSnake)
{
	Position next = pSnake->head->pos;

	switch (pSnake->direction)
	{
	case UP:
		next.y -= 1;
		break;
	case DOWN:
		next.y += 1;
		break;
	case LEFT:
		next.x -= 1;
		break;
	case RIGHT:
		next.x += 1;
		break;
	}
	return next;
}

bool EatFood(Position food, Position next)
{
	return ((food.x == next.x) && (food.y == next.y));
}

void AddHead(Snake* pSnake, Position next)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->pos = next;
	node->next = NULL;

	pSnake->head->next = node;
	pSnake->head = node;

	DisplaySnakeNode(&next);
}

void RemoveTail(Snake* pSnake)
{
	Node* tail = pSnake->tail;
	pSnake->tail = pSnake->tail->next;

	CleanSnakeNode(&tail->pos);
	free(tail);
}

bool KillByWar(const Snake *pSnake, int width, int height)
{
	int x = pSnake->head->pos.x;
	int y = pSnake->head->pos.y;

	if (x >= 0 && x < width &&y >= 0 && y < height)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool KillBySelf(const Snake* pSnake)
{
	Node* node;
	for (node = pSnake->tail; node != pSnake->head; node = node->next)
	{
		if (node->pos.x == pSnake->head->pos.x && node->pos.y == pSnake->head->pos.y)
		{
			return true;
		}
	}

	return false;
}

bool GameOver(const Snake *pSnake, int width, int height)
{
	//撞墙
	if (KillByWar(pSnake, width, height))
	{
		printf("撞到南墙不回头\n");
		return true;
	}
	//自杀
	if (KillBySelf(pSnake))
	{
		printf("我命由我\n");
		return true;
	}
	return false;
}

/*界面*/
//初始化
void ViewInit()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
}

void SetPos(int X, int Y)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hOutput, coord);
}

static void ChineseSetPos(int x, int y)
{
	int X = 2 * (x + 1);
	int Y = y + 1;

	SetPos(X, Y);
}

void DisplayWall(int width, int height)
{
	ViewInit();
	SetPos(0, 0);
	for (int i = 0; i < width + 2; i++)
	{
		printf("□");
	}

	SetPos(0, height + 1);
	for (int i = 0; i < width + 2; i++)
	{
		printf("□");
	}

	for (int i = 0; i < height + 2; i++)
	{
		SetPos(0, i);
		printf("□");
	}

	for (int i = 0; i < height + 2; i++)
	{
		SetPos(2 * (width + 1), i);
		printf("□");
	}
}

void DisplaySnake(const Snake *pSnake)
{
	for (Node *node = pSnake->tail; node != NULL; node = node->next) {
		ChineseSetPos(node->pos.x, node->pos.y);
		printf("○");
	}
}

void DisplayFood(const Position *pFood)
{
	ChineseSetPos(pFood->x, pFood->y);
	printf("☆");
}

void CleanSnakeNode(const Position *pPos)
{
	ChineseSetPos(pPos->x, pPos->y);
	printf(" ");
}

void DisplaySnakeNode(const Position *pPos)
{
	ChineseSetPos(pPos->x, pPos->y);
	printf("○");
}