//
// Created by G750 on 29.11.2017.
//

#include "SBTAnimation.h"
#include "SBTFrame.h"
#include "SBTSpriteSequence.h"
#include "SBTSequenceState.h"

const SBTFrame& SBTAnimation::getFrame(int frameNum)
{
    return m_sequence->getSequenceStateFrame(frameNum);
}

int SBTAnimation::getAngle(int frameNum)
{
    return m_sequence->getSequenceStateAngle(frameNum);
}

std::string SBTAnimation::getMyAtlasFileName()
{
    return m_sequence->getMyAtlasFileName();
}

int SBTAnimation::size() const
{
    return m_sequence->size();
}