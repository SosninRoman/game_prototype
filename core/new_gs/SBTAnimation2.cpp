//
// Created by G750 on 29.11.2017.
//

#include "SBTAnimation2.h"
#include "SBTFrame.h"
#include "SBTSpriteSequence.h"

const SBTFrame& SBTAnimation::getFrame(int frameNum)
{
    return m_sequence->getFrame(frameNum);
}

std::string SBTAnimation::getMyAtlasFileName()
{
    return m_sequence->getMyAtlasFileName();
}

int SBTAnimation::size() const
{
    return m_sequence->size();
}