#include "Minesweeper.h"

#include <iostream>

struct Difficulty
{
	unsigned int cols;
	unsigned int rows;
	unsigned int numMines;
};
const Difficulty easy { 9, 9, 10 }, medium { 16, 16, 40 }, hard { 16, 30, 99 };

void DrawField(const Minesweep::Minefield field, unsigned int cols, unsigned int rows)
{
	std::cout << "   ";
	for (unsigned int x = 0; x < cols; ++x)
	{
		std::cout << x;
		if (x < 10)
			std::cout << " ";
	}
	std::cout << "\n  ";
	for (unsigned int i = 0; i < cols*2+2; ++i)
		std::cout << "-";
	std::cout << "\n";

	for (unsigned int y = 0; y < rows; ++y)
	{
		if (y < 10)
			std::cout << " ";
		std::cout << y << "|";
		for (unsigned int x = 0; x < cols; ++x)
		{
			char tile;
			unsigned int fieldTile = Minesweep::Get(field,x,y,cols);
			switch (fieldTile)
			{
				using namespace Minesweep::MineTile;
				case EMPTY      : tile = ' '; break;
				case MINE       : tile = '*'; break;
				case CLOSED     : tile = '#'; break;
				case FLAG       : tile = '!'; break;
				case WRONG_FLAG : tile = 'x'; break;
				default         : tile = 48+fieldTile; break; // 48+number = ASCII representation of the number
			}

			std::cout << tile << " ";
		}
		std::cout << "|" << y << "\n";
	}
	std::cout << "  ";
	for (unsigned int i = 0; i < cols*2+2; ++i)
		std::cout << "-";
	std::cout << "\n   ";

	for (unsigned int x = 0; x < cols; ++x)
	{
		std::cout << x;
		if (x < 10)
			std::cout << " ";
	}
	std::cout << "\n";

	std::cout << std::flush;
}

Difficulty ChooseDifficulty()
{
	Difficulty diff;
	std::cout << "Difficulty (e,m,h): ";
	char d;
	std::cin >> d;

	switch (d)
	{
		case 'e' : diff = easy;   break;
		case 'm' : diff = medium; break;
		case 'h' : diff = hard;   break;
		default  : diff = easy;   break;
	}

	return diff;
}

int main()
{
	using namespace Minesweep;
	Minesweeper::SeedRandom();

	char again;
	do
	{
		Difficulty diff = ChooseDifficulty();

		Minesweeper ms(diff.cols, diff.rows);
		ms.NewField(diff.numMines);

		bool playing = true;
		while (playing)
		{
			std::cout << "Flags left: " << ms.GetFlagsLeft() << '\n';
			DrawField(ms.GetField(), ms.GetCols(), ms.GetRows());

			WinState winState = ms.GetWinState();
			if (winState == WinState::PLAYING)
			{
				char flagmode;
				unsigned int x, y;
				std::cin >> flagmode >> x >> y;
				std::cout << "\n\n\n" << std::endl;

				if (x > diff.cols && y > diff.rows)
				{
					playing = false;
				}
				else
				{
					if (flagmode == 'f')
						ms.FlagTile(x,y);
					else if (flagmode == 'o')
						ms.OpenTile(x,y);
				}
			}
			else if (winState == WinState::LOST)
			{
				std::cout << "BAM! YOU LOST!" << std::endl;
				playing = false;
			}
			else if (winState == WinState::WON)
			{
				std::cout << "YOU WON!" << std::endl;
				playing = false;
			}
		}

		std::cout << "Play again (y,n)? ";
		std::cin >> again;
	} while (again == 'y');

	return 0;
}
