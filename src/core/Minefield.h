#pragma once

namespace Minesweep
{

namespace MineTile
{
	enum Type
	{
		EMPTY = 0,
		MINE  = 9,
		CLOSED,
		FLAG,
		WRONG_FLAG
	};
}

typedef unsigned int *Minefield;

inline unsigned int &Get(Minefield field, unsigned int x, unsigned int y, unsigned int cols)
{
	return field[(y*cols)+x];
}

}
