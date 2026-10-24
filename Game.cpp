#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace
{
	char cellToChar(const Board & board,int r,int c)
	{
		State s = board.getState(r,c);
		if(s == State::Flag) return 'F';
		else if(s == State::Open) 
		{
			if(board.isMine(r,c)) return '*';
			else return (board.getMine(r,c)?'0' + board.getMine(r,c):' ');
		}
		if(board.isOver() && board.isMine(r,c)) return 'X';
		return '#';
	}
}

Game::Game(int r,int c,int m):board(r,c,m){}

void Game::run()
{
	while(!board.isOver())
	{
		clearScreen();
		drawHeader();
		drawBoard();
		int r,c;char op;
		std::string command;
		getline(std::cin,command);
		while(!commandProcessor(command,op,r,c))
		{
			std::cout<<"Invalid command,please try again.\n";
			getline(std::cin,command);
		}
		switch (op)
		{
		case 'f':
			board.flag(r,c);
			break;
		case 'r':
			board.uncover(r,c);
			break;
		default:
			std::cout<<"Invalid operation,please try again.";
			break;
		}
		std::endl(std::cout);
	}
	drawBoard();
}

void Game::clearScreen() const { std::system("cls"); }

bool Game::commandProcessor(const std::string & line,char & op,int & r,int & c) const
{
	std::istringstream iss(line);
	iss>>op>>r>>c;
	if(!iss.fail() && board.isValid(r,c)) return true;
	else return false;
}

void Game::drawBoard() const
{
	int r = board.getRow(),c = board.getColumn();
	std::cout<<"   ";
	for(int i = 0;i < c;i++)
		std::cout<<std::setw(2)<<i;
	std::cout<<"\n";
	for(int i = 0;i < r;i++)
	{
		std::cout<<std::setw(2)<<i<<' ';
		for(int j = 0;j < c;j++)
			std::cout<<' '<<cellToChar(board,i,j);
		std::cout<<"\n";
	}
	std::cout<<"\n";
}

void Game::drawHeader() const
{
	std::cout<<"Total mines: "<<board.getTotalMine()<<"\n";
	std::cout<<"Commands:  r <row> <col>  reveal\n";
    std::cout<<"           f <row> <col>  flag / unflag\n";
    std::cout<<"-----------------------------------------\n";
}