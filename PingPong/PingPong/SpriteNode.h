#pragma once
#include "SceneNode.h"
#include <SFML\Graphics.hpp>

class SpriteNode: public virtual SceneNode
{
public:
	SpriteNode(sf::Texture& texture, float xscale, float yscale);

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void centerOrigin();

	sf::Vector2u getSize();
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite mSprite;
	sf::Vector2f mScaleFactor; 
};

