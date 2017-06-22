#pragma once
#include "MoveableNode.h"
#include "Animator.h"
#include "ResourceHolder.h"

class Ball :
	public MoveableNode
{
public:
	Ball(TextureHolder& textures);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//
	sf::FloatRect getGlobalBounds() const;
	NodeType getNodeType() const;
	RecieverType getActionType() const;

	virtual void centerOrigin();
	sf::Vector2u getSize();
protected:
	void updateCurrent(sf::Time dt);
private:
	Animator mAnimator;
};

