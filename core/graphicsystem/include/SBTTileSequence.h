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

//#include "SBTTileSheet.h"
class SBTTileSheet;

//Сущность, являющаяся набором логически связанных тайлов. Особенность тайлов в том, что они одинаковых размеров
//Содержит именованные последовательности, представляющие собой произвольное подмножество набора кадров
//Анимация в контексте данного класса - просто набор кадров, в отличии от класса SBTAnimation, где
//вводится время, за которое данная последовательность проигрывается и признак повторяемости
//m_frames_basis - базис, состоящий из множества произвольных кадров. Кадр(SBTFrame) - сущность, описывающая границы спрайта.
//depricated: m_animations - набор последовательностей, образующих анимацию, каждая из которых имеет строковый идентификатор
//m_texture - указатель на текстуру, из которой отображаются кадры

//class SBTTileSequence
template<>
class SBTTemplateSequence<SBTTileSheet, SBTFrame>
{
public:
    typedef std::string frameID;

    SBTTemplateSequence():m_resource(nullptr){}

    explicit SBTTemplateSequence(SBTTileSheet* texture, std::vector<SBTFrame> frames_basis = std::vector<SBTFrame>() );

    void addFrame(const SBTFrame& frame);

    void addFramesSet(const std::vector<SBTFrame>& set);

    void clearBasis(sf::Texture* texture){m_framesBasis.clear();}

    const std::vector<SBTFrame>& getBasis(){return m_framesBasis;}

    const SBTFrame& getSequenceStateFrame(int frameNum) const;

    int getSequenceStateAngle(int frameNum) const;

    const std::string& getMyResourceFileName() const;

    int size() const {return m_framesBasis.size();}
private:
    std::vector<SBTFrame> m_framesBasis;

    SBTTileSheet* m_resource;
};

SBTTemplateSequence<SBTTileSheet, SBTFrame>::SBTTemplateSequence(
        SBTTileSheet* texture, std::vector<SBTFrame> frames_basis):
        m_resource(texture), m_framesBasis(std::move(frames_basis) )
{

}

void SBTTemplateSequence<SBTTileSheet, SBTFrame>::addFramesSet(const std::vector<SBTFrame>& set)
{
    for(auto& frame : set)
    {
        addFrame(frame);
    }
}

const SBTFrame& SBTTemplateSequence<SBTTileSheet, SBTFrame>::getSequenceStateFrame(int frameNum) const
{
    return m_framesBasis[frameNum];
}

int SBTTemplateSequence<SBTTileSheet, SBTFrame>::getSequenceStateAngle(int frameNum) const
{
    return 0;
}

const std::string& SBTTemplateSequence<SBTTileSheet, SBTFrame>::getMyResourceFileName() const
{
    return m_resource->getFileName();
}

void SBTTemplateSequence<SBTTileSheet, SBTFrame>::addFrame(const SBTFrame& frame)
{
    m_framesBasis.emplace_back(frame);
}


#endif //GAME_PROTOTYPE_SBTTILESEQUENCE_H
