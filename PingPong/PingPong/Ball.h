#pragma once
#include "Animator.h"
#include "ResourceHolder.h"
#include "AnimatedNode.h"

class Ball :
	public AnimatedNode
{
public:
	Ball(TextureHolder& textures, sf::Vector2f center);

	void					drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//
	sf::FloatRect			getGlobalBounds() const;
	NodeType				getNodeType() const;
	RecieverType			getActionType() const;

	virtual void			centerOrigin();
	void					setMaster(RecieverType type);
protected:
	void					updateCurrent(sf::Time dt);
private:
	RecieverType			master;
};

