#include "Ball.h"
#include "RecieverTypeEnum.h"

Ball::Ball(GraphicResourceHolder* textures, sf::Vector2f center):
	SBTAbstractSceneNode(),SBTAbstractAnimatedNode(textures), m_master(RecieverType::NoneRecieverType)
{
	setPosition(center);
}

void Ball::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
	SBTAbstractAnimatedNode::drawCurrent(target, states);
}

int Ball::getActionType() const
{
	return RecieverType::BallRecieverType;
}

int Ball::getNodeType() const
{
	return NodeType::BallNodeType;
}

void Ball::updateCurrent(sf::Time dt)
{	
	SBTAbstractSceneNode::updateCurrent(dt);
	SBTAbstractAnimatedNode::updateCurrent(dt);
}

void Ball::centerOrigin()
{
	SBTAbstractAnimatedNode::centerOrigin();
}

sf::FloatRect Ball::getGlobalBounds() const
{
	return SBTAbstractAnimatedNode::getGlobalBounds();
}

void Ball::setMaster(int type)
{
	m_master = type;
}