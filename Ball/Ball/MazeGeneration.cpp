#include <stack>
#include <vector>
#include <time.h>
/*
	Cell represents a cell on a grid which has
	- position (x,y)
	- visited state
	- negihtbours (represented as binary where
		0b0001 = TOP
		0b0010 = RIGHT
		0b0100 = BOTTOM
		0b1000 = LEFT)
*/
// change them for proper output
#define WALL '1'		
#define ROAD ' '

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
char** GenerateMaze(int startX, int startY)
{
	// create grid of cells
	Cell** grid = new Cell * [12]; // rows

	for (int i = 0; i < 12; ++i)
	{
		grid[i] = new Cell[11];
		for (int j = 0; j < 11; j++)
			grid[i][j] = Cell(i, j);
	}

	srand(time(NULL));

	std::stack<Cell>* callStack = new std::stack<Cell>();

	grid[startX][startY].visited = true;

	// let's take random neightbour for start cell, record connection
	// & put this neightbour on a stack

	int neightbours = EMPTY;
	int randomNeightbour;

	for (int i = 0; i < 4; ++i)
	{
		int x = startX + DX[i];
		int y = startY + DY[i];

		if (x > -1 && x < 12 && y > -1 && y < 11)
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
		Cell current = callStack->top();
		neightbours = EMPTY;
		// check if we have any neightbours

		for (int i = 0; i < 4; ++i)
		{
			int x = current.x + DX[i];
			int y = current.y + DY[i];

			if (x > -1 && x < 12 && y > -1 && y < 11)
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

	} while (!callStack->empty());

	// now we have links between cells & we need to convert them to our normal grid, that we gonna return
	char** resultGrid = new char* [25];
	for (int i = 0; i < 25; ++i)
	{
		resultGrid[i] = new char[23];
		for (int j = 0; j < 23; ++j)
			resultGrid[i][j] = WALL;
	}

	for (int gridI = 0, resultGridI = 1; gridI < 12; gridI++, resultGridI += 2)
	{
		for (int gridJ = 0, resultGridJ = 1; gridJ < 11; gridJ++, resultGridJ += 2)
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
	for (int i = 0; i < 12; ++i)
		delete[] grid[i];
	delete[] grid;
	delete callStack;

	return resultGrid;
}