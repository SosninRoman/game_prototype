#include "SBTTileSheet.h"
#include <assert.h>
//#include "SBTTileSequence.h"
#include "SBTTileSequence.h"

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
	m_fileName = file;
	//
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
		//Trying to load just texture
		if(m_texture.loadFromFile(filename) )
		{
			m_columns = 1;
			m_count = 1;
			auto sz = m_texture.getSize();
			m_tileHeight = sz.y;
			m_tileWidth = sz.x;
			return true;
		}
		else
			throw std::runtime_error("Loading TileSheet \"" + filename + " failed."); 
    }

	tinyxml2::XMLElement* tileset = doc.FirstChildElement("tileset");
	assert(tileset != nullptr);
	m_name = tileset->Attribute("name");
	m_tileWidth = tileset->IntAttribute("tilewidth");
	m_tileHeight =  tileset->IntAttribute("tileheight");
	m_columns = tileset->IntAttribute("columns");
	m_count = tileset->IntAttribute("tilecount");

	tinyxml2::XMLElement* image = tileset->FirstChildElement("image");
	assert(image != nullptr);
	const std::string imageFilename = image->Attribute("source");
    const std::string imagePath = JoinPaths(GetParentDirectory(filename), imageFilename);
	bool load_flag = m_texture.loadFromFile(imagePath);
	assert(load_flag);

	tinyxml2::XMLElement* tile = doc.FirstChildElement("tileset")->FirstChildElement("tile");
	while(tile != nullptr)
	{
		tinyxml2::XMLElement* obj = tile->FirstChildElement("objectgroup");
		assert(obj != nullptr);
		std::string frame_set_name = obj->Attribute("name");

		SBTTileSequence frames;
		tinyxml2::XMLElement* animation = tile->FirstChildElement("animation");
		if (animation != nullptr)
		{
			tinyxml2::XMLElement* frame = animation->FirstChildElement("frame");
			while(frame != nullptr)
			{
				int tileid = frame->IntAttribute("tileid");
				int column = tileid % m_columns;
				int row = tileid / m_columns;
				double duration = frame->FloatAttribute("duration");

				sf::IntRect rect(column * m_tileWidth, row * m_tileHeight, m_tileWidth, m_tileHeight);
				//frames.push_back(rect);
				frames.addFrame(SBTFrame(rect) );

				frame = frame->NextSiblingElement("frame");
			}
			m_frames.insert(std::pair<SpriteSequenceID, SBTTileSequence>(frame_set_name, frames));
		}
		tile = tile->NextSiblingElement("tile");
	}
	return true;
}

sf::Texture& SBTTileSheet::getTexture()
{
	return m_texture;
}

const sf::Texture& SBTTileSheet::getTexture() const
{
	return m_texture;
}

//SBTTileSequence SBTTileSheet::getFrame(string name) const
//{
//	auto itr = m_frames.find(name);
//	assert(itr != m_frames.end());
//	return itr->second;
//}

string SBTTileSheet::getFileName()
{
	return m_fileName;
}

string SBTTileSheet::getFileName() const
{
	return m_fileName;
}

sf::Sprite SBTTileSheet::getTile(int tileid)
{
	int column = tileid % m_columns;
	int row = tileid / m_columns;
	assert((column+1) * (row+1) <= tileid+1); 
	sf::Sprite result(m_texture);
	sf::IntRect frame(column * m_tileWidth, row * m_tileHeight, m_tileWidth, m_tileHeight);
	result.setTextureRect(frame);
	return result;
}