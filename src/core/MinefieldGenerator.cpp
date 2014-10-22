#include "MinefieldGenerator.h"

#include <cstdlib>

namespace Minesweep
{

MinefieldGenerator::MinefieldGenerator(Minefield &field) : field(field)
{
}

MinefieldGenerator::~MinefieldGenerator()
{
}

void MinefieldGenerator::Generate(const unsigned int numMines)
{
	PlaceMines(numMines);
	PlaceNumbers();
}

void MinefieldGenerator::PlaceMines(const unsigned int numMines)
{
	for (unsigned int i = 0; i < numMines; ++i)
	{
		unsigned int x, y;

		do
		{
			x = std::rand() % field.GetCols();
			y = std::rand() % field.GetRows();
		} while (field.Get(x,y) != MineTile::EMPTY);

		field.Get(x,y) = MineTile::MINE;
	}
}

void MinefieldGenerator::PlaceNumbers()
{
	for (unsigned int y = 0; y < field.GetRows(); ++y)
	{
		for (unsigned int x = 0; x < field.GetCols(); ++x)
		{
			if (field.Get(x,y) == MineTile::EMPTY)
			{
				unsigned int minesAround = 0;
				for (int dy = -1; dy <= +1; ++dy)
				{
					for (int dx = -1; dx <= +1; ++dx)
					{
						if (!((dx == 0)&&(dy == 0)))
						{
							const unsigned int nx = x+dx;
							const unsigned int ny = y+dy;

							if ((nx >= 0)&&(nx < field.GetCols())&&(ny >= 0)&&(ny < field.GetRows()))
							{
								if (field.Get(nx,ny) == MineTile::MINE)
									++minesAround;
							}
						}
					}
				}
				field.Get(x,y) = minesAround;
			}
		}
	}
}

}
