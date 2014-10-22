#pragma once

#include <Minefield.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

static const unsigned int TILESIZE = 32;
static const float TILEPADDING = 1.0f;

struct Tile
{
	sf::Sprite sprite;
	unsigned int x;
	unsigned int y;
};

typedef std::vector<Tile> TileList;

class SFMLMinefield
{
	public:
		SFMLMinefield(const Minesweep::Minefield &field, const sf::Vector2f &origin);
		~SFMLMinefield();

		void DrawField(sf::RenderWindow &win);
		void UpdateField();

		Tile *GetTileFromMouse(const sf::Vector2i &mousePos);

		inline sf::Vector2f GetTilePosition(const unsigned int x, const unsigned int y)
		{
			return sf::Vector2f(origin.x + (TILESIZE * x) + (TILEPADDING * x), origin.y + (TILESIZE * y) + (TILEPADDING * y));
		}

		inline sf::Vector2f GetSizeOfField()
		{
			return sf::Vector2f(GetTilePosition(field.GetCols()-1, 0).x + TILESIZE+TILEPADDING, GetTilePosition(0, field.GetRows()-1).y + TILESIZE+TILEPADDING);
		}

		inline void SetOrigin(const sf::Vector2f &nOrigin) { origin = nOrigin; }

	private:
		sf::Texture closedTile;
		sf::Texture openTile;
		sf::Texture flagTile;
		sf::Texture wrongFlagTile;
		sf::Texture mineTile;
		sf::Texture numTile[8];

		TileList tiles;

		sf::Vector2f origin;

		const Minesweep::Minefield &field;
};
