#pragma once
#include "Animator.h"
#include "AnimatedNode.h"

class Paddle: public AnimatedNode
{
public:
	enum class PaddleType
	{
		LeftPaddle = 0,
		RightPaddle = 1,
		NumOfTypes = 1 << 1,
	};

	Paddle(RecieverType type , TextureHolder& textures);
	
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
};

