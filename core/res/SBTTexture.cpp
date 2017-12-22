//
// Created by G750 on 10.12.2017.
//

#include "SBTTexture.h"

SBTTexture::SBTTexture(const std::string &textureFilePath):
m_fileName(textureFilePath)
{
    if( !m_texture->loadFromFile(textureFilePath) )
    {
        throw std::runtime_error("Loading texture \"" + textureFilePath +  " failed.");
    }
}

bool SBTTexture::loadFromFile(const std::string &textureFilePath)
{
    if(m_texture != nullptr)
    {
        m_texture.reset(new sf::Texture);
    }

    m_fileName = textureFilePath;

    if( !m_texture->loadFromFile(textureFilePath) )
    {
        throw std::runtime_error("Loading texture \"" + textureFilePath +  " failed.");
    }

    return true;
}

bool SBTTexture::loadFromFile(const std::string &atlasMetaFilePath, const std::string &sequencesMetaFilePath)
{
    return false;
}

const std::string& SBTTexture::getFileName() const
{
    return m_fileName;
}

const SBTSequence& SBTTexture::getSequence(const FrameSequenceID& seqID) const
{

}