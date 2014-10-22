#pragma once

#include "Minefield.h"

#include <cstdlib>
#include <ctime>

namespace Minesweep
{

enum WinState
{
	PLAYING = 1,
	WON,
	LOST
};

class Minesweeper
{
	public:
		Minesweeper(const unsigned int cols, const unsigned int rows);
		~Minesweeper();

		static inline void SeedRandom(unsigned int seed = std::time(nullptr)) { std::srand(seed); }

		void NewField(const unsigned int numMines);

		void FlagTile(const int x, const int y);

		void OpenTile(const int x, const int y);

		void OpenEmptiesFrom(const unsigned int x, const unsigned int y);
		void OpenAllMines(bool markWrongs = true);

		inline const Minefield &GetField() const { return playfield; }
		inline const int GetFlagsLeft() const { return flagsLeft; }
		inline const WinState GetWinState() const { return winState; }

	private:
		void CheckForWin();

		Minefield field;
		Minefield playfield;

		int flagsLeft;

		WinState winState;
};

}
