#include "SpriteNode.h"


SpriteNode::SpriteNode(sf::Texture& texture):mSprite(texture)
{
	mSprite.scale(0.5,0.5);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(mSprite, states);
}