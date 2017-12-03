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
	typedef int SpriteAtlasesID;
    typedef int FontID;

	void load(ID id, const std::string& filepath)
	{
		std::unique_ptr<Resourse> res(new Resourse() );
		if(!res->loadFromFile(filepath)) throw std::runtime_error("Fail to load resourse from" + filepath);
		auto ins = mResourseMap.insert(std::make_pair(id, std::move(res)));
		assert(ins.second);
	}

    void load(ID id, const std::string& filepath1, const std::string& filepath2)
    {
        std::unique_ptr<Resourse> res(new Resourse() );
        if(!res->loadFromFile(filepath1, filepath2) )
            throw std::runtime_error("Fail to load resourse from files" + filepath1 + " , " + filepath2);
        auto ins = mResourseMap.insert(std::make_pair(id, std::move(res)));
        assert(ins.second);
    }
	
	Resourse& get(ID id)
	{
		auto found = mResourseMap.find(static_cast<int>(id) );
		assert(found != mResourseMap.end());
		return *found->second;
	}
	
	const Resourse& get(ID id) const
	{
		auto found = mResourseMap.find(static_cast<int>(id) );
		assert(found != mResourseMap.end());
		return *found->second;
	}

	Resourse& get(const std::string& filename)
	{
		for (auto itr = mResourseMap.begin(); itr != mResourseMap.end(); ++itr)
		{
			auto str = itr->second->getFileName();
			if ( str == filename)
				return *(itr->second);
		}
		throw std::runtime_error("Can't find resourse " + filename);
	}

	const Resourse& get(const std::string& filename) const
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
