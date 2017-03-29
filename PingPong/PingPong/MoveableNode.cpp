#include "MoveableNode.h"

void MoveableNode::setVelocity(sf::Vector2f v)
{
	mVelocity = v;
}

void MoveableNode::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f MoveableNode::getVelocity()
{
	return mVelocity;
}

void MoveableNode::accelerate(sf::Vector2f v)
{
	mVelocity += v;
}

void MoveableNode::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void MoveableNode::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}