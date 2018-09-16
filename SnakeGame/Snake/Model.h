#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

#define INIT 3  //��ʼ������
#define POSX 7  //��ʼλ��x
#define POSY 2  //��ʼλ��y
#define WIDTH 28   //���̿��
#define HEIGHT 27  //���̸߶�

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



void SnakeInit(Snake* pSnake);  //��ʼ����
bool IsOverlap(Position pos, const Snake *pSnake); //λ�ñ�ռ��
void GameInit(Game *pGame);//��ʼ����Ϸ
Position GenerateFood(int width, int height, const Snake* pSnake);//��ʼ��ʳ��
Position GetNextPosition(const Snake* pSnake); //��һλ��
bool EatFood(Position food, Position next); //�Ե�ʳ��
void AddHead(Snake* pSnake, Position next);//���ӳ��ȵ�ͷ��
void RemoveTail(Snake* pSnake);//ɾ��β��
bool GameOver(const Snake *pSnake, int width, int height);//�ж��Ƿ�����

//����
void DisplayWall(int width, int height);//��ӡǽ
void DisplaySnake(const Snake *pSnake);//��ӡ��
void DisplayFood(const Position *pFood);//��ӡʳ��
void CleanSnakeNode(const Position *pPos);//�ߺ����λ��
void DisplaySnakeNode(const Position *pPos);//��ӡ�߹�֮��Ľڵ�

#endif // !__MODEL_H__

