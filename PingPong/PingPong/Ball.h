#pragma once
#include "MoveableNode.h"
#include "Animator.h"
#include "ResourceHolder.h"

class Ball :
	public MoveableNode
{
public:
	Ball(sf::CircleShape& ball, TextureHolder& textures);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//
	void setOutlineColor(sf::Color clr)
	{
		mBall.setOutlineColor(clr);
	}
	void setOutlineThickness(float th)
	{
		mBall.setOutlineThickness(th);
	}
	void setFillColor(sf::Color clr)
	{
		mBall.setFillColor(clr);
	}
	float getSize() const
	{
		return mBall.getRadius();
	}
	sf::FloatRect getGlobalBounds() const
	{
		return getTransform().transformRect(mBall.getGlobalBounds());
	}
	NodeType getNodeType() const;
	RecieverType getActionType() const;
protected:
	void updateCurrent(sf::Time dt);
private:
	sf::CircleShape mBall;
	Animator mAnimator;
};

