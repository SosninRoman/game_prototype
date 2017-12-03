//
// Created by G750 on 02.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTSEQUENCESTATE_H
#define GAME_PROTOTYPE_SBTSEQUENCESTATE_H
#include "SBTFrame.h"

//Сущность, описывающее состояние кадра в последовательности.
//Включает в себя имя кадра из текстурного атласа и угол, под которым он будет изображен.
struct SBTSequenceState
{
    typedef std::string frameID;
    explicit SBTSequenceState(const frameID& frmID, int angl = 0):
    m_frameID(frmID), m_angle(angl)
    {}

    frameID m_frameID;

    int m_angle = 0;
};
#endif //GAME_PROTOTYPE_SBTSEQUENCESTATE_H
