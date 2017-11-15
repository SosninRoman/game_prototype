#include "SBTAbstractSpriteNode.h"


SBTAbstractSpriteNode::SBTAbstractSpriteNode(sf::Texture& texture, float xscale, float yscale):
	mSprite(texture), mScaleFactor(xscale,yscale)
{
	mSprite.scale(mScaleFactor.x,mScaleFactor.y);
	centerOrigin();
}

SBTAbstractSpriteNode::SBTAbstractSpriteNode(sf::Sprite sprite, float xscale, float yscale):
	mScaleFactor(xscale, yscale)
{
	if(sprite.getTexture() != nullptr)
	{
		mSprite.setTexture(*sprite.getTexture());
	}
	mSprite.setTextureRect(sprite.getTextureRect());
}

void SBTAbstractSpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

sf::FloatRect SBTAbstractSpriteNode::getGlobalBounds() const
{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

void SBTAbstractSpriteNode::centerOrigin()
{
	auto rect = mSprite.getTextureRect();
	setOrigin(static_cast<float>(rect.width) / 2 * mScaleFactor.x, static_cast<float>(rect.height) / 2 * mScaleFactor.y);
}

sf::Vector2u SBTAbstractSpriteNode::getSize()
{
	return sf::Vector2u( static_cast<unsigned int>(mSprite.getTexture()->getSize().x * mScaleFactor.x), static_cast<unsigned int>(mSprite.getTexture()->getSize().y * mScaleFactor.y));
}

void SBTAbstractSpriteNode::setSprite(sf::Sprite& sprite)
{
	mSprite.setTexture(*sprite.getTexture());
	mSprite.setTextureRect(sprite.getTextureRect());
	mSprite.setColor(sprite.getColor());
}

void SBTAbstractSpriteNode::setRectangle(sf::IntRect& rect)
{
	mSprite.setTextureRect(rect);
}