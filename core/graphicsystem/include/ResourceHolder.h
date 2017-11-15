#pragma once
#include <map>
#include <string>
#include <memory>
#include <assert.h>
#include <SFML\Graphics.hpp>
#include "SBTTileSheet.h"

//class SBTTileSheet;

template<class ID, class Resourse>
class SBTResourceHolder
{
public:
	void load(ID id, const std::string& filename)
	{
		std::unique_ptr<Resourse> res(new Resourse());
		if(!res->loadFromFile(filename)) throw std::runtime_error("Fail to load resourse from" + filename);
		auto ins = mResourseMap.insert(std::make_pair(id, std::move(res)));
		assert(ins.second);
	}
	
	Resourse& get(ID id)
	{
		auto found = mResourseMap.find(id);
		assert(found != mResourseMap.end());
		return *found->second;
	}
	
	const Resourse& get(ID id) const
	{
		auto found = mResourseMap.find(id);
		assert(found != mResourseMap.end());
		return *found->second;
	}

	Resourse& get(std::string filename)
	{
		for (auto itr = mResourseMap.begin(); itr != mResourseMap.end(); ++itr)
		{
			auto str = itr->second->getFileName();
			if ( str == filename)
				return *(itr->second);
		}
		throw std::runtime_error("Can't find resourse " + filename);
	}

	const Resourse& get(std::string filename) const
	{
		for (auto itr = mResourseMap.begin(); itr != mResourseMap.end(); ++itr)
		{
			if (itr->second->getFileName() == filename)
				return *(itr->second);
		}
		throw std::runtime_error("Can't find resourse " + filename);
	}
private:
	std::map<ID, std::unique_ptr<Resourse> > mResourseMap;
};

typedef SBTResourceHolder<int, sf::Font> FontHolder;
typedef SBTResourceHolder<int, SBTTileSheet> TextureHolder;