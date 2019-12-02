#include"Game.h";
#include"Stack.h"
#include <time.h>
#include <windows.h>
#pragma region MazeGeneration



#define WALL 1
#define ROAD 0
#define TOP 0b0001
#define RIGHT 0b0010
#define BOTTOM 0b0100
#define LEFT 0b1000
#define EMPTY 0b0000

int DX[4] = { -1, 0, 1, 0 };
int DY[4] = { 0, 1, 0, -1 };
int NEIGHTBOURS[4] = { TOP, RIGHT, BOTTOM, LEFT };

struct Cell
{
	Cell()
	{
		x = y = 0;
		visited = false;
		neightbours = 0b0000;
	}

	Cell(int x, int y)
	{
		this->x = x;
		this->y = y;
		visited = false;
		neightbours = 0b0000;
	}

	short x;
	short y;
	bool visited;
	int neightbours;
};

/*
	We use 25(rows) by 23(cols) grid filled with 0 & 1
	0 mean this is a free cell & we can use it as we wish
	1 mean that this is wall & we can't use it

	Actually we work with the grid of 12x11 (we double
	and increase number by 1 to get the final grid)

	We use DFS algorithm which works simply:
	1. Choose initial cell
	2. Check if we can visit any neightbour of the cell
		Y => 	pick random neightbour
				put it on a stack
				mark path to neightbour
		N => 	cell is visited
	3. Pop cell from the stack, go back to 2
*/
char** GenerateMaze(int startX, int startY, int rows, int cols)
{
	// create grid of cells
	Cell** grid = new Cell * [rows]; // rows

	for (int i = 0; i < rows; ++i)
	{
		grid[i] = new Cell[cols];
		for (int j = 0; j < cols; j++)
			grid[i][j] = Cell(i, j);
	}

	srand(time(NULL));

	Stack<Cell>* callStack = new Stack<Cell>();

	grid[startX][startY].visited = true;

	// let's take random neightbour for start cell, record connection
	// & put this neightbour on a stack

	int neightbours = EMPTY;
	int randomNeightbour;

	for (int i = 0; i < 4; ++i)
	{
		int x = startX + DX[i];
		int y = startY + DY[i];

		if (x > -1 && x < rows && y > -1 && y < cols)
			if (!grid[x][y].visited)
				neightbours += NEIGHTBOURS[i];
	}

	do
	{
		randomNeightbour = rand() % 4;
	} while ((neightbours & NEIGHTBOURS[randomNeightbour]) == 0);

	grid[startX][startY].neightbours += NEIGHTBOURS[randomNeightbour];

	int _x = startX + DX[randomNeightbour];
	int _y = startY + DY[randomNeightbour];

	grid[_x][_y].visited = true;

	callStack->push(grid[_x][_y]);

	do
	{
		Cell current = callStack->getTopLink();			//Changes
		neightbours = EMPTY;
		// check if we have any neightbours

		for (int i = 0; i < 4; ++i)
		{
			int x = current.x + DX[i];
			int y = current.y + DY[i];

			if (x > -1 && x < rows && y > -1 && y < cols)
				if (!grid[x][y].visited)
					neightbours += NEIGHTBOURS[i];
		}

		if (neightbours == EMPTY)
		{
			callStack->pop();
			continue;
		}

		// if we have any => choose one random => put it on a stack
		do
		{
			randomNeightbour = rand() % 4;
		} while ((neightbours & NEIGHTBOURS[randomNeightbour]) == 0);

		grid[current.x][current.y].neightbours += NEIGHTBOURS[randomNeightbour];
		_x = current.x + DX[randomNeightbour];
		_y = current.y + DY[randomNeightbour];

		grid[_x][_y].visited = true;
		callStack->push(grid[_x][_y]);

	} while (!callStack->isEmpty());					//Changes

	int _rows = rows * 2 + 1;
	int _cols = cols * 2 + 1;

	// now we have links between cells & we need to convert them to our normal grid, that we gonna return
	char** resultGrid = new char* [_rows];
	for (int i = 0; i < _rows; ++i)
	{
		resultGrid[i] = new char[_cols];
		for (int j = 0; j < _cols; ++j)
			resultGrid[i][j] = WALL;
	}

	for (int gridI = 0, resultGridI = 1; gridI < rows; gridI++, resultGridI += 2)
	{
		for (int gridJ = 0, resultGridJ = 1; gridJ < cols; gridJ++, resultGridJ += 2)
		{
			for (int k = 0; k < 4; ++k)
			{
				if ((grid[gridI][gridJ].neightbours & NEIGHTBOURS[k]) != EMPTY)
				{
					resultGrid[resultGridI][resultGridJ] = ROAD;
					resultGrid[resultGridI + DX[k]][resultGridJ + DY[k]] = ROAD;
					resultGrid[resultGridI + 2 * DX[k]][resultGridJ + 2 * DY[k]] = ROAD;
				}
			}
		}
	}

	// free memory
	for (int i = 0; i < rows; ++i)
		delete[] grid[i];
	delete[] grid;
	delete callStack;

	return resultGrid;
}

#pragma endregion

static int level = 1;

Game::Game()
{
	char** grid = GenerateMaze(0, 0, 7,6);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mas[i][j] = grid[i][j];
		}
	}
	delete[] grid;
	Ball_Coordinates.x = Start.x = 1;
	Ball_Coordinates.y = Start.y = 1;
	Finish.x = 11;
	Finish.y = 13;
};

void Game::Move(char button)
{

	switch (button)
	{
	case 'w':
		if (mas[Ball_Coordinates.y - 1][Ball_Coordinates.x] != 1 && Ball_Coordinates.y <=rows)
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
		if (mas[Ball_Coordinates.y][Ball_Coordinates.x + 1] != 1 && Ball_Coordinates.x <cols)
			Ball_Coordinates.x++;
		break;

	}
}

void Game::Show()
{
	if (level !=4)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (i == Ball_Coordinates.y && j == Ball_Coordinates.x)
					std::cout << (char)(79);
				else if (i == Finish.y && j == Finish.x)
					std::cout << (char)(58);
				else if (mas[i][j] == 1)
					std::cout << (char)(176);
				else if (mas[i][j] == 0)
					std::cout << " ";
			}
			std::cout << std::endl;
			if (Ball_Coordinates.x == 11 && Ball_Coordinates.y == 13)
			{	
				level++;
				system("cls");
				cout << "level:" << level;
				Sleep(3000);
				system("cls");
				Ball_Coordinates.x = 1;
				Ball_Coordinates.y = 1;
				

				char** grid1 = GenerateMaze(0, 0,7,6);
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						mas[i][j] = grid1[i][j];
					}
				}
			}
			/*if (Ball_Coordinates.x == 1 && Ball_Coordinates.y == 0)
			{
				if (level != 3)
				{
					level++;
					Ball_Coordinates.x = 1;
					Ball_Coordinates.y = 25;
				}
				else FinishGame();
			}*/
		}
		std::cout << std::endl;
	}
	else if (level == 4)
		FinishGame();
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
