//
// Created by G750 on 28.11.2017.
//

#include "SBTSpriteSequence.h"
#include "SBTFrame.h"
#include "SBTSpriteAtlas.h"
#include "SBTSequenceState.h"

SBTSpriteSequence::SBTSpriteSequence(SBTSpriteAtlas* texture, std::vector<SBTSequenceState> frames_basis):
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

const SBTFrame& SBTSpriteSequence::getSequenceStateFrame(int frameNum) const
{
    return m_atlas->getFrame(m_frames_basis[frameNum].m_frameID);
}

int SBTSpriteSequence::getSequenceStateAngle(int frameNum) const
{
    return m_frames_basis[frameNum].m_angle;
}

const std::string& SBTSpriteSequence::getMyAtlasFileName() const
{
    return m_atlas->getFileName();
}

void SBTSpriteSequence::addFrame(const frameID& frame, int angle)
{
    m_frames_basis.emplace_back(SBTSequenceState(frame, angle) );
}

void SBTSpriteSequence::addFrame(const SBTSequenceState& frame)
{
    m_frames_basis.emplace_back(frame);
}

const SBTSequenceState& SBTSpriteSequence::getSequenceState(int frameNum) const
{
    return m_frames_basis[frameNum];
}