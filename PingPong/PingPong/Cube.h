#pragma once
#include "SceneNode.h"
#include "Animator.h"

class Cube: public SceneNode
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

