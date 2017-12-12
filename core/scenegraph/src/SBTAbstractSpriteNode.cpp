#include "SBTAbstractSpriteNode.h"
#include "SBTSpriteAtlas.h"

SBTAbstractSpriteNode::SBTAbstractSpriteNode(sf::Sprite& sprite,float xscale, float yscale):
m_RenderSprite(sprite), mScaleFactor(xscale,yscale)
{
    m_RenderSprite.scale(mScaleFactor.x,mScaleFactor.y);
    centerOrigin();
}

void SBTAbstractSpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_RenderSprite, states);
}

sf::FloatRect SBTAbstractSpriteNode::getGlobalBounds() const
{
	return getTransform().transformRect(m_RenderSprite.getGlobalBounds());
}

void SBTAbstractSpriteNode::centerOrigin()
{
	auto rect = m_RenderSprite.getTextureRect();
	setOrigin(static_cast<float>(rect.width) / 2 * mScaleFactor.x, static_cast<float>(rect.height) / 2 * mScaleFactor.y);
}

sf::Vector2u SBTAbstractSpriteNode::getSize()
{
	return sf::Vector2u( static_cast<unsigned int>(m_RenderSprite.getTexture()->getSize().x * mScaleFactor.x),
                         static_cast<unsigned int>(m_RenderSprite.getTexture()->getSize().y * mScaleFactor.y));
}

void SBTAbstractSpriteNode::setSprite(sf::Sprite& sprite)
{
	m_RenderSprite.setTexture(*sprite.getTexture());
	m_RenderSprite.setTextureRect(sprite.getTextureRect());
	m_RenderSprite.setColor(sprite.getColor());
}

void SBTAbstractSpriteNode::setRectangle(sf::IntRect& rect)
{
	m_RenderSprite.setTextureRect(rect);
}