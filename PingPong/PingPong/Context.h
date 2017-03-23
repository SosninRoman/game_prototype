#pragma once
#include <SFML\Graphics.hpp>

struct Context
{
	Context(sf::RenderWindow& window):window(&window){}
	~Context(){}

	sf::RenderWindow* window;
};

