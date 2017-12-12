#pragma once
#include "SBTAbstractSceneNode.h"
#include <SFML\Graphics.hpp>

class SBTSpriteAtlas;

class SBTAbstractSpriteNode: public virtual SBTAbstractSceneNode
{
public:
    typedef std::string spriteID;
	explicit SBTAbstractSpriteNode(sf::Sprite& sprite,float xscale = 1, float yscale = 1);

	sf::FloatRect	getGlobalBounds() const override;
	void			centerOrigin() override;

	sf::Vector2u			getSize();
	void					setSprite(sf::Sprite& sprite);
	void					setRectangle(sf::IntRect& rect);
protected:
	void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
private:	
	sf::Sprite				m_RenderSprite;
    spriteID                m_spriteID;
	sf::Vector2f			mScaleFactor; 
};

