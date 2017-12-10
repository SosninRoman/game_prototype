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
		auto ins = m_resourceMap.insert(std::make_pair(id, std::unique_ptr<Resource>(res.release() ) ) );
		assert(ins.second);
	}

    void load(ID id, const std::string& filepath)
    {
        std::unique_ptr<Resource> res(new Resource() );
        if(!res->loadFromFile(filepath)) throw std::runtime_error("Fail to load resourse from" + filepath);
        auto ins = m_resourceMap.insert(std::make_pair(id, std::move(res)));
        assert(ins.second);
    }

    void load(ID id, const std::string& filepath1, const std::string& filepath2)
    {
        std::unique_ptr<Resource> res(new Resource() );
        if(!res->loadFromFile(filepath1, filepath2) )
            throw std::runtime_error("Fail to load resourse from files" + filepath1 + " , " + filepath2);
        auto ins = m_resourceMap.insert(std::make_pair(id, std::move(res)));
        assert(ins.second);
    }

    template<class ConvertResource>
    void load(ID id, const std::string& filepath1, const std::string& filepath2)
    {
        std::unique_ptr<ConvertResource> res(new ConvertResource() );
        if(!res->loadFromFile(filepath1, filepath2) )
            throw std::runtime_error("Fail to load resourse from files" + filepath1 + " , " + filepath2);
        auto ins = m_resourceMap.insert(std::make_pair(id, std::unique_ptr<Resource>(res.release() ) ) );
        assert(ins.second);
    }

    void add(ID id, std::unique_ptr<Resource>&& resource)
    {
        if( !m_resourceMap.insert(std::pair<ID, std::unique_ptr<Resource> >(id, std::move(resource))).second )
            throw std::runtime_error("Resource" + resource->getFileName() + " already add into holder");
    }

    template<class ConvertResource>
	void add(ID id, std::unique_ptr<ConvertResource>&& resource)
	{
		if( !m_resourceMap.insert(std::pair<ID, std::unique_ptr<Resource> >(id, std::move(resource))).second )
			throw std::runtime_error("Resource" + resource->getFileName() + " already add into holder");
	}

    Resource& getByID(ID id)
	{
		auto found = m_resourceMap.find(id);
		assert(found != m_resourceMap.end());
		return *found->second;
	}
	
	const Resource& getByID(ID id) const
	{
		auto found = m_resourceMap.find(id);
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
