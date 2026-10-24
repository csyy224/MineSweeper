#include "Board.hpp"
#include <iostream>
#include <random>

void Board::randomPlacement()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> rangeX(0,column - 1);
	std::uniform_int_distribution<int> rangeY(0,row - 1);
	for(int i = 0;i < mine;i++)
	{
		int x = rangeX(rng),y = rangeY(rng);
		while(cells[y][x].isMine)	x = rangeX(rng),y = rangeY(rng);
		cells[y][x].isMine = true;
	}
}

bool Board::isValid(int r,int c) const { return r >= 0 && r <= row - 1 && c >= 0 && c <= column - 1; }

void Board::countNeighboringMines()
{
	for(int i = 0;i < row;i++)
		for(int j = 0;j < column;j++)
			cells[i][j].mineCount = (isValid(i - 1,j - 1)?cells[i - 1][j - 1].isMine:0)
								  + (isValid(i - 1,j    )?cells[i - 1][j    ].isMine:0)
								  + (isValid(i    ,j - 1)?cells[i    ][j - 1].isMine:0)
								  + (isValid(i + 1,j + 1)?cells[i + 1][j + 1].isMine:0)
								  + (isValid(i + 1,j    )?cells[i + 1][j    ].isMine:0)
								  + (isValid(i    ,j + 1)?cells[i    ][j + 1].isMine:0)
								  + (isValid(i - 1,j + 1)?cells[i - 1][j + 1].isMine:0)
								  + (isValid(i + 1,j - 1)?cells[i + 1][j - 1].isMine:0);
}

Board::Board(int r,int c,int m)
{
	row = r;
	column = c;
	mine = m;
	gameOver = false;
	safeCell = r * c - m;
	cells.resize(r,std::vector<Cell>(c,{State::Hide,false,-1}));
	randomPlacement();
	countNeighboringMines();
}

void Board::uncover(int r,int c)
{
	if(!isValid(r,c)) 
	{
		std::cout<<"Invalid position! Please try again.";
		return ;
	}
	if(cells[r][c].state == State::Open)
	{
		std::cout<<"Already open,please try again.";
		return ;
	}
	if(cells[r][c].state == State::Flag)
	{
		std::cout<<"You sure? Hhh";
		return ;
	}
	if(cells[r][c].isMine) 
	{
		gameOver = true;
		std::cout<<"It's a BIG MINE!!!";
		return ;
	}
	else
	{
		cells[r][c].state = State::Open;
		safeCell--;
		if(!safeCell) 
		{
			gameOver = true;
			std::cout<<"Congrats! You win!!!";
			return ;
		}
	}
}

void Board::flag(int r,int c)
{
	if(!isValid(r,c)) 
	{
		std::cout<<"Invalid position! Please try again.";
		return ;
	}
	if(cells[r][c].state == State::Open)
	{
		std::cout<<"Already open,please try again.";
		return ;
	}
	else if(cells[r][c].state == State::Flag)
		cells[r][c].state = State::Hide;
	else 
		cells[r][c].state = State::Flag;
}

bool Board::isOver() const { return gameOver; }

int Board::getColumn() const { return column; }

int Board::getRow() const { return row; }

int Board::getTotalMine() const { return mine; }

State Board::getState(int r,int c) const
{
	if(!isValid(r,c)) 
	{
		std::cout<<"Invalid position! Please try again.";
		return State::Err;
	}
	return cells[r][c].state;
}

int Board::getMine(int r,int c) const
{
	if(!isValid(r,c)) 
	{
		std::cout<<"Invalid position! Please try again.";
		return -1;
	}
	return cells[r][c].mineCount;
}

bool Board::isMine(int r,int c) const { return isValid(r,c) && cells[r][c].isMine; }

Board::~Board() = default;
