#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "SFML\Graphics.hpp"
#include "tinyxml2.h"

#include "SBTFrame.h"

using std::vector;
using std::string;
using std::map;

//class SBTTileSequence;
class SBTTileSheet;
template<class Resource, class SequenceState> class SBTTemplateSequence;
typedef SBTTemplateSequence<SBTTileSheet, SBTFrame> SBTTileSequence;

class SBTTileSheet
{
public:
	typedef vector<sf::IntRect> frames_vector;
    typedef std::string SpriteSequenceID;

	SBTTileSheet();
	~SBTTileSheet();

	bool							loadFromFile(const std::string& filename, const sf::IntRect& area = sf::IntRect() );

    bool							loadFromFile(const std::string& filename, const std::string& filename2){return false;}

	sf::Texture&					getTexture();

	const sf::Texture&				getTexture() const;

	//SBTTileSequence					getFrame(string name) const;

	explicit operator sf::Texture&() {return m_texture;}
	
	string							getFileName();
	string							getFileName() const;

	sf::Sprite						getTile(int tileid);
	
	int								getColumns() const {return m_columns;}
	int								getTileWidth() const {return m_tileWidth;}
	int								getTileHeight() const {return m_tileHeight;}
private:
	string							m_name;
	string							m_fileName;

	sf::Texture						m_texture;
	
	int								m_columns;
	int								m_count;
	int								m_tileWidth;
	int								m_tileHeight;
	
	//map<string, frames_vector>		mFrames;
    map<SpriteSequenceID, SBTTileSequence>		m_frames;
};

//#include "SBTTileSequence.h"