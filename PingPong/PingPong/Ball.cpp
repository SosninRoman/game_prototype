#include "Ball.h"

Ball::Ball(TextureHolder& textures, sf::Vector2f center):
	SceneNode(),AnimatedNode(textures), master(RecieverType::None)
{
	setPosition(center);
}

void Ball::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{	
	AnimatedNode::drawCurrent(target, states);
}

RecieverType Ball::getActionType() const
{
	return RecieverType::Ball;
}

NodeType Ball::getNodeType() const
{
	return NodeType::Ball;
}

void Ball::updateCurrent(sf::Time dt)
{	
	SceneNode::updateCurrent(dt);
	AnimatedNode::updateCurrent(dt);
}

void Ball::centerOrigin()
{
	AnimatedNode::centerOrigin();
}

sf::FloatRect Ball::getGlobalBounds() const
{
	//return getTransform().transformRect( getSpriteBounds() );
	return AnimatedNode::getGlobalBounds();
}

void Ball::setMaster(RecieverType type)
{
	master = type;
}