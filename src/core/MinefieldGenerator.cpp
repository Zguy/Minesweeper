#include "MinefieldGenerator.h"

#include <cstdlib>

namespace Minesweep
{

namespace
{

void PlaceMines(Minefield field, unsigned int cols, unsigned int rows, unsigned int mineCount)
{
	for (unsigned int i = 0; i < mineCount; ++i)
	{
		unsigned int x, y;

		do
		{
			x = std::rand() % cols;
			y = std::rand() % rows;
		} while (Get(field,x,y,cols) != MineTile::EMPTY);

		Get(field,x,y,cols) = MineTile::MINE;
	}
}

void PlaceNumbers(Minefield field, unsigned int cols, unsigned int rows)
{
	for (unsigned int y = 0; y < rows; ++y)
	{
		for (unsigned int x = 0; x < cols; ++x)
		{
			unsigned int &tile = Get(field,x,y,cols);
			if (tile == MineTile::EMPTY)
			{
				unsigned int minesAround = 0;
				for (int dy = -1; dy <= +1; ++dy)
				{
					for (int dx = -1; dx <= +1; ++dx)
					{
						if (!((dx == 0)&&(dy == 0)))
						{
							unsigned int nx = x+dx;
							unsigned int ny = y+dy;

							if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && Get(field,nx,ny,cols) == MineTile::MINE)
							{
								++minesAround;
							}
						}
					}
				}

				tile = minesAround;
			}
		}
	}
}

}

void Generate(Minefield field, unsigned int cols, unsigned int rows, unsigned int mineCount)
{
	PlaceMines(field, cols, rows, mineCount);
	PlaceNumbers(field, cols, rows);
}

}
