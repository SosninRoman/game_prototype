#pragma once
#include "MoveableNode.h"
#include "Animator.h"
#include "ResourceHolder.h"
#include "AnimatedNode.h"

class Ball :
	public MoveableNode, public AnimatedNode
{
public:
	Ball(TextureHolder& textures);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//
	sf::FloatRect getGlobalBounds() const;
	NodeType getNodeType() const;
	RecieverType getActionType() const;

	virtual void centerOrigin();
protected:
	void updateCurrent(sf::Time dt);
};

