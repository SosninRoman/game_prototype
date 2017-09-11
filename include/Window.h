#pragma once
#include <SFML\Graphics.hpp>

class GameWindow: public sf::RenderWindow
{
public:
	GameWindow(int sz_x, int sz_y, const sf::String& title, sf::Uint32 style = 7U, const sf::ContextSettings& settings = sf::ContextSettings() );
	~GameWindow();

	sf::Vector2u getResolution() const
	{
		return resolution;
	}

private:
	sf::Vector2u resolution;
};

