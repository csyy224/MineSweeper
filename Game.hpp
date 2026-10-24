#ifndef GAME_HPP
#define GAME_HPP
#include "Board.hpp"
#include <string>

class Game
{
	private:
	Board board;
	void clearScreen() const;
	void drawBoard() const;
	void drawHeader() const;
	bool commandProcessor(const std::string & line,char & op,int & r,int & c) const;

	public:
	Game(int r,int c,int m);
	void run();
};

#endif