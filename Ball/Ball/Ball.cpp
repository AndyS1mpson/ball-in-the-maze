#include <iostream>;
#include "Game.h";
#include <conio.h>;



int main(int argc, const char* argv[])
{
	Game a;

	char c;
	do
	{
		
		a.Show();
		
		a.Move(_getch());
	
		system("cls");
	} while (true);

	return 0;
}