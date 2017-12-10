//
// Created by G750 on 03.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTGRAPHICRESOURCE_H
#define GAME_PROTOTYPE_SBTGRAPHICRESOURCE_H
#include <memory>
#include <SFML/Graphics.hpp>
#include "SBTAbstractSequence.h"

class SBTAbstractGraphicResource
{
public:
    typedef std::string SequenceID;

    explicit SBTAbstractGraphicResource(const sf::Texture& texture = sf::Texture()):
            m_texture(new sf::Texture(texture) ){}

    virtual bool loadFromFile(const std::string&) = 0;
    virtual bool loadFromFile(const std::string&, const std::string&) = 0;
    virtual const std::string& getFileName() const = 0;
    virtual const SBTSequence& getSequence(const SequenceID& seqID) const = 0;

    const sf::Texture& getTexture()const
    {
        return *m_texture;
    }
public:
    std::unique_ptr<sf::Texture> m_texture;
};
#endif //GAME_PROTOTYPE_SBTGRAPHICRESOURCE_H
