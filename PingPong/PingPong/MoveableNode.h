#pragma once
#include "SceneNode.h"

class MoveableNode :
	public SceneNode
{
public:
	void setVelocity(sf::Vector2f v);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();
	void accelerate(sf::Vector2f v);
	void accelerate(float vx, float vy);

	void updateCurrent(sf::Time dt);
private:
	sf::Vector2f mVelocity;
};

