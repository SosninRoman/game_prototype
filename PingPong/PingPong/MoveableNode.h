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
	void rotate_velocity(float degree)
	{
		sf::Vector2f nVelocity;
		nVelocity.x = mVelocity.x * std::cos(degree) - mVelocity.y * std::sin(degree);
		nVelocity.y = mVelocity.x * std::sin(degree) + mVelocity.y * std::cos(degree);
		mVelocity = std::move(nVelocity);
	}
private:
	sf::Vector2f mVelocity;
};

