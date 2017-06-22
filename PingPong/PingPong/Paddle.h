#pragma once
#include "MoveableNode.h"
#include "Animator.h"

class Paddle: public MoveableNode
{
public:
	enum class PaddleType
	{
		LeftPaddle = 0,
		RightPaddle = 1,
		NumOfTypes = 1 << 1,
	};

	Paddle(sf::RectangleShape&rect, RecieverType type , TextureHolder& textures);

	sf::Vector2u getSize();
	
	sf::FloatRect getGlobalBounds() const;
	
	float getSpeed() const;

	NodeType getNodeType() const;
	RecieverType getActionType() const;

	virtual void centerOrigin();

private:
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	RecieverType mRecieverType;
	PaddleType mType;

	Animator mAnimator;
};

