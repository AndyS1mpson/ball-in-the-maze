#include <iostream>;
using namespace std;
#include "Game.h";


 //const int column = 20;//�������
 //const int line = 24;//�������


int main(int argc, const char* argv[])
{
	Game a;

	char c;
	do
	{
		a.Show();
		cin >> c;
	
		system("cls");
		a.Move(c);
	} while (true);

	return 0;
}