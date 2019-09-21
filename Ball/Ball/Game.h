#pragma once
#include <iostream>;
using namespace std;

struct Point
{
public:
	int x;
	int y;
};

class Game
{
private:
	const int mas[24][20];
	Point Ball_Coordinates;

public:
	Game() :mas{ {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						{1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,},
						{1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,0,1,},
						{1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,},
						{1,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,},
						{1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,},
						{1,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,0,1,},
						{1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,},
						{1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,},
						{1,1,0,0,0,1,0,0,1,1,0,1,1,1,1,0,0,0,0,1,},
						{1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,},
						{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,},
						{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,},
						{1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,},
						{1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,0,1,},
						{1,0,1,1,0,1,1,0,1,0,1,1,1,0,1,0,0,0,0,1,},
						{1,0,1,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,1,1,},
						{1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,},
						{1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,},
						{1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,},
						{1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,},
						{1,0,1,0,1,1,1,1,1,0,0,0,1,0,1,0,0,1,0,1,},
						{1,0,1,0,0,0,0,0,1,1,1,0,0,0,1,0,1,1,0,1,},
						{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,} }
	{

		Ball_Coordinates.x = 1;
		Ball_Coordinates.y = 23;
	}


	void Move(char button)
	{

		switch (button)
		{
		case 'w':
			if (mas[Ball_Coordinates.y - 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y <= 23)
				Ball_Coordinates.y--;
			break;
		case 's':
			if (mas[Ball_Coordinates.y + 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y >= 0)
				Ball_Coordinates.y++;
			break;
		case 'a':
			if (mas[Ball_Coordinates.y][Ball_Coordinates.x - 1] != 1 && Ball_Coordinates.x >= 0)
				Ball_Coordinates.x--;
			break;
		case 'd':
			if (mas[Ball_Coordinates.y][Ball_Coordinates.x + 1] != 1 && Ball_Coordinates.x <= 23)
				Ball_Coordinates.x++;
			break;

		}
	}


	void Show()
	{
		
			for (int i = 0; i < 24; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					if(i == Ball_Coordinates.y && j == Ball_Coordinates.x) 
						cout << static_cast<char>(9824);
					else if (mas[i][j] == 1)
						cout << static_cast<char>(176);
					else if (mas[i][j] == 0)
						cout << " ";

					if (Ball_Coordinates.x == 1 && Ball_Coordinates.y == 0)
					{
						system("cls");
						cout << "You win";
					}
				}
				cout << endl;
			}
	
	}
		
};

