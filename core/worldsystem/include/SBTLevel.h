#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "SBTGraphicResourceHolder.h"

class SBTTileSheet;

using std::vector;
using std::string;
using std::map;

struct LevelObject
{
	string				  name;
	string				  type;
	sf::Sprite			  sprite;
	sf::IntRect           rect;
	map<string, string>	  properties;
	//
	bool without_sprite;
	int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);
};

class SBTLevel
{
public:
	typedef map<int, const SBTTileSheet&>::iterator sheet_iterator;
	struct Layer
	{
		Layer(int sz = 0):tiles(sz){}
		int opacity;
		vector<sf::Sprite> tiles;
	};

    SBTLevel() = default;

    ~SBTLevel() = default;

	//bool loadFromFile(const string& filename, TileSheetHolder& textures);
	bool loadFromFile(const string& filename, GraphicResourceHolder& textures);

	void draw(sf::RenderTarget& target);

	LevelObject* getObject(const string& name);

	vector<LevelObject>& getAllObjects();
private:
	sf::IntRect getFrame(int tileid, const SBTTileSheet& map_sheet);

    int                        mWidth;

    int                        mHeight;

    int                        mTileWidth;

    int                        mTileHeight;

    int						   mFirstTileId;

    vector<Layer>			   mLayers;

    vector<LevelObject>		   mObjects;

    map<int, const SBTTileSheet&> mSheets;
};

