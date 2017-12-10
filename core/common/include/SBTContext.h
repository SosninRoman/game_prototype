#pragma once
#include <SFML\Graphics.hpp>
#include "SBTGraphicResourceHolder.h"
#include "SBTAbstractCommandManager.h"
#include "SBTGameWindow.h"

struct SBTContext
{
	SBTContext(SBTGameWindow* window, FontHolder* fonts, SBTAbstractCommandManager* player, GraphicResourceHolder* grld):
		window(window),
		fonts(fonts),
		player(player),
        graphicResources(grld)
	{
	}
	~SBTContext(){}

	SBTGameWindow*				window;

	FontHolder*					fonts;

	GraphicResourceHolder* 		graphicResources;

	SBTAbstractCommandManager*	player;
};

