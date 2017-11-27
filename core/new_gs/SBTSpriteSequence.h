//
// Created by G750 on 23.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTSPRITESHEET_H
#define GAME_PROTOTYPE_SBTSPRITESHEET_H
#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "SBTFrame.h"

//Сущность, являющаяся набором логически связанных спрайтов
//Содержит именованные последовательности, представляющие собой произвольное подмножество набора кадров
//Анимация в контексте данного класса - просто набор кадров, в отличии от класса SBTAnimation, где
//вводится время, за которое данная последовательность проигрывается
//m_frames_basis - базис, состоящий из множества произвольных кадров. Кадр(SBTFrame) - сущность, описывающая границы спрайта.
//m_animations - набор последовательностей, образующих анимацию, каждая из которых имеет строковый идентификатор
//m_texture - указатель на текстуру, из которой отображаются кадры
class SBTSpriteSequence
{
public:
    typedef std::string animationID;
    typedef int animationPos;

    SBTSpriteSequence(){};
    explicit SBTSpriteSequence(sf::Texture* texture):m_texture(texture){};
    SBTSpriteSequence(sf::Texture* texture, const std::vector<SBTFrame>& frames_basis):
            m_texture(texture), m_frames_basis(frames_basis){}
    SBTSpriteSequence(sf::Texture* texture, const std::vector<SBTFrame>& frames_basis,
                   std::map<animationID, std::vector<animationPos> >& animations):
            m_texture(texture), m_frames_basis(frames_basis), m_animations(animations){}

    void addFrame(SBTFrame frame);
    void addFrame(const std::string& name, int rectLeft, int rectTop, int rectWidth, int rectHeight);
    void addFramesSet(const std::vector<SBTFrame>& set);

    void addFrameToSequence(animationID animID, animationPos animPos);
    void addSequence(animationID animID, std::vector<animationPos> framesIDs);

    void setTexture(sf::Texture* texture);
    void setTextureAndClear(sf::Texture* texture);

    const std::vector<animationPos>& getSequence(const animationID& seqID);
private:
    sf::Texture* m_texture;
    std::vector<SBTFrame> m_frames_basis;
    std::map<animationID, std::vector<animationPos> > m_animations;
};
#endif //GAME_PROTOTYPE_SBTSPRITESHEET_H
