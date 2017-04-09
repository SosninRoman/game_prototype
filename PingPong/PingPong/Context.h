#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "Player.h"

struct Context
{
	Context(sf::RenderWindow& window, FontHolder& fonts, Player& player):window(&window), fonts(&fonts), player(&player){}
	~Context(){}

	sf::RenderWindow* window;
	FontHolder*       fonts;
	Player*           player;
};

