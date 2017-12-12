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
#include "SBTAnimation.h"
#include "SBTGraphicResourceHolder.h"

using std::string;
using std::vector;
using std::map;
class SBTAnimation;
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
    typedef std::string animationID;

    explicit SBTAnimator(GraphicResourceHolder* textures);

    //Добавляем последовательность sequenceIDInAtlas из набора тайлов\текстурного атласа SpriteAtlasID в m_animations,
    // снабдив ее duration, looping и идентификатором animationNameInAnimator
    //идентификатор animationNameInAnimator нужен из-за того, что в одном аниматоре могут быть последовательности из
    //разных атласов, а значит их идентификаторы могут совпадать
    void addAnimation(const std::string& GraphicResourceID, const string& sequenceIDInGraphicResource,
                      const animationID& animationNameInAnimator, sf::Time duration, bool looping);

    void switchAnimation(const string& animationNameInAnimator);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(sf::Time dt);

    const sf::Sprite& getRenderSprite() const;

    sf::Vector2u getSize();

    SBTAnimation* findAnimation(const string& animationNameInAnimator);

    const SBTAnimation* getCurrentAnimation();
private:
    sf::Sprite					m_renderSprite;

    sf::Time					m_currentTime;

    //animationID - так называется анимация в Animator
    //Здесь каждая SBTAnimation имеет свой строковый идентификатор, поскольку может встретиться случай,
    //когда две анимации из разных SBTSpriteAtlas будут иметь одинаковые имена
    map<animationID, SBTAnimation>	m_animations;

    map_iterator				m_currentAnimation;

    GraphicResourceHolder*      m_graphicResources;
};

#endif //GAME_PROTOTYPE_SBTANUMATOR_H
