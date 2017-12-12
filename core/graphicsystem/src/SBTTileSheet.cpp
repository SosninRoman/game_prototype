#include "SBTTileSheet.h"
#include <assert.h>
#include <sstream>

SBTTileSheet::SBTTileSheet(const std::string& metaFilePath)
{
	loadFromFile(metaFilePath);
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

bool SBTTileSheet::loadFromFile(const std::string& filename)
{
	const size_t slashPos = filename.find_last_of('/');
	string file = filename.substr(slashPos+1, filename.size()-1);
	m_fileName = file;
	//
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
		//Trying to load just texture
		if(m_texture->loadFromFile(filename) )
		{
			m_columns = 1;
			m_size = 1;
			auto sz = m_texture->getSize();
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
	m_size = tileset->IntAttribute("tilecount");

	tinyxml2::XMLElement* image = tileset->FirstChildElement("image");
	assert(image != nullptr);
	const std::string imageFilename = image->Attribute("source");
    const std::string imagePath = JoinPaths(GetParentDirectory(filename), imageFilename);
	bool load_flag = m_texture->loadFromFile(imagePath);
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

                frames.addFrame(tileid);

				frame = frame->NextSiblingElement("frame");
			}
			m_tileSequences.insert(std::pair<SpriteSequenceID, SBTTileSequence>(frame_set_name, frames));
		}
		tile = tile->NextSiblingElement("tile");
	}
	return true;
}

const string& SBTTileSheet::getFileName() const
{
	return m_fileName;
}

sf::Sprite SBTTileSheet::getTile(int tileid) const
{
	int column = tileid % m_columns;
	int row = tileid / m_columns;
	assert((column+1) * (row+1) <= tileid+1); 
	sf::Sprite result(*m_texture);
	sf::IntRect frame(column * m_tileWidth, row * m_tileHeight, m_tileWidth, m_tileHeight);
	result.setTextureRect(frame);
	return result;
}

void SBTTileSheet::loadTexture(const std::string& textureFilePath)
{
		m_texture.reset(new sf::Texture() );

	if( !m_texture->loadFromFile(textureFilePath) )
	{
		throw std::runtime_error("Loading texture \"" + textureFilePath  + " failed.");
	}
	m_fileName = textureFilePath;
}

SBTTileSequence& SBTTileSheet::addSequence(const SpriteSequenceID& seqID, std::vector<int> seqBasis)
{
    for(int frame : seqBasis)
    {
        if(frame >= m_size ) {
            std::stringstream s;
            s << "frame " << frame << " is absent in tilesheet \"" << m_fileName;
            throw std::runtime_error(s.str() );
        }
    }
    auto res = m_tileSequences.insert(make_pair(seqID, SBTTileSequence(this, seqBasis) ) );
    if(!res.second)
        throw std::runtime_error("sequence " + seqID +" is already exist in atlas \"" + m_fileName);
}

SBTFrame SBTTileSheet::getFrame(int frameNum)
{
    if(frameNum >= m_size)
    {
        std::stringstream s;
        s << "frame " << frameNum << " is absent in tilesheet \"" << m_fileName;
        throw std::runtime_error(s.str() );
    }
    int column = frameNum % m_columns;
    int row = frameNum / m_columns;
    sf::IntRect frame = sf::IntRect(column * m_tileWidth, row * m_tileHeight, m_tileWidth, m_tileHeight);
    return frame;
}

void SBTTileSheet::addTileToSequence(const SpriteSequenceID& seqID, int tileNum)
{
    if(tileNum >= m_size)
    {
        std::stringstream s;
        s << "frame " << tileNum << " is absent in tilesheet \"" << m_fileName;
        throw std::runtime_error(s.str() );
    }

    if(m_tileSequences.find(seqID) == m_tileSequences.end() )
    {
        std::stringstream s;
        s << "tile sequence " << seqID << " is absent in tilesheet \"" << m_fileName;
        throw std::runtime_error(s.str() );
    }

    m_tileSequences[seqID].addFrame(tileNum);
}

const SBTSequence& SBTTileSheet::getSequence(const SequenceID& seqID) const
{
    auto seq_id = m_tileSequences.find(seqID);
    if(seq_id != m_tileSequences.end() )
        return seq_id->second;
    else
        throw std::runtime_error("Can't find sequence" + seqID +" in atlas \"" + m_fileName);
}