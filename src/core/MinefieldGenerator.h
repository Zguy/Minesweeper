#pragma once

#include "Minefield.h"

namespace Minesweep
{

class MinefieldGenerator
{
	public:
		MinefieldGenerator(Minefield &field);
		~MinefieldGenerator();

		void Generate(const unsigned int numMines);

		void PlaceMines(const unsigned int numMines);
		void PlaceNumbers();

	private:
		Minefield &field;
};

}
