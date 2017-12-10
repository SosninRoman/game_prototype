#include "SBTLevel.h"
#include "SBTTileSheet.h"

int LevelObject::GetPropertyInt(string name)
{
    int i = atoi(properties[name].c_str());
    return i;
}

float LevelObject::GetPropertyFloat(string name)
{
    float f = static_cast<float>( atof(properties[name].c_str()) );
    return f;
}

string LevelObject::GetPropertyString(string name)
{
    return properties[name];
}

bool SBTLevel::loadFromFile(const string& filename, GraphicResourceHolder& textures)
{
	tinyxml2::XMLDocument doc;
	if(doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
		throw std::runtime_error("Loading map \"" + filename + " failed."); 
    }
	
	tinyxml2::XMLElement* map = doc.FirstChildElement("map");
	assert(map != nullptr);
	mWidth = map->IntAttribute("width");
	mHeight = map->IntAttribute("height");
	mTileWidth = map->IntAttribute("tilewidth");
	mTileHeight = map->IntAttribute("tileheight");

	tinyxml2::XMLElement* tileset = map->FirstChildElement("tileset");
	assert(tileset != nullptr);
	//
	mFirstTileId = tileset->IntAttribute("firstgid");
	while(tileset != nullptr)
	{
		string source = tileset->Attribute("source");
        SBTTileSheet& map_sheet = dynamic_cast<SBTTileSheet&>(textures.getByFilename(source) );
		//SBTTileSheet& map_sheet = textures.get(source);
		int first_map_id = tileset->IntAttribute("firstgid");

		mSheets.insert(std::pair<int,const SBTTileSheet&>(first_map_id, map_sheet));

		tileset = tileset->NextSiblingElement("tileset");
	}
	//

	tinyxml2::XMLElement* layer = map->FirstChildElement("layer");
	while(layer != nullptr)
	{			
		tinyxml2::XMLElement* tile = layer->FirstChildElement("data")->FirstChildElement("tile");
		Layer new_layer;
		
		const char* opacity = layer->Attribute("opacity");
		if(opacity == nullptr)
			new_layer.opacity = 255;
		else
		{
			float f = static_cast<float>( std::atof(opacity) );
			new_layer.opacity = static_cast<int>(255 * f);
		}

		new_layer.tiles.reserve(static_cast<int>(mWidth * mHeight));
		int tilecount = 0;
		while(tile != nullptr)
		{
			int tileid = tile->IntAttribute("gid");			
			if( tileid >= mFirstTileId)
			{
				sheet_iterator itr = --(mSheets.upper_bound(tileid));
				const SBTTileSheet& map_sheet = itr->second;
				//
				sf::IntRect frame = getFrame(tileid - itr->first, map_sheet);
				//
				sf::Sprite sprite(map_sheet.getTexture());
				sprite.setTextureRect(frame);
				//
				int column = tilecount % mWidth;
				int row    = tilecount / mWidth;
				sprite.setPosition(static_cast<float>(column) * frame.width, static_cast<float>(row) * frame.height);
				//
				new_layer.tiles.push_back(sprite);
			}
			tile = tile->NextSiblingElement("tile");
			++tilecount;
		}
		mLayers.push_back(new_layer);
		layer = layer->NextSiblingElement("layer");
	}

	tinyxml2::XMLElement* objectgroup = map->FirstChildElement("objectgroup");
	while(objectgroup != nullptr)
	{
		tinyxml2::XMLElement* object = objectgroup->FirstChildElement("object");
		while(object != nullptr)
		{
			LevelObject new_object;
			const char* name = object->Attribute("name");
			new_object.name = name != nullptr? name:"";
			const char* type = object->Attribute("type"); 
			if(type == nullptr)
				throw std::runtime_error("There is object without type in " + filename + " map");
			new_object.type = type;
			int tileid = object->IntAttribute("gid");
			if(tileid >= mFirstTileId)
			{
				new_object.without_sprite = false;
				//
				sheet_iterator itr = --(mSheets.upper_bound(tileid));
				const SBTTileSheet& map_sheet = itr->second;
//				//
//				new_object.sprite.setTexture(map_sheet.getTexture());
//				sf::IntRect frame = getFrame(tileid - itr->first, map_sheet);
//				new_object.sprite.setTextureRect(frame);
                //
                new_object.sprite = map_sheet.getTile(tileid - itr->first);
			}
			else
			{
				new_object.without_sprite = true;
			}
			new_object.rect.left   = object->IntAttribute("x");
			new_object.rect.top    = object->IntAttribute("y");
			new_object.rect.width  = object->IntAttribute("width");
			new_object.rect.height = object->IntAttribute("height");

			tinyxml2::XMLElement* properties = object->FirstChildElement("properties");
			if(properties != nullptr)
			{
				tinyxml2::XMLElement* o_property = properties->FirstChildElement("property");
				while(o_property != nullptr)
				{
					new_object.properties.insert( std::pair<string,string>(o_property->Attribute("name"), o_property->Attribute("value")) );
					o_property = o_property->NextSiblingElement("property");
				}
			}

			mObjects.push_back(new_object);
			object = object->NextSiblingElement("object");
		}
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}
	return true;
}

sf::IntRect SBTLevel::getFrame(int tileid, const SBTTileSheet& map_sheet)
{
	int map_colums      = map_sheet.getColumns();
	int map_tile_width  = map_sheet.getTileWidth();
	int map_tile_height = map_sheet.getTileHeight();

	int column = tileid % map_colums;
	int row = tileid / map_colums;
	sf::IntRect frame = sf::IntRect(column * map_tile_width, row * map_tile_height, map_tile_width, map_tile_height);
	return frame;
}

void SBTLevel::draw(sf::RenderTarget& target)
{
	for(auto& layer : mLayers)
	{
		for(auto& sprite : layer.tiles)
			target.draw(sprite);
	}
}

LevelObject* SBTLevel::getObject(const string& name)
{
	for(auto& obj : mObjects)
	{
		if (obj.name == name)
			return &obj;
	}
	return nullptr;
}

vector<LevelObject>& SBTLevel::getAllObjects()
{
	return mObjects;
}