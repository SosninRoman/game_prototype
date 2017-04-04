#pragma once
#include "MoveableNode.h"

class Paddle: public MoveableNode
{
public:
	Paddle(sf::RectangleShape&rect):mRect(rect){}
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const ;
	void setOutlineColor(sf::Color clr)
	{
		mRect.setOutlineColor(clr);
	}
	void setOutlineThickness(float th)
	{
		mRect.setOutlineThickness(th);
	}
	void setFillColor(sf::Color clr)
	{
		mRect.setFillColor(clr);
	}
	sf::Vector2f getSize() const
	{
		return mRect.getSize();
	}
	sf::FloatRect getGlobalBounds()
	{
		return getWorldTransform().transformRect(mRect.getGlobalBounds());
	}
	void updateCurrent(sf::Time dt)
	{
		MoveableNode::updateCurrent(dt);
		MoveableNode::setVelocity(0,0);
	}
private:
	sf::RectangleShape mRect;
};

