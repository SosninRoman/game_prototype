#pragma once
#include "Animator.h"
#include "AnimatedNode.h"
#include "SpriteNode.h"

class Cube: public SpriteNode
{
public:
	Cube(sf::Sprite& textures);

	virtual RecieverType getActionType() const;
	
	virtual NodeType getNodeType() const;

	virtual sf::FloatRect getGlobalBounds() const;
	
	virtual void centerOrigin();
	
	void kill();
	
	bool isMarkedForRemove();
private:
	void updateCurrent(sf::Time dt);
	
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	bool mRemove;
};

