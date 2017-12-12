#pragma once
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <SFML\Graphics.hpp>
#include <utility>

template<class ID, class Resource>
class SBTResourceHolder
{
public:
	typedef int SpriteAtlasesID;
    typedef int FontID;

	template<class ConvertResource>
	void load(ID id, const std::string& filepath)
	{
        std::unique_ptr<ConvertResource> res(new ConvertResource() );
		if(!res->loadFromFile(filepath)) throw std::runtime_error("Fail to load resourse from" + filepath);
		const auto& ins = m_resourceMap.insert(std::move(std::make_pair(id, std::move(std::unique_ptr<Resource>(res.release() ) ) ) ) );
		assert(ins.second);
	}

    template<class ConvertResource>
    void load(ID id, const std::string& filepath1, const std::string& filepath2)
    {
        std::unique_ptr<ConvertResource> res(new ConvertResource() );
        if(!res->loadFromFile(filepath1, filepath2) )
            throw std::runtime_error("Fail to load resourse from files" + filepath1 + " , " + filepath2);
        const auto& ins = m_resourceMap.insert(std::move(std::make_pair(id, std::move(std::unique_ptr<Resource>(res.release() ) ) ) ) );
        assert(ins.second);
    }

    template<class ConvertResource>
    ConvertResource* createResource(ID id)
    {
        if(m_resourceMap.find(id) != m_resourceMap.end() )
            throw std::runtime_error("Resource" + id + " already exist in holder");
        std::unique_ptr<Resource> new_resource( new ConvertResource);
        const auto& result = m_resourceMap.insert(std::move(std::make_pair(id, std::move(new_resource) ) ) );
        return dynamic_cast<ConvertResource*>((*result.first).second.get());
    }

    Resource& getByID(ID id)
	{
		const auto& found = m_resourceMap.find(id);
		assert(found != m_resourceMap.end());
		return *found->second;
	}
	
	const Resource& getByID(ID id) const
	{
		const auto& found = m_resourceMap.find(id);
		assert(found != m_resourceMap.end());
		return *found->second;
	}

    Resource& getByFilename(const std::string& filename)
	{
		for (auto itr = m_resourceMap.begin(); itr != m_resourceMap.end(); ++itr)
		{
			auto str = itr->second->getFileName();
			if ( str == filename)
				return *(itr->second);
		}
		throw std::runtime_error("Can't find resourse " + filename);
	}

	const Resource& getByFilename(const std::string& filename) const
	{
		for (auto itr = m_resourceMap.begin(); itr != m_resourceMap.end(); ++itr)
		{
			if (itr->second->getFileName() == filename)
				return *(itr->second);
		}
		throw std::runtime_error("Can't find resourse " + filename);
	}
private:
	std::map<ID, std::unique_ptr<Resource> > m_resourceMap;
};

typedef SBTResourceHolder<std::string, sf::Font> FontHolder;
