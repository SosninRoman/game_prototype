#include "SpriteNode.h"


SpriteNode::SpriteNode(sf::Texture& texture, float xscale, float yscale):
	mSprite(texture), mScaleFactor(xscale,yscale)
{
	mSprite.scale(mScaleFactor.x,mScaleFactor.y);
	centerOrigin();
}

SpriteNode::SpriteNode(sf::Sprite sprite, float xscale, float yscale):
	mScaleFactor(xscale, yscale)
{
	if(sprite.getTexture() != nullptr)
	{
		mSprite.setTexture(*sprite.getTexture());
	}
	mSprite.setTextureRect(sprite.getTextureRect());
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mSprite, states);
}

sf::FloatRect SpriteNode::getGlobalBounds() const
{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

void SpriteNode::centerOrigin()
{
	auto rect = mSprite.getTextureRect();
	//auto* text = mSprite.getTexture();
	//setOrigin(static_cast<float>(text->getSize().x) / 2 * mScaleFactor.x, static_cast<float>(text->getSize().y) / 2 * mScaleFactor.y);
	setOrigin(static_cast<float>(rect.width) / 2 * mScaleFactor.x, static_cast<float>(rect.height) / 2 * mScaleFactor.y);
}

sf::Vector2u SpriteNode::getSize()
{
	return sf::Vector2u( static_cast<unsigned int>(mSprite.getTexture()->getSize().x * mScaleFactor.x), static_cast<unsigned int>(mSprite.getTexture()->getSize().y * mScaleFactor.y));
}

void SpriteNode::setSprite(sf::Sprite& sprite)
{
	mSprite.setTexture(*sprite.getTexture());
	mSprite.setTextureRect(sprite.getTextureRect());
	mSprite.setColor(sprite.getColor());
}

void SpriteNode::setRectangle(sf::IntRect& rect)
{
	mSprite.setTextureRect(rect);
}