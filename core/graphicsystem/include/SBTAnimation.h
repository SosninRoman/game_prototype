//
// Created by G750 on 21.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTANIMATION_H
#define GAME_PROTOTYPE_SBTANIMATION_H
#include <SFML/Graphics.hpp>
#include <string>

class SBTFrame;
class SBTSequence;
//Сущность, являющаяся анимацией, заданной в m_sequence, дополненной временем выполнения и признаком повторяемости
//m_sequence - набор спрайтов, на базе которого строится анимация
//depricated: m_animationID - строка, идентифицирующая конкретную анимацию из m_sequence, которую представляет экземпляр SBTAnimation
//m_duration - время, за которое должна быть прокручена анимация
//m_looping - признак, определяющий, будет ли анимация повторяться (false - играем один раз и замрет в последнем кадре)
class SBTAnimation
{
public:
    SBTAnimation(const SBTSequence* sequence, sf::Time& duration, bool looping):
            m_sequence(sequence),
            m_duration(duration),
            m_looping(looping)
    {
    }

    /*Возвращаем кадр по его порядковому номеру в анимации*/
    SBTFrame getFrame(int frameNum);

    int getAngle(int frameNum);

    std::string getMyResourceFileName();

    const sf::Time& getDuration(){return m_duration;}

    int size() const;

    bool isLooping(){return m_looping;}
private:
    const SBTSequence* m_sequence;

    sf::Time m_duration;

    bool m_looping;
};
#endif //GAME_PROTOTYPE_SBTANIMATION_H
