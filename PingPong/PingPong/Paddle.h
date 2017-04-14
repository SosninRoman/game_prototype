#pragma once
#include "MoveableNode.h"

class Paddle: public MoveableNode
{
public:
	enum class PaddleType
	{
		LeftPaddle = 0,
		RightPaddle = 1,
		NumOfTypes = 1 << 1,
	};

	Paddle(sf::RectangleShape&rect, RecieverType type ):mRect(rect), mRecieverType(type){mType = PaddleType::RightPaddle;}
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
	sf::FloatRect getGlobalBounds() const
	{
		return getWorldTransform().transformRect(mRect.getGlobalBounds());
	}
	void updateCurrent(sf::Time dt)
	{
		MoveableNode::updateCurrent(dt);
		MoveableNode::setVelocity(0,0);
	}

	float getSpeed() const;

	NodeType getNodeType() const;
	RecieverType getActionType() const;

private:
	sf::RectangleShape mRect;
	RecieverType mRecieverType;
	PaddleType mType;
};

