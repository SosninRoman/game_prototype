#pragma once
#include "SBTAbstractSpriteNode.h"
#include "LayerNode.h"

class Cube: public SBTAbstractSpriteNode
{
public:
	Cube(SBTSpriteAtlas& atlas, const spriteID& frameName);

    int getActionType() const override;
	
	int getNodeType() const override;

	sf::FloatRect getGlobalBounds() const override;
	
	void centerOrigin() override;
	
	void kill();
	
	bool isMarkedForRemove() override;
private:
	void updateCurrent(sf::Time dt) override;
	
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool m_remove;
};

