#pragma once
#include "SBTAbstractSceneNode.h"
#include <SFML\Graphics.hpp>
#include "ResourceHolder.h"

class SBTAbstractSpriteNode: public virtual SBTAbstractSceneNode
{
public:
	SBTAbstractSpriteNode(sf::Texture& texture, float xscale = 1, float yscale = 1);
	SBTAbstractSpriteNode(sf::Sprite sprite, float xscale = 1, float yscale = 1);

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

