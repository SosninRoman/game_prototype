#pragma once
#include "Animator.h"
#include "AnimatedNode.h"

class Cube: public AnimatedNode
{
public:
	Cube(TextureHolder& textures);

	virtual RecieverType getActionType() const;
	virtual NodeType getNodeType() const;

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void centerOrigin();
	void kill();
	bool isMarkedForRemove();
private:
	void updateCurrent(sf::Time dt);
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	Animator mAnimator;
	bool mRemove;
};

