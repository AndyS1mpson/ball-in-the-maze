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

public:
	Game();

	void Move(char);
	void Show();
	
	void FinishGame();
};

