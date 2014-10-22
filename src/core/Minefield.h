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

class Minefield
{
	public:
		Minefield(const unsigned int cols, const unsigned int rows, bool close = false);
		~Minefield();

		inline unsigned int &Get(const unsigned int x, const unsigned int y) { return field[(y*cols)+x]; }
		inline const unsigned int &Get(const unsigned int x, const unsigned int y) const { return field[(y*cols)+x]; }

		void Clear(bool close = false);

		inline const unsigned int GetCols() const { return cols; }
		inline const unsigned int GetRows() const { return rows; }

	private:
		unsigned int *field;
		const unsigned int cols, rows;
};

}
