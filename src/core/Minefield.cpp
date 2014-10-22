#include "Minefield.h"

namespace Minesweep
{

Minefield::Minefield(const unsigned int cols, const unsigned int rows, bool close) : cols(cols), rows(rows)
{
	field = new unsigned int[cols*rows];
	Clear(close);
}

Minefield::~Minefield()
{
	delete field;
}

void Minefield::Clear(bool close)
{
	for (unsigned int y = 0; y < rows; ++y)
	{
		for (unsigned int x = 0; x < cols; ++x)
		{
			Get(x,y) = (close ? MineTile::CLOSED : MineTile::EMPTY);
		}
	}
}

}
