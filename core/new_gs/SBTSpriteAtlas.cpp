//
// Created by G750 on 27.11.2017.
//

#include "SBTSpriteAtlas.h"
//#include "SBTFrame.h"
//#include "SBTSpriteSequence.h"
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

    loadSequencesFromMetaFile(sequencesMetaFilePath);
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

void SBTSpriteAtlas::loadSequencesFromMetaFile(const std::string& sequencesMetaFilePath)
{
    tinyxml2::XMLDocument sequencesMetaFile;
    if(sequencesMetaFile.LoadFile(sequencesMetaFilePath.c_str()) != tinyxml2::XML_SUCCESS)
    {
        throw std::runtime_error("Loading sequences meta file \"" + sequencesMetaFilePath + " failed.");
    }

    tinyxml2::XMLElement* sequences = sequencesMetaFile.FirstChildElement("TextureAtlas");
    assert(sequences != nullptr);

    tinyxml2::XMLElement* framesSequence = sequences->FirstChildElement("sequence");
    assert(framesSequence != nullptr);
    //
    while(framesSequence != nullptr)
    {
        std::string seqName = framesSequence->Attribute("name");

        tinyxml2::XMLElement* frame = framesSequence->FirstChildElement("frame");
        SBTSpriteSequence seq(this);
        while(frame != nullptr)
        {
            std::string frameName = frame->Attribute("frameid");
            auto itr = m_framesCollection.find(frameName);
            if(itr != m_framesCollection.end() )
                seq.addFrame(frameName);
            else
                throw std::runtime_error("Can't find frame" + frameName +" in sequences meta file \"" + sequencesMetaFilePath);
            frame = frame->NextSiblingElement("frame");
        }
        m_spriteSequences.insert(std::pair<const std::string, SBTSpriteSequence&>(std::move(seqName), seq) );

        framesSequence = framesSequence->NextSiblingElement("sequence");
    }
}

void SBTSpriteAtlas::loadFromFile(const std::string &sequencesMetaFilePath)
{
    loadSequencesFromMetaFile(sequencesMetaFilePath);
}

const SBTFrame& SBTSpriteAtlas::getFrame(const FrameID& frmID) const
{
    auto frame_itr = m_framesCollection.find(frmID);
    if(frame_itr != m_framesCollection.end() )
        return frame_itr->second;
    else
        throw std::runtime_error("Can't find frame" + frmID +" in atlas \"" + m_fileName);
}

const SBTSpriteSequence& SBTSpriteAtlas::getSequence(const SpriteSequenceID& seqID) const
{
    auto seq_id = m_spriteSequences.find(seqID);
    if(seq_id != m_spriteSequences.end() )
        return seq_id->second;
    else
        throw std::runtime_error("Can't find sequence" + seqID +" in atlas \"" + m_fileName);
}

const std::string& SBTSpriteAtlas::getFileName() const
{
    return m_fileName;
}

void  SBTSpriteAtlas::addSequencesFromFile(const std::string& SpriteSequencesMetaFilePath )
{
    clearSequences();

    loadSequencesFromMetaFile(SpriteSequencesMetaFilePath);
}

void SBTSpriteAtlas::addFrame(SBTFrame& frame)
{
    auto res = m_framesCollection.insert(std::pair<const std::string, SBTFrame&>(frame.name(), frame) );
    if(!res.second)
        throw std::runtime_error("frame " + frame.name() +" is already exist in atlas \"" + m_fileName);
}

void SBTSpriteAtlas::clearAll()
{
    m_texture.release();
    m_framesCollection.clear();
    m_fileName.clear();
    m_spriteSequences.clear();
}

void SBTSpriteAtlas::clearFrames()
{
    m_framesCollection.clear();
    m_spriteSequences.clear();
}

void SBTSpriteAtlas::clearSequences()
{
    m_spriteSequences.clear();
}

void SBTSpriteAtlas::addSequence(const SpriteSequenceID& seqID, const std::vector<FrameID>& seqBasis)
{
    for(const FrameID& frame : seqBasis)
    {
        if(m_framesCollection.find(frame) == m_framesCollection.end() )
            throw std::runtime_error("frame " + frame +" is absent in atlas \"" + m_fileName);
    }
    auto res = m_spriteSequences.insert(make_pair(seqID, SBTSpriteSequence(this, seqBasis) ) );
    if(!res.second)
        throw std::runtime_error("sequence " + seqID +" is already exist in atlas \"" + m_fileName);
}

void SBTSpriteAtlas::addFrameToSequence(const SpriteSequenceID& seqID, const FrameID& frID)
{
    if(m_spriteSequences.find(seqID) != m_spriteSequences.end() )
    {
        if(m_framesCollection.find(frID) != m_framesCollection.end() ) {
            m_spriteSequences[seqID].addFrame(frID);
        }
        else
            throw std::runtime_error("frame " + frID +" is absent in atlas \"" + m_fileName);
    }
    else
        throw std::runtime_error("sequence " + seqID +" is absent in atlas \"" + m_fileName);
}