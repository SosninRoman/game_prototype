//
// Created by G750 on 21.11.2017.
//

#ifndef GAME_PROTOTYPE_SBTANUMATOR_H
#define GAME_PROTOTYPE_SBTANUMATOR_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"
#include "SBTAnimation.h"

using std::string;
using std::vector;
using std::map;

//Класс, отвечающий за смену кадров анимации, переключение анимации, отрисовку спрайта объекта
//m_renderSprite - спрайт, который явлюется изображением объекта в игровом окне
//m_currentTime - текущее время отсчета, используемое для переключения кадров анимации
//m_animations - набор анимаций, соответствующий сущности, владеющей аниматором
//m_currentAnimation - текущая анимация аниматора
//m_textures - ссылка на владельца всех TileSheet-ов
class SBTAnimator
{
public:
    typedef map<string, SBTAnimation>::iterator map_iterator;

    explicit SBTAnimator(TextureHolder& textures);

    SBTAnimation* addAnimation(const std::string& animationNameInAnimator, const std::string& tileSheetID,
                               const string& animationID, sf::Time duration, bool looping){};

    void switchAnimation(const string& animationNameInAnimator){};

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{};

    void update(sf::Time dt){};

    const sf::Sprite& getRenderSprite() const{};

    sf::Vector2u getSize(){};

    SBTAnimation* findAnimation(const string& name){};

    const SBTAnimation* getCurrentAnimation(){return (m_currentAnimation == m_animations.end())? nullptr : &(m_currentAnimation->second);}
private:
    sf::Sprite					m_renderSprite;

    sf::Time					m_currentTime;

    //string - как называется анимация в Animator
    //Здесь каждая SBTAnimation имеет свой строковый идентификатор, поскольку может встретиться случай,
    //когда две анимации из разных SBTSpriteSheet будут иметь одинаковые имена
    map<string, SBTAnimation>	m_animations;

    map_iterator				m_currentAnimation;

    TextureHolder&              m_textures;
};

#endif //GAME_PROTOTYPE_SBTANUMATOR_H
