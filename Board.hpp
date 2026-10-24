#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>
#include "Cell.hpp"

class Board
{
	private:
	int row,column,mine,safeCell;
	bool gameOver;
	std::vector<std::vector<Cell>> cells;
	void countNeighboringMines();
	void randomPlacement();

	public:
	Board(int r,int c,int m);
	~Board();
	bool isValid(int r,int c) const;
	void uncover(int r,int c);
	void flag(int r,int c);
	int getRow() const;
	int getColumn() const;
	int getTotalMine() const;
	bool isOver() const;
	State getState(int r,int c) const;
	int getMine(int r,int c) const;
	bool isMine(int r,int c) const;
};

#endif