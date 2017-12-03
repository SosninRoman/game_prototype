//
// Created by G750 on 23.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTSPRITESHEET_H
#define GAME_PROTOTYPE_SBTSPRITESHEET_H

#include "SBTAbstractSequence.h"
#include "SBTSequenceState.h"
#include "SBTSpriteAtlas.h"

//typedef SBTTemplateSequence<SBTSpriteAtlas, SBTSequenceState> SBTSpriteSequence;

//#include <vector>
//#include <map>
//#include <string>
//#include <SFML/Graphics.hpp>
//
//class SBTSpriteAtlas;
//class SBTFrame;
//class SBTSequenceState;

//Сущность, являющаяся набором логически связанных спрайтов
//Содержит именованные последовательности, представляющие собой произвольное подмножество набора кадров
//Анимация в контексте данного класса - просто набор кадров, в отличии от класса SBTAnimation, где
//вводится время, за которое данная последовательность проигрывается и признак повторяемости
//m_frames_basis - базис, состоящий из множества произвольных кадров. Кадр(SBTFrame) - сущность, описывающая границы спрайта.
//depricated: m_animations - набор последовательностей, образующих анимацию, каждая из которых имеет строковый идентификатор
//m_texture - указатель на текстуру, из которой отображаются кадры

//class SBTSpriteSequence
//{
//public:
//    typedef std::string frameID;
//
//    SBTSpriteSequence():m_atlas(nullptr){}
//
//    explicit SBTSpriteSequence(SBTSpriteAtlas* texture, std::vector<SBTSequenceState> frames_basis = std::vector<SBTSequenceState>());
//
//    void addFrame(const frameID& frame, int angle = 0);
//
//    void addFrame(const SBTSequenceState& frame);
//
//    void addFramesSet(const std::vector<frameID>& set);
//
//    void clearBasis(sf::Texture* texture){m_frames_basis.clear();}
//
//    const std::vector<SBTSequenceState>& getBasis(){return m_frames_basis;}
//
//    const SBTFrame& getSequenceStateFrame(int frameNum) const;
//
//    const SBTSequenceState& getSequenceState(int frameNum) const;
//
//    int getSequenceStateAngle(int frameNum) const;
//
//    const std::string& getMyAtlasFileName() const;
//
//    int size() const {return m_frames_basis.size();}
//private:
//    //std::vector<frameID> m_frames_basis;
//    std::vector<SBTSequenceState> m_frames_basis;
//
//    SBTSpriteAtlas* m_atlas;
//};
#endif
