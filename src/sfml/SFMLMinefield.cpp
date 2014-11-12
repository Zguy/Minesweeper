#include "SFMLMinefield.h"

SFMLMinefield::SFMLMinefield(const Minesweep::Minefield field, unsigned int cols, unsigned int rows, const sf::Vector2f &origin) : origin(origin), cols(cols), rows(rows), field(field)
{
	closedTile.loadFromFile("data/closed.png");
	openTile.loadFromFile("data/open.png");
	flagTile.loadFromFile("data/flag.png");
	wrongFlagTile.loadFromFile("data/wrongFlag.png");
	mineTile.loadFromFile("data/mine.png");
	numTile[0].loadFromFile("data/1.png");
	numTile[1].loadFromFile("data/2.png");
	numTile[2].loadFromFile("data/3.png");
	numTile[3].loadFromFile("data/4.png");
	numTile[4].loadFromFile("data/5.png");
	numTile[5].loadFromFile("data/6.png");
	numTile[6].loadFromFile("data/7.png");
	numTile[7].loadFromFile("data/8.png");
}

SFMLMinefield::~SFMLMinefield()
{
}

void SFMLMinefield::DrawField(sf::RenderWindow &win)
{
	for (TileList::iterator it = tiles.begin(); it != tiles.end(); ++it)
	{
		win.draw((*it).sprite);
	}
}

void SFMLMinefield::UpdateField()
{
	tiles.clear();

	for (unsigned int y = 0; y < rows; ++y)
	{
		for (unsigned int x = 0; x < cols; ++x)
		{
			bool useFrontTile = true;
			sf::Sprite tile;
			sf::Sprite backTile;
			unsigned int fieldTile = Minesweep::Get(field,x,y,cols);
			switch (fieldTile)
			{
				using namespace Minesweep::MineTile;
				case EMPTY      : backTile = sf::Sprite(openTile);   useFrontTile = false;             break;
				case MINE       : backTile = sf::Sprite(openTile);   tile = sf::Sprite(mineTile);      break;
				case CLOSED     : backTile = sf::Sprite(closedTile); useFrontTile = false;             break;
				case FLAG       : backTile = sf::Sprite(closedTile); tile = sf::Sprite(flagTile);      break;
				case WRONG_FLAG : backTile = sf::Sprite(closedTile); tile = sf::Sprite(wrongFlagTile); break;
				default         : backTile = sf::Sprite(openTile);   tile = sf::Sprite(numTile[fieldTile-1]); break;
			}

			sf::Vector2f tilePos = GetTilePosition(x,y);
			backTile.setPosition(tilePos);
			if (useFrontTile)
				tile.setPosition(tilePos);

			Tile btile;
			btile.sprite = backTile;
			btile.x = x;
			btile.y = y;
			tiles.push_back(btile);
			if (useFrontTile)
			{
				Tile ftile;
				ftile.sprite = tile;
				ftile.x = x;
				ftile.y = y;
				tiles.push_back(ftile);
			}
		}
	}
}

Tile *SFMLMinefield::GetTileFromMouse(const sf::Vector2i &mousePos)
{
	Tile *tile = nullptr;
	for (Tile &it : tiles)
	{
		sf::Sprite &currTile = it.sprite;
		const sf::Vector2f &pos = currTile.getPosition();
		const sf::FloatRect bounds = currTile.getLocalBounds();
		if ((mousePos.x > pos.x)&&(mousePos.x < pos.x+bounds.width)&&(mousePos.y > pos.y)&&(mousePos.y < pos.y+bounds.height))
		{
			tile = &it;
			break;
		}
	}

	return tile;
}
