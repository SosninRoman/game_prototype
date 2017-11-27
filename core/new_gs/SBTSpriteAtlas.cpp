//
// Created by G750 on 27.11.2017.
//

#include "SBTSpriteAtlas.h"
#include <tinyxml2.h>
#include <assert.h>
#include <utility>


//Загрузка атдаса с использованием xml файлов с информацией об месторасположении самой текстуры, метаинформацией об
// спрайтах и последовательностях, состоящих из спрайтов
SBTSpriteAtlas::SBTSpriteAtlas(const std::string& atlasMetaFilePath):
m_texture(new sf::Texture() ), m_fileName(atlasMetaFilePath)
{
    loadMetaInfo(atlasMetaFilePath);
}

void SBTSpriteAtlas::loadTexture(const std::string& textureFilePath)
{
    if(m_texture != nullptr)
        m_texture.release();
    else
        m_texture.reset(new sf::Texture() );

    if( !m_texture->loadFromFile(textureFilePath) )
    {
        throw std::runtime_error("Loading texture \"" + textureFilePath  + " failed.");
    }
}

SBTSpriteAtlas::SBTSpriteAtlas(const std::string& atlasMetaFilePath, const std::string& sequencesMetaFilePath):
m_texture(new sf::Texture() ), m_fileName(atlasMetaFilePath)
{
    loadMetaInfo(atlasMetaFilePath);

}

void SBTSpriteAtlas::loadMetaInfo(const std::string& atlasMetaFilePath)
{
    tinyxml2::XMLDocument atlasMetaFile;
    if(atlasMetaFile.LoadFile(atlasMetaFilePath.c_str()) != tinyxml2::XML_SUCCESS)
    {
        throw std::runtime_error("Loading atlas meta file \"" + atlasMetaFilePath + " failed.");
    }

    tinyxml2::XMLElement* atlas = atlasMetaFile.FirstChildElement("TextureAtlas");
    assert(atlas != nullptr);

    std::string texturePath = atlas->Attribute("imagePath");

    if( !m_texture->loadFromFile(texturePath) )
    {
        throw std::runtime_error("Loading texture \"" + texturePath +  "for atlas \"" + atlasMetaFilePath + " failed.");
    }

    tinyxml2::XMLElement* spriteFrame = atlas->FirstChildElement("SubTexture");
    assert(spriteFrame != nullptr);
    //
    while(spriteFrame != nullptr)
    {
        std::string frameName = spriteFrame->Attribute("name");
        int frameX = spriteFrame->IntAttribute("x");
        int frameY = spriteFrame->IntAttribute("y");
        int frameWidth = spriteFrame->IntAttribute("width");
        int frameHeight = spriteFrame->IntAttribute("height");

        SBTFrame newFrame(frameName, frameX, frameY, frameWidth, frameHeight);

        m_framesCollection.insert(std::pair<std::string ,const SBTFrame&>(frameName, newFrame ) );

        spriteFrame = spriteFrame->NextSiblingElement("SubTexture");
    }
}