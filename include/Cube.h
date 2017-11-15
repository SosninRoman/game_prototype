#pragma once
#include "SBTAbstractSpriteNode.h"
#include "LayerNode.h"

class Cube: public SBTAbstractSpriteNode
{
public:
	Cube(sf::Sprite& textures);

	virtual int getActionType() const;
	
	virtual int getNodeType() const;

	virtual sf::FloatRect getGlobalBounds() const;
	
	virtual void centerOrigin();
	
	void kill();
	
	bool isMarkedForRemove();
private:
	void updateCurrent(sf::Time dt);
	
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	bool mRemove;
};

