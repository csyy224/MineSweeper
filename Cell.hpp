#ifndef CELL_HPP
#define CELL_HPP

enum class State { Hide,Open,Flag,Err };

struct Cell
{
	State state;
	bool isMine;
	int mineCount;
};

#endif