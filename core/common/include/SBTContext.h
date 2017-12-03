#pragma once
#include <SFML\Graphics.hpp>
#include "SBTTextureHolder.h"
#include "SBTAtlasHolder.h"
#include "SBTTileSheetHolder.h"
#include "SBTAbstractCommandManager.h"
#include "SBTGameWindow.h"

struct SBTContext
{
	SBTContext(SBTGameWindow* window, FontHolder* fonts, SBTAbstractCommandManager* player, TextureHolder* textures,
    AtlasHolder* atl, TileSheetHolder* tst):
		window(window),
		fonts(fonts),
		player(player),
		textures(textures),
        atlases(atl),
        tilesets(tst)
	{
	}
	~SBTContext(){}

	SBTGameWindow*			window;

	FontHolder*			fonts;

	TextureHolder*		textures;

	AtlasHolder*        atlases;

    TileSheetHolder*    tilesets;

	SBTAbstractCommandManager*				player;
};

