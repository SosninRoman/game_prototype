//
// Created by G750 on 28.11.2017.
//

#include "SBTSpriteSequence.h"
#include "SBTFrame.h"
#include "SBTSpriteAtlas.h"

SBTSpriteSequence::SBTSpriteSequence(SBTSpriteAtlas* texture, std::vector<frameID> frames_basis):
m_atlas(texture), m_frames_basis(std::move(frames_basis) )
{

}

void SBTSpriteSequence::addFramesSet(const std::vector<frameID>& set)
{
    for(auto& frame : set)
    {
        addFrame(frame);
    }
}

const SBTFrame& SBTSpriteSequence::getFrame(int frameNum) const
{
    return m_atlas->getFrame(m_frames_basis[frameNum]);
}

const std::string& SBTSpriteSequence::getMyAtlasFileName() const
{
    return m_atlas->getFileName();
}