#include "Game.hpp"
#include <iostream>
#include <windows.h>

int main()
{
	SetConsoleTitleW(L"MineSweeper");
	system("color 4F");
	int level,r,c,m;
	std::cout<<"level:\n1 primary 10x10 / 20\n2 middle 15x15 / 60\n3 high 20x20 150\n(1/2/3)?\n";
	std::cin>>level;getchar();
	switch (level)
	{
	case 1:
		r = 10,c = 10,m = 20;
		break;
	case 2:
		r = 15,c = 15,m = 60;
		break;
	case 3:
		r = 20,c = 20,m = 150;
		break;
	default:
		std::cout<<"Invalid number.";
		return 0;
	}
	Game game(r,c,m);
	game.run();
	system("pause");
}