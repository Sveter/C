#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define INIT 3  //初始化长度
#define POSX 7  //初始位置x
#define POSY 2  //初始位置y
#define WIDTH 28   //棋盘宽度
#define HEIGHT 27  //棋盘高度

typedef enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}Direction;

typedef struct Position
{
	int x;
	int y;
}Position;

typedef struct Node
{
	Position pos;
	struct Node* next;
}Node;

typedef struct Snake
{
	Node* head;
	Node* tail;
	Direction direction;
}Snake;

typedef struct Game
{
	Snake snake;
	Position food;
	int width;
	int height;
}Game;



void SnakeInit(Snake* pSnake);  //初始化蛇
bool IsOverlap(Position pos, const Snake *pSnake); //位置被占用
void GameInit(Game *pGame);//初始化游戏
Position GenerateFood(int width, int height, const Snake* pSnake);//初始化食物
Position GetNextPosition(const Snake* pSnake); //下一位置
bool EatFood(Position food, Position next); //吃到食物
void AddHead(Snake* pSnake, Position next);//增加长度到头部
void RemoveTail(Snake* pSnake);//删除尾部
bool GameOver(const Snake *pSnake, int width, int height);//判断是否死亡

//界面
void DisplayWall(int width, int height);//打印墙
void DisplaySnake(const Snake *pSnake);//打印蛇
void DisplayFood(const Position *pFood);//打印食物
void CleanSnakeNode(const Position *pPos);//走后清除位置
void DisplaySnakeNode(const Position *pPos);//打印走过之后的节点

#endif // !__MODEL_H__

