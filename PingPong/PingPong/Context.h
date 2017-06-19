#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "Player.h"

struct Context
{
	Context(sf::RenderWindow& window, FontHolder& fonts, Player& player, TextureHolder& textures):window(&window), fonts(&fonts), player(&player), textures(&textures){}
	~Context(){}

	sf::RenderWindow* window;
	FontHolder*       fonts;
	TextureHolder*    textures;
	Player*           player;
};

