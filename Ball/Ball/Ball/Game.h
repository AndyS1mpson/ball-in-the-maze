#pragma once
#include <iostream>

struct Point
{
public:
	int x;
	int y;
};


class Game
{
private:
	static const int cols = 13;
	static const int rows = 15;
	char mas[rows][cols];
	Point Start;
	Point Finish;
	Point Ball_Coordinates;
	char _direction;

public:
	Game();

	void Move();
	void Show();
	void ContinuousMove();
	void SetDirection(char);
	
	void FinishGame();
};

