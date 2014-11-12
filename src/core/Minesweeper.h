#pragma once

#include "Minefield.h"

#include <cstdlib>
#include <ctime>

namespace Minesweep
{

enum class WinState
{
	PLAYING,
	WON,
	LOST
};

class Minesweeper
{
	public:
		Minesweeper(unsigned int cols, unsigned int rows);
		~Minesweeper();

		static inline void SeedRandom(unsigned int seed = std::time(nullptr)) { std::srand(seed); }

		void NewField(unsigned int mineCount);

		void FlagTile(int x, int y);

		void OpenTile(int x, int y);

		void OpenEmptiesFrom(unsigned int x, unsigned int y);
		void OpenAllMines(bool markWrongs);

		inline unsigned int GetCols() const { return cols; }
		inline unsigned int GetRows() const { return rows; }
		inline const Minefield GetField() const { return playfield; }

		inline int GetFlagsLeft() const { return flagsLeft; }
		inline WinState GetWinState() const { return winState; }

	private:
		void CheckForWin();

		unsigned int cols, rows, count;
		Minefield field, playfield;

		int flagsLeft;

		WinState winState;
};

}
