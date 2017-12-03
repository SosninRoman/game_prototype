//
// Created by G750 on 02.12.2017.
//

#include "SBTAbstractUnvisibleNode.h"

SBTAbstractUnvisibleNode::SBTAbstractUnvisibleNode(float xscale, float yscale):
        m_sprite(sf::Sprite() ), mScaleFactor(xscale,yscale)
{
    m_sprite.scale(mScaleFactor.x,mScaleFactor.y);
    centerOrigin();
}

void SBTAbstractUnvisibleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

sf::FloatRect SBTAbstractUnvisibleNode::getGlobalBounds() const
{
    return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void SBTAbstractUnvisibleNode::centerOrigin()
{
    auto rect = m_sprite.getTextureRect();
    setOrigin(static_cast<float>(rect.width) / 2 * mScaleFactor.x, static_cast<float>(rect.height) / 2 * mScaleFactor.y);
}

sf::Vector2u SBTAbstractUnvisibleNode::getSize()
{
    return sf::Vector2u( static_cast<unsigned int>(m_sprite.getTexture()->getSize().x * mScaleFactor.x),
                         static_cast<unsigned int>(m_sprite.getTexture()->getSize().y * mScaleFactor.y));
}

void SBTAbstractUnvisibleNode::setRectangle(sf::IntRect& rect)
{
    m_sprite.setTextureRect(rect);
}