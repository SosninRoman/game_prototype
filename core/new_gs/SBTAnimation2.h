//
// Created by G750 on 21.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTANIMATION_H
#define GAME_PROTOTYPE_SBTANIMATION_H
#include <SFML/Graphics.hpp>
#include <string>
#include "SBTFrame.h"

class SBTSpriteSequence;

//Сущность, являющаяся одной из анимаций, заданных в m_sheet
//m_sheet - набор спрайтов, из которого берется анимация
//m_animationID - строка, идентифицирующая конкретную анимацию из m_sheet, которую представляет экземпляр SBTAnimation
//m_duration - время, за которое должна быть прокручена анимация
//m_looping - признак, определяющий, будет ли анимация повторяться (false - играем один раз и замрет в последнем кадре)
class SBTAnimation
{
    SBTAnimation(SBTSpriteSequence* sheet, const std::string& animationID, sf::Time& duration, bool looping):
            m_sequence(sheet),
            m_animationID(animationID),
            m_duration(duration),
            m_looping(looping)
    {
    }

    /*Возвращаем кадр по его порядковому номеру в анимации*/
    SBTFrame* getFrame(int frameNum){}
private:
    SBTSpriteSequence* m_sequence;
    std::string m_animationID;
    sf::Time m_duration;
    bool m_looping;
};
#endif //GAME_PROTOTYPE_SBTANIMATION_H
