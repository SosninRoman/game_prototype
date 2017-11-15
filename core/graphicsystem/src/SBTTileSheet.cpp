#include "SBTTileSheet.h"
#include <assert.h>

SBTTileSheet::SBTTileSheet()
{
}


SBTTileSheet::~SBTTileSheet()
{
}

std::string GetParentDirectory(const std::string &filepath)
{
    const size_t slashPos = filepath.find_last_of('/');
    std::string parentDir;
    if (slashPos != std::string::npos)
    {
        parentDir = filepath.substr(0, slashPos);
    }
    return parentDir;
}

std::string JoinPaths(const std::string &path, const std::string &subpath)
{
    if (path.empty())
    {
        return subpath;
    }
    if (subpath.empty())
    {
        return path;
    }

	std::string result = path;

    return result + '\\' + subpath;
}

bool SBTTileSheet::loadFromFile(const std::string& filename, const sf::IntRect& area)
{
	const size_t slashPos = filename.find_last_of('/');
	string file = filename.substr(slashPos+1, filename.size()-1);
	mFileName = file;
	//
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
		//Trying to load just texture
		if(mTexture.loadFromFile(filename))
		{
			mColumns = 1;
			mCount = 1;
			auto sz = mTexture.getSize();
			mTileHeight = sz.y;
			mTileWidth = sz.x;
			return true;
		}
		else
			throw std::runtime_error("Loading TileSheet \"" + filename + " failed."); 
    }

	tinyxml2::XMLElement* tileset = doc.FirstChildElement("tileset");
	assert(tileset != nullptr);
	mName = tileset->Attribute("name");
	mTileWidth = tileset->IntAttribute("tilewidth");
	mTileHeight =  tileset->IntAttribute("tileheight");
	mColumns = tileset->IntAttribute("columns");
	mCount = tileset->IntAttribute("tilecount");

	tinyxml2::XMLElement* image = tileset->FirstChildElement("image");
	assert(image != nullptr);
	const std::string imageFilename = image->Attribute("source");
    const std::string imagePath = JoinPaths(GetParentDirectory(filename), imageFilename);
	bool load_flag = mTexture.loadFromFile(imagePath);
	assert(load_flag);

	tinyxml2::XMLElement* tile = doc.FirstChildElement("tileset")->FirstChildElement("tile");
	while(tile != nullptr)
	{
		tinyxml2::XMLElement* obj = tile->FirstChildElement("objectgroup");
		assert(obj != nullptr);
		std::string frame_set_name = obj->Attribute("name");

		frames_vector frames;
		tinyxml2::XMLElement* animation = tile->FirstChildElement("animation");
		if (animation != nullptr)
		{
			tinyxml2::XMLElement* frame = animation->FirstChildElement("frame");
			while(frame != nullptr)
			{
				int tileid = frame->IntAttribute("tileid");
				int column = tileid % mColumns;
				int row = tileid / mColumns;
				double duration = frame->FloatAttribute("duration");

				sf::IntRect rect(column * mTileWidth, row * mTileHeight, mTileWidth, mTileHeight);
				frames.push_back(rect);

				frame = frame->NextSiblingElement("frame");
			}
			mFrames.insert(std::pair<string, frames_vector>(frame_set_name, frames));
		}
		tile = tile->NextSiblingElement("tile");
	}
	return true;
}

sf::Texture& SBTTileSheet::getTexture()
{
	return mTexture;
}

const sf::Texture& SBTTileSheet::getTexture() const
{
	return mTexture;
}

SBTTileSheet::frames_vector SBTTileSheet::getFrame(string name) const
{
	auto itr = mFrames.find(name);
	assert(itr != mFrames.end());
	return itr->second;
}

string SBTTileSheet::getFileName()
{
	return mFileName;
}

string SBTTileSheet::getFileName() const
{
	return mFileName;
}

sf::Sprite SBTTileSheet::getTile(int tileid)
{
	int column = tileid % mColumns;
	int row = tileid / mColumns;
	assert((column+1) * (row+1) <= tileid+1); 
	sf::Sprite result(mTexture);
	sf::IntRect frame(column * mTileWidth, row * mTileHeight, mTileWidth, mTileHeight);
	result.setTextureRect(frame);
	return result;
}