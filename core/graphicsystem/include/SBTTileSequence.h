//
// Created by G750 on 02.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTTILESEQUENCE_H
#define GAME_PROTOTYPE_SBTTILESEQUENCE_H
#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "SBTAbstractSequence.h"

class SBTTileSheet;
class SBTFrame;
//Сущность, являющаяся набором логически связанных тайлов. Особенность тайлов в том, что они одинаковых размеров
//Содержит именованные последовательности, представляющие собой произвольное подмножество набора кадров
//Анимация в контексте данного класса - просто набор кадров, в отличии от класса SBTAnimation, где
//вводится время, за которое данная последовательность проигрывается и признак повторяемости
//m_frames_basis - базис, состоящий из множества произвольных кадров. Кадр(SBTFrame) - сущность, описывающая границы спрайта.
//depricated: m_animations - набор последовательностей, образующих анимацию, каждая из которых имеет строковый идентификатор
//m_texture - указатель на текстуру, из которой отображаются кадры
class SBTTileSequence
{
public:
    typedef std::string frameID;

    SBTTileSequence():m_tileSheet(nullptr){}

    explicit SBTTileSequence(SBTTileSheet* texture, std::vector<SBTFrame> frames_basis = std::vector<SBTFrame>() );

    void addFrame(const SBTFrame& frame);

    void addFramesSet(const std::vector<SBTFrame>& set);

    void clearBasis(sf::Texture* texture){m_frames_basis.clear();}

    const std::vector<SBTFrame>& getBasis(){return m_frames_basis;}

    const SBTFrame& getSequenceStateFrame(int frameNum) const;

    int getSequenceStateAngle(int frameNum) const;

    const std::string& getMyTileSheetFileName() const;

    int size() const {return m_frames_basis.size();}
private:
    std::vector<SBTFrame> m_frames_basis;

    SBTTileSheet* m_tileSheet;
};
#endif //GAME_PROTOTYPE_SBTTILESEQUENCE_H
