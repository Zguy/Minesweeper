#include "Minesweeper.h"
#include "MinefieldGenerator.h"

namespace Minesweep
{

Minesweeper::Minesweeper(unsigned int cols, unsigned int rows) : cols(cols), rows(rows), count(cols * rows), flagsLeft(0), winState(WinState::PLAYING)
{
	field = new unsigned int[count];
	playfield = new unsigned int[count];

	for (unsigned int i = 0; i < count; ++i)
	{
		field[i] = MineTile::EMPTY;
		playfield[i] = MineTile::CLOSED;
	}
}

Minesweeper::~Minesweeper()
{
	delete[] field;
	delete[] playfield;
	field = playfield = nullptr;
}

void Minesweeper::NewField(unsigned int mineCount)
{
	Generate(field, cols, rows, mineCount);

	for (unsigned int i = 0; i < count; ++i)
	{
		playfield[i] = MineTile::CLOSED;
	}

	flagsLeft = mineCount;
}

void Minesweeper::FlagTile(int x, int y)
{
	if (x >= 0 && x < static_cast<int>(cols) && y >= 0 && y < static_cast<int>(rows))
	{
		unsigned int &tile = Get(playfield,x,y,cols);
		if (tile == MineTile::CLOSED)
		{
			tile = MineTile::FLAG;
			--flagsLeft;
		}
		else if (tile == MineTile::FLAG)
		{
			tile = MineTile::CLOSED;
			++flagsLeft;
		}
	}
}

void Minesweeper::OpenTile(int x, int y)
{
	if (x >= 0 && x < static_cast<int>(cols) && y >= 0 && y < static_cast<int>(rows))
	{
		unsigned int &playtile = Get(playfield,x,y,cols);
		if (playtile == MineTile::CLOSED)
		{
			unsigned int &tile = Get(field,x,y,cols);
			playtile = tile;

			if (tile == MineTile::EMPTY)
			{
				OpenEmptiesFrom(x,y);
			}
			else if (tile == MineTile::MINE)
			{
				OpenAllMines(true);
				winState = WinState::LOST;
			}
			else
			{
				CheckForWin();
			}
		}
	}
}

void Minesweeper::OpenEmptiesFrom(unsigned int x, unsigned int y)
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
	for (unsigned int i = 0; i < count; ++i)
	{
		bool isMine = field[i] == MineTile::MINE;
		bool isFlag = playfield[i] == MineTile::FLAG;
		if (isMine && !isFlag)
		{
			playfield[i] = MineTile::MINE;
		}
		else if (markWrongs && !isMine && isFlag)
		{
			playfield[i] = MineTile::WRONG_FLAG;
		}
	}
}

void Minesweeper::CheckForWin()
{
	for (unsigned int i = 0; i < count; ++i)
	{
		unsigned int tile = playfield[i];
		if ((tile == MineTile::CLOSED || tile == MineTile::FLAG) && field[i] != MineTile::MINE)
			return;
	}

	// If we get through the loop, we have won!
	OpenAllMines(false);
	winState = WinState::WON;
}

}
