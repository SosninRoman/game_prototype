#pragma once
#include <map>
#include <string>
#include <memory>
#include <assert.h>
#include <SFML\Graphics.hpp>

enum FontID{MainMenuFont};

template<class ID, class Resourse>
class ResourceHolder
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
private:
	std::map<ID, std::unique_ptr<Resourse> > mResourseMap;
};

typedef ResourceHolder<FontID,sf::Font> FontHolder;