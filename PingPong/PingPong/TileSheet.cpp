#include "TileSheet.h"


TileSheet::TileSheet()
{
}


TileSheet::~TileSheet()
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

    return path + '\\' + subpath;
}

bool TileSheet::loadFromFile(const std::string& filename, const sf::IntRect& area)
{
	mFileName = filename;
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
		//Trying to load just texture
		if(mTexture.loadFromFile(filename))
			return true;
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

sf::Texture& TileSheet::getTexture()
{
	return mTexture;
}

TileSheet::frames_vector TileSheet::getFrame(string name) const
{
	auto itr = mFrames.find(name);
	assert(itr != mFrames.end());
	return itr->second;
}
