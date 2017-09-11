#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "Player.h"
#include "Window.h"

struct Context
{
	//Context(sf::RenderWindow& window, FontHolder& fonts, Player& player, TextureHolder& textures):window(&window), fonts(&fonts), player(&player), textures(&textures){}
	Context(GameWindow& window, FontHolder& fonts, Player& player, TextureHolder& textures):
		window(&window), 
		fonts(&fonts), 
		player(&player), 
		textures(&textures)
	{
	}
	~Context(){}

	GameWindow*			window;

	FontHolder*			fonts;

	TextureHolder*		textures;

	Player*				player;
};

