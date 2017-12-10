//
// Created by G750 on 29.11.2017.
//

#include "SBTAnimation.h"
#include "SBTAbstractSequence.h"

SBTFrame SBTAnimation::getFrame(int frameNum)
{
    return m_sequence->getSequenceStateFrame(frameNum);
}

int SBTAnimation::getAngle(int frameNum)
{
    return m_sequence->getSequenceStateAngle(frameNum);
}

std::string SBTAnimation::getMyAtlasFileName()
{
    return m_sequence->getMyResourceFileName();
}

int SBTAnimation::size() const
{
    return m_sequence->size();
}