//
// Created by G750 on 03.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTABSTRACTSEQUENCE_H
#define GAME_PROTOTYPE_SBTABSTRACTSEQUENCE_H
#include <string>
#include <vector>
#include "SBTFrame.h"

class SBTSequence
{
public:
    SBTSequence() = default;
    virtual ~SBTSequence() = default;

    virtual SBTFrame     getSequenceStateFrame(int frameNum) const = 0;
    virtual int                 getSequenceStateAngle(int frameNum) const = 0;
    virtual const std::string&  getMyResourceFileName() const = 0;
    virtual int                 size() const = 0;
};

#endif //GAME_PROTOTYPE_SBTABSTRACTSEQUENCE_H