#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"

struct Context
{
	Context(sf::RenderWindow& window, FontHolder& fonts):window(&window), fonts(&fonts){}
	~Context(){}

	sf::RenderWindow* window;
	FontHolder*       fonts;
};

