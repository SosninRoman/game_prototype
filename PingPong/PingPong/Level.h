#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "ResourceHolder.h"

using std::vector;
using std::string;
using std::map;

struct LevelObject
{
	string				  name;
	string				  type;
	sf::Sprite			  sprite;
	//sf::Vector2i		  position;
	sf::IntRect           rect;
	map<string, string>	  properties;
	//
	bool without_sprite;
	int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);
};

class Level
{
public:
	typedef map<int, const TileSheet&>::iterator sheet_iterator;
	struct Layer
	{
		Layer(int sz = 0):tiles(sz){}
		int opacity;
		vector<sf::Sprite> tiles;
	};
	
	Level();
	~Level();
	bool loadFromFile(const string& filename, TextureHolder& textures);
	void draw(sf::RenderTarget& target);
	LevelObject* getObject(const string& name);
	vector<LevelObject>& getAllObjects();
private:
	sf::IntRect getFrame(int tileid, const TileSheet& map_sheet);
	int                        mWidth;
	int                        mHeight;
	int                        mTileWidth;
	int                        mTileHeight;
	int						   mFirstTileId;
	vector<Layer>			   mLayers;
	vector<LevelObject>		   mObjects;
	map<int, const TileSheet&> mSheets;
};

