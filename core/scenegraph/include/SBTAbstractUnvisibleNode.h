//
// Created by G750 on 02.12.2017.
//

#ifndef GAME_PROTOTYPE_SBTABSTRACTUNVISIBLENODE_H
#define GAME_PROTOTYPE_SBTABSTRACTUNVISIBLENODE_H

#include "SBTAbstractSceneNode.h"
#include <SFML\Graphics.hpp>

class SBTAbstractUnvisibleNode: public virtual SBTAbstractSceneNode
{
public:
    typedef std::string spriteID;
    explicit SBTAbstractUnvisibleNode(float xscale = 1, float yscale = 1);

    sf::FloatRect	getGlobalBounds() const override;

    void			centerOrigin() override;

    sf::Vector2u			getSize();

    void					setRectangle(sf::IntRect& rect);

protected:
    void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Sprite				m_sprite;
    sf::Vector2f			mScaleFactor;
};

#endif //GAME_PROTOTYPE_SBTABSTRACTUNVISIBLENODE_H
