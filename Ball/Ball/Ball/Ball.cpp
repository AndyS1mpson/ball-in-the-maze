#include <iostream>;
#include "Game.h";
#include <conio.h>;
#include <windows.h>

int main(int argc, const char* argv[])
{
	Game a;
	std:: cout << "Ball in the maze";
	Sleep(3000);
	system("cls");
	std::cout << "level:1";
	Sleep(3000);
	system("cls");
	char button;
	
	do
	{
		if (_kbhit()) {
			button = _getch();
			if (button == 'q')
			{
				a.FinishGame();
				break;
			}

			a.SetDirection(button);
		}		
		
		a.Move();
		
		a.Show();

		Sleep(10);

		system("cls");

	} while (true);

	return 0;
}