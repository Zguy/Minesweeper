#include "Minesweeper.h"
#include "MinefieldGenerator.h"

namespace Minesweep
{

Minesweeper::Minesweeper(const unsigned int cols, const unsigned int rows) : field(cols,rows), playfield(cols,rows,true), flagsLeft(0), winState(PLAYING)
{
}

Minesweeper::~Minesweeper()
{
}

void Minesweeper::NewField(const unsigned int numMines)
{
	MinefieldGenerator gen(field);
	gen.Generate(numMines);

	playfield.Clear(true);

	flagsLeft = numMines;
}

void Minesweeper::FlagTile(const int x, const int y)
{
	if ((x >= 0)&&(x < static_cast<const int>(field.GetCols()))&&(y >= 0)&&(y < static_cast<const int>(field.GetRows())))
	{
		if (playfield.Get(x,y) == MineTile::CLOSED)
		{
			playfield.Get(x,y) = MineTile::FLAG;
			--flagsLeft;
		}
		else if (playfield.Get(x,y) == MineTile::FLAG)
		{
			playfield.Get(x,y) = MineTile::CLOSED;
			++flagsLeft;
		}
	}
}

void Minesweeper::OpenTile(const int x, const int y)
{
	if ((x >= 0)&&(x < static_cast<const int>(field.GetCols()))&&(y >= 0)&&(y < static_cast<const int>(field.GetRows()))&&(playfield.Get(x,y) == MineTile::CLOSED))
	{
		playfield.Get(x,y) = field.Get(x,y);

		if (field.Get(x,y) == MineTile::EMPTY)
		{
			OpenEmptiesFrom(x,y);
		}
		else if (field.Get(x,y) == MineTile::MINE)
		{
			OpenAllMines();
			winState = LOST;
		}
		else
		{
			CheckForWin();
		}
	}
}

void Minesweeper::OpenEmptiesFrom(const unsigned int x, const unsigned int y)
{
	OpenTile(x-1, y-1);
	OpenTile(x  , y-1);
	OpenTile(x+1, y-1);
	OpenTile(x-1, y  );
	OpenTile(x+1, y  );
	OpenTile(x-1, y+1);
	OpenTile(x  , y+1);
	OpenTile(x+1, y+1);
}

void Minesweeper::OpenAllMines(bool markWrongs)
{
	for (unsigned int y = 0; y < field.GetRows(); ++y)
	{
		for (unsigned int x = 0; x < field.GetCols(); ++x)
		{
			if (field.Get(x,y) == MineTile::MINE)
			{
				if (playfield.Get(x,y) != MineTile::FLAG)
					playfield.Get(x,y) = MineTile::MINE;
			}
			else
				if ((markWrongs)&&(playfield.Get(x,y) == MineTile::FLAG))
					playfield.Get(x,y) = MineTile::WRONG_FLAG;
		}
	}
}

void Minesweeper::CheckForWin()
{
	for (unsigned int y = 0; y < field.GetRows(); ++y)
	{
		for (unsigned int x = 0; x < field.GetCols(); ++x)
		{
			if (((playfield.Get(x,y) == MineTile::CLOSED)||(playfield.Get(x,y) == MineTile::FLAG))&&(field.Get(x,y) != MineTile::MINE))
				return;
		}
	}

	// If we get through the loop, we have won!
	OpenAllMines(false);
	winState = WON;
}

}
