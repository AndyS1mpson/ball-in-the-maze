#include"Game.h";

static int level=1;
void Game::Move(char button)
{

	switch (button)
	{
	case 'w':
		if (mas[level-1][Ball_Coordinates.y - 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y <=rows)
			Ball_Coordinates.y--;
		break;
	case 's':
		if (mas[level-1][Ball_Coordinates.y + 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y >= 0)
			Ball_Coordinates.y++;
		break;
	case 'a':
		if (mas[level-1][Ball_Coordinates.y][Ball_Coordinates.x - 1] != 1 && Ball_Coordinates.x >= 0)
			Ball_Coordinates.x--;
		break;
	case 'd': 
		if (mas[level-1][Ball_Coordinates.y][Ball_Coordinates.x + 1] != 1 && Ball_Coordinates.x <cols)
			Ball_Coordinates.x++;
		break;

	}
}

void Game::Show()
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == Ball_Coordinates.y && j == Ball_Coordinates.x)
				std::cout << (char)(79);
			else if (mas[level-1][i][j] == 1)
				std::cout << (char)(176);
			else if (mas[level-1][i][j] == 0)
				std::cout << " ";

			if (Ball_Coordinates.x == 1 && Ball_Coordinates.y == 0)
			{
				if (level != 3)
				{
					level++;
					Ball_Coordinates.x = 1;
					Ball_Coordinates.y = 25;
				}
				else FinishGame();
			}
		}
		std::cout << std::endl;
	}

}

void Game::FinishGame()
{
	system("cls");
	std::cout << "You win" << std::endl;
	std::cout << "Close game?" << std::endl;
	std::cout << "1)Yes     2)No" << std::endl;
	int c;
	std::cin >> c;
	if (c == 1)
		exit(0);
	else
	{
		system("cls");
		Ball_Coordinates.x = 1;
		Ball_Coordinates.y = 23;
		
	}

}
