//
// Created by G750 on 02.12.2017.
//

#include "SBTTileSequence.h"
#include "SBTFrame.h"
#include "SBTTileSheet.h"

SBTTileSequence::SBTTileSequence(SBTTileSheet* texture, std::vector<SBTFrame> frames_basis):
        m_tileSheet(texture), m_frames_basis(std::move(frames_basis) )
{

}

void SBTTileSequence::addFramesSet(const std::vector<SBTFrame>& set)
{
    for(auto& frame : set)
    {
        addFrame(frame);
    }
}

const SBTFrame& SBTTileSequence::getSequenceStateFrame(int frameNum) const
{
    return m_frames_basis[frameNum];
}

int SBTTileSequence::getSequenceStateAngle(int frameNum) const
{
    return 0;
}

const std::string& SBTTileSequence::getMyTileSheetFileName() const
{
    return m_tileSheet->getFileName();
}

void SBTTileSequence::addFrame(const SBTFrame& frame)
{
    m_frames_basis.emplace_back(frame);
}