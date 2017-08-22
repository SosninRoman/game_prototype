#include "Ball.h"

Ball::Ball(TextureHolder& textures, sf::Vector2f center):
	SceneNode(),AnimatedNode(textures)
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
	
	//MoveableNode::updateCurrent(dt);
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