#pragma once
#include "SceneNode.h"
#include <SFML\Graphics.hpp>

class SpriteNode: public SceneNode
{
public:
	SpriteNode(sf::Texture& texture);
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite mSprite;
};

