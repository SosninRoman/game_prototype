#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "SFML\Graphics.hpp"
#include "ResourceHolder.h"
#include "tinyxml2.h"

using std::vector;
using std::string;
using std::map;

class TileSheet
{
public:
	typedef vector<sf::IntRect> frames_vector;
	TileSheet();
	~TileSheet();

	bool loadFromFile(const std::string& filename, const sf::IntRect& area = sf::IntRect());
	sf::Texture& getTexture();
	const sf::Texture& getTexture() const;
	frames_vector getFrame(string name) const;

	operator sf::Texture&() {return mTexture;}
	string getFileName();
	string getFileName() const;

	sf::Sprite getTile(int tileid);
	
	int getColumns() const {return mColumns;}
	int getTileWidth() const {return mTileWidth;}
	int getTileHeight() const {return mTileHeight;}
private:
	string mName;
	string mFileName;
	sf::Texture mTexture;
	int mColumns;
	int mCount;
	int mTileWidth;
	int mTileHeight;
	map<string, frames_vector> mFrames;
};

