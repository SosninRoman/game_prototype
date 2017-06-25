#pragma once
#include "SceneNode.h"
#include "SFML\Graphics.hpp"

class InvisibleNode: public SceneNode
{
public:
	InvisibleNode();
	~InvisibleNode();
private:
	sf::IntRect mRectangle;
};

