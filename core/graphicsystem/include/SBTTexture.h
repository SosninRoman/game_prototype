//
// Created by G750 on 10.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTTEXTURE_H
#define GAME_PROTOTYPE_SBTTEXTURE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>

#include "SBTAbstractGraphicResource.h"

class SBTTexture;
class SBTFrameSequence;

class SBTTexture: public SBTAbstractGraphicResource {
public:
    typedef std::string FrameID;
    typedef std::string FrameSequenceID;

    SBTTexture() = default;

    SBTTexture(const sf::Texture &texture, std::string textureFilePath) :
            SBTAbstractGraphicResource(texture), m_fileName(std::move(textureFilePath) ) {}

    explicit SBTTexture(const std::string& textureFilePath);

    bool loadFromFile(const std::string& textureFilePath) override;

    bool loadFromFile(const std::string& atlasMetaFilePath, const std::string &sequencesMetaFilePath) override;

    const SBTSequence& getSequence(const FrameSequenceID& seqID) const override;

    const std::string &getFileName() const override;
private:
    std::string m_fileName;

    std::map<FrameSequenceID, SBTFrameSequence>		m_frameSequences; //Наборы последовательностей кадров
};


class SBTFrameSequence: public SBTSequence
{
public:
    typedef std::string frameID;

    SBTFrameSequence():m_resource(nullptr){}

    explicit SBTFrameSequence(SBTTexture* resource,
                                 std::vector<SBTFrame> frames_basis = std::vector<SBTFrame>() ):
            m_resource(resource), m_framesBasis(frames_basis){}

    void addFrame(const SBTFrame& frame)
    {
        m_framesBasis.emplace_back(frame);
    }

    void addFramesSet(const std::vector<SBTFrame>& set)
    {
        for(auto& frame : set)
        {
            addFrame(frame);
        }
    }

    void clearBasis(sf::Texture* texture)
    {
        m_framesBasis.clear();
    }

    const std::vector<SBTFrame>& getBasis()
    {
        return m_framesBasis;
    }

    SBTFrame getSequenceStateFrame(int frameNum) const override
    {
        return m_framesBasis[frameNum];
    }

    int getSequenceStateAngle(int frameNum) const override
    {
        return 0;
    }

    const std::string& getMyResourceFileName() const override
    {
        return m_resource->getFileName();
    }

    int size() const override
    {
        return m_framesBasis.size();
    }
private:
    std::vector<SBTFrame> m_framesBasis;

    SBTTexture* m_resource;
};
#endif //GAME_PROTOTYPE_SBTTEXTURE_H
