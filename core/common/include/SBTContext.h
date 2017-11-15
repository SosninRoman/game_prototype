#pragma once
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "SBTAbstractCommandManager.h"
#include "SBTGameWindow.h"

struct SBTContext
{
	SBTContext(SBTGameWindow* window, FontHolder* fonts, SBTAbstractCommandManager* player, TextureHolder* textures):
		window(window),
		fonts(fonts),
		player(player),
		textures(textures)
	{
	}
	~SBTContext(){}

	SBTGameWindow*			window;

	FontHolder*			fonts;

	TextureHolder*		textures;

	SBTAbstractCommandManager*				player;
};

