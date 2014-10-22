#include "SFMLMinefield.h"

#include <Minesweeper.h>

#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>

struct Difficulty
{
	unsigned int cols;
	unsigned int rows;
	unsigned int numMines;
};
Difficulty ChooseDifficulty()
{
	static const Difficulty easy { 9, 9, 10 }, medium { 16, 16, 40 }, hard { 16, 30, 99 };

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

	Difficulty diff = ChooseDifficulty();

	Minesweeper ms(diff.cols, diff.rows);
	ms.NewField(diff.numMines);

	sf::Vector2f fieldOrigin(10.f, 10.f);
	SFMLMinefield minefield(ms.GetField(), fieldOrigin);

	sf::Vector2f fieldSize = minefield.GetSizeOfField();
	sf::Uint32 windowStyle = sf::Style::Titlebar | sf::Style::Close;
	sf::RenderWindow app(sf::VideoMode(static_cast<unsigned int>(fieldSize.x+10.f), static_cast<unsigned int>(fieldSize.y+10.f) + 50, 32), "SFML Sweeper", windowStyle);

	sf::Font font;
	font.loadFromFile("data/arial.ttf");

	sf::Text timeString(sf::String(), font, 30);
	timeString.setPosition(10.f, fieldOrigin.y+fieldSize.y);

	sf::Text flagLeftString(sf::String(), font, 30);
	flagLeftString.setPosition(app.getSize().x-10.f-150.f, fieldOrigin.y+fieldSize.y);

	sf::Clock timer;

	while (app.isOpen())
	{
		sf::Event ev;
		while (app.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				app.close();

			if (ms.GetWinState() == WinState::PLAYING)
			{
				if (ev.type == sf::Event::MouseButtonPressed)
				{
					Tile *tile = minefield.GetTileFromMouse(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
					if (tile != nullptr)
					{
						if (ev.mouseButton.button == sf::Mouse::Left)
						{
							ms.OpenTile(tile->x, tile->y);
						}
						else if (ev.mouseButton.button == sf::Mouse::Right)
						{
							ms.FlagTile(tile->x, tile->y);
						}
					}
				}
			}
			else
			{
				if ((ev.type == sf::Event::KeyPressed)&&(ev.key.code == sf::Keyboard::Return))
				{
					app.close();
				}
			}
		}

		minefield.UpdateField();

		if (ms.GetWinState() == WinState::PLAYING)
		{
			std::stringstream t;
			t << "Time: " << static_cast<unsigned int>(timer.getElapsedTime().asSeconds()) << " s";
			timeString.setString(t.str());

			t.str("");
			t.clear();
			t << "Flags: " << ms.GetFlagsLeft();
			flagLeftString.setString(t.str());
		}

		app.clear(sf::Color(0, 0, 0));

		minefield.DrawField(app);

		app.draw(timeString);
		app.draw(flagLeftString);

		if (ms.GetWinState() != WinState::PLAYING)
		{
			sf::Text winString(sf::String(), font, 30);

			if (ms.GetWinState() == WinState::WON)
				winString.setString("You Won!");
			else if (ms.GetWinState() == WinState::LOST)
				winString.setString("You Lost!");

			winString.setPosition((app.getSize().x / 2.f) - (winString.getLocalBounds().width / 2.f), (app.getSize().y / 2.f)-50.f);

			app.draw(winString);
		}

		app.display();
	}

	return 0;
}
