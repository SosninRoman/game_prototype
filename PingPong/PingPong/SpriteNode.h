#pragma once
#include "SceneNode.h"
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"

class SpriteNode: public virtual SceneNode
{
public:
	SpriteNode(sf::Texture& texture, float xscale = 1, float yscale = 1);
	SpriteNode(sf::Sprite& sprite, float xscale = 1, float yscale = 1);

	virtual sf::FloatRect	getGlobalBounds() const;
	virtual void			centerOrigin();

	sf::Vector2u			getSize();
	void					setSprite(sf::Sprite& sprite);
	void					setRectangle(sf::IntRect& rect);
protected:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:	
	sf::Sprite				mSprite;
	sf::Vector2f			mScaleFactor; 
};

